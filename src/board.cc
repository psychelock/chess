#include "board.hh"

constexpr int direction[6] = {8, 8, 4, 4, 8, 0};  

constexpr int offset[6][8] = \
{
        { -11, -10, -9, -1, 1,  9, 10, 11 }, /* KING */
        { -11, -10, -9, -1, 1,  9, 10, 11 }, /* QUEEN */
        { -10,  -1,  1, 10, 0,  0,  0,  0 }, /* ROOK */
        { -11,  -9,  9, 11, 0,  0,  0,  0 }, /* BISHOP */
        { -21, -19,-12, -8, 8, 12, 19, 21 }, /* KNIGHT */
        { -11,  -9,  9,  11, 0, 0,  0,  0 } // only the capture directions here!
};

constexpr bool slide[6] = { false, true, true, true, false, false };

constexpr int pawndir[4] = { 9,10,11,20};


namespace board
{
    ChessBoard::ChessBoard(std::string setup)
    {
        turn_ = Color::WHITE;
        castling_ = "KQkq";
        en_passant_ = "-";
        for(int i = 0; i < 21; i++)
        {
            board_[i] = std::nullopt;
        }
        for(int i = 101; i < 120; i++)
        {
            board_[i] = std::nullopt;
        }
        create_board(setup);
        calculate_moves();
    }

    void ChessBoard::calculate_moves(void)
    {
        all_moves_ = possible_moves();
    }

    ChessBoard::opt_piece_t ChessBoard::create_piece(char c)
    {
        PieceType type;
        if (islower(c))
        {
            type = pgn_parser::parse_piecetype(toupper(c));
            side_piece_t tmp = std::make_pair(type, Color::BLACK);
            return tmp;
        }
        else if (!islower(c))
        {
            type = pgn_parser::parse_piecetype(c);
            side_piece_t tmp = std::make_pair(type, Color::WHITE);
            return tmp;
        }
        std::cerr << "Invalid symbol, should never happend " << c;
        return std::nullopt;
    }

    void ChessBoard::create_board(std::string setup)
    {
        int count = 0;
        int pos = 91;
        for (auto c: setup)
        {
            if (isalpha(c))
            {
                opt_piece_t tmp = create_piece(c);
                if(tmp == std::nullopt)
                    return;
                board_[pos] = tmp;
                pos++;
            }
            else if (isdigit(c))
            {
                count = c - '0';
                for(int i = 0; i < count; i++)
                {
                    board_[pos] = std::nullopt;
                    pos++;
                }
            }
            else if (c == '/')
            {
                board_[pos] = std::nullopt;
                board_[pos-19] = std::nullopt;
                pos -= 18;
            }
            else
            {
                std::cerr << "Invalid symbol, should never happend " << c;
                exit(1);
            }
        }
    }

    ChessBoard::opt_piece_t ChessBoard::operator[](const Position& position) const
    {
        int file = utils::utype(position.file_get());
        int rank = utils::utype(position.rank_get());
        return board_.at((rank + 1) * 10 + file);       // rank + 1 to access 2nd row at first
    }

    std::string ChessBoard::dump_board()
    {
        std::string res = "";
        for(int i = 91; i != 29; i++)
        {
            if(i % 10 == 9)
            {
                res += "\n";
                i -= 19;
                continue;
            }
            if(board_[i] == std::nullopt)
                res += "- ";
            else
            {
                res += tools::get_char(board_[i]);
                res += " "; 
            }
        }
        res += "\n";
        std::cout << res;
        return res;
    }

    bool ChessBoard::valid_move(const PgnMove& move, bool test)
    {
        all_moves_ = possible_moves();

        auto it =  std::find(all_moves_.begin(), all_moves_.end(), move);
        if(it != all_moves_.end())
        {
            do_move(*it);
            Color oppcol = (turn_ == Color::WHITE) ? Color::BLACK : Color::WHITE;
            if (is_check(oppcol, 0))
            {
                //undo_move();
                return false;
            }
            oppcol = (oppcol == Color::WHITE) ? Color::BLACK : Color::WHITE;

            if(is_check(oppcol, 0))
            {
                if(is_checkmate(oppcol))
                {
                    (*it).report_set(ReportType::CHECKMATE);
                    if(test) //undo only while testing
                        undo_move();
                    return move.get_report() == ReportType::CHECKMATE;

                }
                else
                {
                    (*it).report_set(ReportType::CHECK);
                    if(test) //undo only while testing
                        undo_move();
                    return move.get_report() == ReportType::CHECK;
                }
            }
            if(test) // undo only while testing
                undo_move();
            return move.get_report() == ReportType::NONE; // not a check
        }
        return false;
    }

