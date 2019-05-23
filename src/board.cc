#include "board.hh"

constexpr int direction[6] = {8, 8, 4, 4, 8, 0};  

constexpr int offset[6][8] = \
{
    { -11, -10, -9, -1, 1,  9, 10, 11 }, /* KING */
        { -11, -10, -9, -1, 1,  9, 10, 11 }, /* QUEEN */
        { -10,  -1,  1, 10, 0,  0,  0,  0 }, /* ROOK */
        { -11,  -9,  9, 11, 0,  0,  0,  0 }, /* BISHOP */
        { -21, -19,-12, -8, 8, 12, 19, 21 }, /* KNIGHT */
        {   -11,   -9,  9,  11, 0,  0,  0,  0 } // only the capture directions here!
};

constexpr bool slide[6] = { false, true, true, true, false, false };

constexpr int pawndir[4] = { 9,10,11,20};


namespace board
{
    bool ChessBoard::is_checkmove(PgnMove move, board_t board, Color turn)
    {
        board_t copy = board;
        do_move(copy, move);
        return is_check(copy, turn);
    }

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

    bool ChessBoard::valid_move(const PgnMove& move)
    {
        auto moves = possible_moves();
        auto it =  std::find(moves.begin(), moves.end(), move);
        if(it != moves.end())
        {
            if (is_checkmove(move, board_, turn_))
                return false;

            Color oppcol = (turn_ == Color::WHITE) ? Color::BLACK : Color::WHITE;

            if(is_checkmove(move, board_, oppcol))
            {
                (*it).report_set(ReportType::CHECK);
                return move.get_report() == ReportType::CHECK;
            }
            return move.get_report() == ReportType::NONE; // not a check
        }
        return false;
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
                            //FIXME
                            // handle check 
                            // handle promotion
                            // handle checkmate
                            // handle castling
                            // handle en passant
                            auto from  = tools::get_position(pos);
                            PgnMove currentmove(from.value(), to.value(), pt, capture, \
                                    ReportType::NONE);

                            moves.insert(moves.end(), currentmove);
                        }while(slide[piece_num] && (capture == false));
                    }
                }
                else
                {
                    int white = piece->second == Color::WHITE ? 1 : -1;
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
                       dest_int = pos + i * white;  
                       std::optional<Position> to = tools::get_position(dest_int);
                       if(to == std::nullopt) // out of bounds
                           continue;
                       auto dest_piece = board_[dest_int]; // optional pair of piece type and color
                       if(i%10 == 0 && dest_piece != std::nullopt)  // pawan cant move forward
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

    void ChessBoard::set_turn(Color color)
    {
        turn_ = color;
    }

    static bool is_check_pawn(int dir, Color king)
    {
        if(king == Color::WHITE && dir > 0)
            return true;
        else if( king == Color::BLACK && dir < 0)
            return true;
        return false;
    }

    static bool is_check_aux(int pos, const board_t& board, int dir, \
            const Color kingcolor, int number)
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
            else if(board.at(dest_int) != std::nullopt)
            {
                if(board.at(dest_int)->second == kingcolor)     // same piece
                    break;
                auto pt = board.at(dest_int)->first;          //  enemy piece after here
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


    bool ChessBoard::is_check(board_t& board, Color kingcolor)
    {
        bool check = false;
        for(auto const&[pos, piece] : board)
        {
            if(piece != std::nullopt)
            {
                if(piece->first == PieceType::KING && piece->second == kingcolor)
                {
                    for(int dir = 0; dir < 8; dir++)
                    {
                        if(check)
                            return true;
                        check = check ||  is_check_aux(pos, board, dir, kingcolor, 1); // for other pieces
                        check = check ||  is_check_aux(pos, board, dir, kingcolor, 4); // for knight
                    }
                    return check;
                }
            }
        }
        return false;
    }

    void ChessBoard::do_move(board_t& board, PgnMove move)
    {
        auto from = move.get_start();
        auto to = move.get_end();

        auto res = board[tools::get_index(from)];
        board[tools::get_index(from)] = std::nullopt;
        board[tools::get_index(to)] = res;
        //FIXME handle special cases later;
    }


}
