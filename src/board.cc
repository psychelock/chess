#include "board.hh"

constexpr int direction[6] = {8, 8, 4, 4, 8, 0};  

constexpr int offset[6][8] = \
{
    { -11, -10, -9, -1, 1,  9, 10, 11 },  /* KING */
        { -11, -10, -9, -1, 1,  9, 10, 11 }, /* QUEEN */
        { -10,  -1,  1, 10, 0,  0,  0,  0 }, /* ROOK */
        { -11,  -9,  9, 11, 0,  0,  0,  0 }, /* BISHOP */
        { -21, -19,-12, -8, 8, 12, 19, 21 }, /* KNIGHT */
        {   0,   0,  0,  0, 0,  0,  0,  0 }
};

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
        return it != moves.end();
    }


    std::list<PgnMove> ChessBoard::possible_moves(void)
    {
        std::list<PgnMove> moves;
        bool capture;
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
                        int dest_int = pos;
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
                        }while((pt == PieceType::BISHOP ||  \
                                pt == PieceType::ROOK || pt == PieceType::QUEEN \
                               ) && (capture == false));
                    }
                }
                else
                    continue;
                // add pawn moves here
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

}