    void ChessBoard::undo_move(void)
    {
        auto tmp = pvs_.top();
        this->board_ = tmp.get_b();
        this->turn_ = tmp.get_t();
        this->castling_ = tmp.get_cast();
        this->en_passant_ = tmp.get_en_p();
        pvs_.pop();
    }

    std::optional<PgnMove> ChessBoard::add_castling_aux(int pos, int side)
    {
        if (pos == 25 || pos == 95)
        {
            if(board_.at(pos+(1*side)) == std::nullopt &&\
                    board_.at(pos+(2*side)) == std::nullopt)
            {
                if(side == -1 && board_.at(pos-3) != std::nullopt)
                    return std::nullopt;
                if(!(is_check(turn_, pos+(1*side))) &&\
                        !(is_check(turn_, pos+(2*side))))
                {
                    auto to = tools::get_position(pos+(2*side));
                    auto from = tools::get_position(pos);
                    PgnMove currentmove(from.value(), to.value(),\
                            PieceType::KING, false, ReportType::NONE);
                    return currentmove;
                }
            }
        }
        return std::nullopt;
    }

    std::list<PgnMove> ChessBoard::add_castling(int pos, std::list<PgnMove> moves)
    {
        int side = 0;
        char king = (turn_ == Color::WHITE) ? 'K' : 'k';
        char queen = (turn_ == Color::WHITE) ? 'Q' : 'q';

        if(castling_.find(king) != std::string::npos)
        {
            side = 1;
            auto tmp = add_castling_aux(pos, side);
            if(tmp != std::nullopt)
                moves.insert(moves.end(), tmp.value());
        }
        if(castling_.find(queen) != std::string::npos)
        {
            side = -1;
            auto tmp = add_castling_aux(pos, side);
            if(tmp != std::nullopt)
                moves.insert(moves.end(), tmp.value());
        }
        return moves;
    }

    std::list<PgnMove> ChessBoard::possible_moves(void)
    {
        std::list<PgnMove> moves;
        bool capture = false;
        int dest_int;
        for(auto const& [pos, piece] : board_)
        {
            if(piece != std::nullopt && piece->second == turn_)
            {
                int piece_num = utils::utype(piece->first);
                PieceType pt = piece->first;
                if(pt != PieceType::PAWN)
                {
                    for(int dir = 0; dir < direction[piece_num]; dir++)     
                        // each direction the piece can move
                    {
                        dest_int = pos;
                        do
                        {
                            capture = false;
                            dest_int += offset[piece_num][dir];
                            auto to = tools::get_position(dest_int);
                            if(to == std::nullopt) // out of bounds
                                break;
                            if(board_[dest_int] != std::nullopt)
                            {
                                if (board_[dest_int]->second == turn_) // same colored piece
                                    break;
                                else
                                    capture = true;
                            }
                            auto from  = tools::get_position(pos);
                            PgnMove currentmove(from.value(), to.value(), pt, capture, \
                                    ReportType::NONE);

                            moves.insert(moves.end(), currentmove);
                        }while(slide[piece_num] && (capture == false));
                    }
                }
                if(pt == PieceType::KING)
                    moves = add_castling(pos, moves);
                else if(pt == PieceType::PAWN)
                {
                    int side = piece->second == Color::WHITE ? 1 : -1;
                    dest_int = pos;
                    for(int i : pawndir)
                    {
                        capture = false;
                        if(i == 20)
                        {
                            if(turn_ == Color::WHITE)
                            {
                                if(!(pos >30 && pos < 40))
                                    break;
                            }
                            else if(turn_ == Color::BLACK)
                            {
                                if(!(pos >80 && pos < 90))
                                    break;
                            }
                        }
                        dest_int = pos + i * side;  
                        std::optional<Position> to = tools::get_position(dest_int);
                        if(to == std::nullopt) // out of bounds
                            continue;
                        auto dest_piece = board_[dest_int]; // optional pair of piece type and color
                        if(i%10 == 0 && dest_piece != std::nullopt)  // pawn cant move forward
                            continue;
                        else if(i == 20 && board_[dest_int - (10 * side)] != std::nullopt)   // pawn cant jump hey (double forward)
                            continue;
                        else if(i%10 != 0)
                        {
                            if(dest_piece == std::nullopt || dest_piece->second == turn_)
                                continue;
                            capture = true;
                        }
                        auto from  = tools::get_position(pos);
                        PgnMove currentmove(from.value(), to.value(), pt, capture, \
                                ReportType::NONE);

                        moves.insert(moves.end(), currentmove);
                    }

                }
            }
        }
        return moves;
    }

    void ChessBoard::print_possible_moves(const std::list<PgnMove>& moves)
    {
        for(auto move : moves)
        {
            std::cout << move;
        }
    }

    static bool is_check_pawn(int dir, Color king)
    {
        if(king == Color::WHITE && dir > 0)
            return true;
        else if( king == Color::BLACK && dir < 0)
            return true;
        return false;
    }

    bool ChessBoard::is_check_aux(int pos, int dir, const Color kingcolor, int number)
    {
        bool check = false;
        int dest_int = pos ;
        int count = 0;
        do
        {
            count ++;
            dest_int += offset[number][dir];
            auto to = tools::get_position(dest_int);
            if(to == std::nullopt)
                return false;
            else if(board_.at(dest_int) != std::nullopt)
            {
                if(board_.at(dest_int)->second == kingcolor)     // same piece color
                    break;
                auto pt = board_.at(dest_int)->first;          //  enemy piece after here
                int pnum = utils::utype(pt);
                int direc = offset[number][dir];
                // stop after first case for king
                if(std::find(&offset[pnum][0], &offset[pnum][0]+8, direc) \
                        != &offset[pnum][0]+8)                        // checks by everything else
                {
                    if(pnum == 0)       // 'checks' by king
                        return count == 1;
                    if(pt == PieceType::PAWN)                       // checks by pawn
                        return count == 1 && is_check_pawn(direc, kingcolor);
                    check = true;
                }
                break;
            }
        }while(number == 1); /*number is 1 for 'queens' directions */
        return check;
    }


    bool ChessBoard::is_check(Color kingcolor, int position)
    {
        int pos = 0;
        bool check = false;
        if(position == 0)
        {
            for(auto const&[index, piece] : board_)
                if(piece != std::nullopt)
                    if(piece->first == PieceType::KING && piece->second == kingcolor)
                    {
                        pos = index;
                        break;
                    }
        }
        else
            pos = position;

        for(int dir = 0; dir < 8; dir++)
        {
            if(check)
                return true;
            check = check ||  is_check_aux(pos, dir, kingcolor, 1); // for other pieces
            check = check ||  is_check_aux(pos, dir, kingcolor, 4); // for knight
        }
        return check;
    }

    void ChessBoard::do_move(PgnMove move)
    {
        pvs_.push(Previous(board_, turn_, castling_, en_passant_));
        auto from = tools::get_index(move.get_start());
        auto to = tools::get_index(move.get_end());

        if(move.get_piece() == PieceType::KING) //castling
        {
            if(from == 25 || from == 95)
            {
                if(to == 27 || to == 97)
                {
                    int rookfrompos = (to == 27) ? 28 : 98;
                    int rooktopos = (to == 27) ? 26 : 96;
                    auto rook = board_[rookfrompos];
                    board_[rookfrompos] = std::nullopt;
                    board_[rooktopos] = rook;
                }
                else if(to == 23 || to == 93)
                { 
                    int rookfrompos = (to == 23) ? 21 : 91;
                    int rooktopos = (to == 23) ? 24 : 94;
                    auto rook = board_[rookfrompos];
                    board_[rookfrompos] = std::nullopt;
                    board_[rooktopos] = rook;
                }
            }
        }
        else if(move.get_piece() == PieceType::PAWN) //en_paasant or promotion
        {
            if(tools::string_from_pos(move.get_end()).compare(en_passant_)==0)
            {
                int tmp = to % 10;
                if(to >= 41 && to <= 48)
                    board_[50+tmp] = std::nullopt;
                else if (to >= 71 && to <= 78)
                    board_[60+tmp] = std::nullopt;
            }
            else if(to >= 91 && to <= 98)
            {
                board_[from] = std::nullopt;
                auto piece = move.get_promotion().value();
                auto res = std::optional(std::make_pair(piece, turn_));
                board_[to] = res;
            }
        }
        auto res = board_[from];
        board_[from] = std::nullopt;
        board_[to] = res;
        turn_ = (turn_ == Color::WHITE) ? Color::BLACK : Color::WHITE;
    }

    bool ChessBoard::is_stalemate(void)
    {
        return (all_moves_.size()==0);
    }

    bool ChessBoard::is_checkmate(Color side)
    {
        calculate_moves();
        for(auto move: all_moves_)
        {
            do_move(move);
            if(!is_check(side, 0))
            {
                undo_move();
                return false;
            }
            undo_move();
        }
        return true;
    }
}
