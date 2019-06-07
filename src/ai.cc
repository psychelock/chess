#include "ai.hh"

constexpr char init_setup[] = \
                            "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";

constexpr double PawnEvalWhite[8][8]=
{
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0},
    { 5.0,  5.0,  5.0,  5.0,  5.0,  5.0,  5.0,  5.0},
    { 1.0,  1.0,  2.0,  3.0,  3.0,  2.0,  1.0,  1.0},
    { 0.5,  0.5,  1.0,  2.5,  2.5,  1.0,  0.5,  0.5},
    { 0.0,  0.0,  0.0,  2.0,  2.0,  0.0,  0.0,  0.0},
    { 0.5, -0.5, -1.0,  0.0,  0.0, -1.0, -0.5,  0.5},
    { 0.5,  1.0, 1.0,  -2.0, -2.0,  1.0,  1.0,  0.5},
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0}
};

constexpr double PawnEvalBlack[8][8]=
{
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0},
    { 0.5,  1.0, 1.0,  -2.0, -2.0,  1.0,  1.0,  0.5},
    { 0.5, -0.5, -1.0,  0.0,  0.0, -1.0, -0.5,  0.5},
    { 0.0,  0.0,  0.0,  2.0,  2.0,  0.0,  0.0,  0.0},
    { 0.5,  0.5,  1.0,  2.5,  2.5,  1.0,  0.5,  0.5},
    { 1.0,  1.0,  2.0,  3.0,  3.0,  2.0,  1.0,  1.0},
    { 5.0,  5.0,  5.0,  5.0,  5.0,  5.0,  5.0,  5.0},
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0}
};

constexpr double KnightEval[8][8] =
{
    {-5.0, -4.0, -3.0, -3.0, -3.0, -3.0, -4.0, -5.0},
    {-4.0, -2.0,  0.0,  0.5,  0.5,  0.0, -2.0, -4.0},
    {-3.0,  0.5,  1.0,  1.5,  1.5,  1.0,  0.5, -3.0},
    {-3.0,  0.0,  1.5,  2.0,  2.0,  1.5,  0.0, -3.0},
    {-3.0,  0.5,  1.5,  2.0,  2.0,  1.5,  0.5, -3.0},
    {-3.0,  0.0,  1.0,  1.5,  1.5,  1.0,  0.0, -3.0},
    {-4.0, -2.0,  0.0,  0.0,  0.0,  0.0, -2.0, -4.0},
    {-5.0, -4.0, -3.0, -3.0, -3.0, -3.0, -4.0, -5.0}
};

constexpr double BishopEvalWhite[8][8] =
{
    {-2.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -2.0},
    {-1.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -1.0},
    {-1.0,  0.0,  0.5,  1.0,  1.0,  0.5,  0.0, -1.0},
    {-1.0,  0.5,  0.5,  1.0,  1.0,  0.5,  0.5, -1.0},
    {-1.0,  0.0,  1.0,  1.0,  1.0,  1.0,  0.0, -1.0},
    {-1.0,  1.0,  1.0,  1.0,  1.0,  1.0,  1.0, -1.0},
    {-1.0,  0.5,  0.0,  0.0,  0.0,  0.0,  0.5, -1.0},
    {-2.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -2.0}
};

constexpr double BishopEvalBlack[8][8] =
{
    {-2.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -2.0},
    {-1.0,  0.5,  0.0,  0.0,  0.0,  0.0,  0.5, -1.0},
    {-1.0,  1.0,  1.0,  1.0,  1.0,  1.0,  1.0, -1.0},
    {-1.0,  0.0,  1.0,  1.0,  1.0,  1.0,  0.0, -1.0},
    {-1.0,  0.5,  0.5,  1.0,  1.0,  0.5,  0.5, -1.0},
    {-1.0,  0.0,  0.5,  1.0,  1.0,  0.5,  0.0, -1.0},
    {-1.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -1.0},
    {-2.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -2.0}
};


constexpr double RookEvalWhite[8][8] =
{
    {0.0,   0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0},
    {0.5,   1.0,  1.0,  1.0,  1.0,  1.0,  1.0,  0.5},
    {-0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5},
    {-0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5},
    {-0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5},
    {-0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5},
    {-0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5},
    {0.0,   0.0,  0.0,  0.5,  0.5,  0.0,  0.0,  0.0}
};

constexpr double RookEvalBlack[8][8] =
{
    {0.0,   0.0,  0.0,  0.5,  0.5,  0.0,  0.0,  0.0},
    {-0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5},
    {-0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5},
    {-0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5},
    {-0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5},
    {-0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5},
    {0.5,   1.0,  1.0,  1.0,  1.0,  1.0,  1.0,  0.5},
    {0.0,   0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0}
};

constexpr double QueenEval[8][8] =
{
    {-2.0, -1.0, -1.0, -0.5, -0.5, -1.0, -1.0, -2.0},
    {-1.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -1.0},
    {-1.0,  0.0,  0.5,  0.5,  0.5,  0.5,  0.0, -1.0},
    {-0.5,  0.0,  0.5,  0.5,  0.5,  0.5,  0.0, -0.5},
    { 0.0,  0.0,  0.5,  0.5,  0.5,  0.5,  0.0, -0.5},
    {-1.0,  0.5,  0.5,  0.5,  0.5,  0.5,  0.0, -1.0},
    {-1.0,  0.0,  0.5,  0.0,  0.0,  0.0,  0.0, -1.0},
    {-2.0, -1.0, -1.0, -0.5, -0.5, -1.0, -1.0, -2.0}
};

constexpr double KingEvalWhite[8][8] =
{
    {-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
    {-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
    {-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
    {-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
    {-2.0, -3.0, -3.0, -4.0, -4.0, -3.0, -3.0, -2.0},
    {-1.0, -2.0, -2.0, -2.0, -2.0, -2.0, -2.0, -1.0},
    { 2.0,  2.0,  0.0,  0.0,  0.0,  0.0,  2.0,  2.0},
    { 2.0,  3.0,  1.0,  0.0,  0.0,  1.0,  3.0,  2.0}
};

constexpr double KingEvalBlack[8][8] =
{
    { 2.0,  3.0,  1.0,  0.0,  0.0,  1.0,  3.0,  2.0},
    { 2.0,  2.0,  0.0,  0.0,  0.0,  0.0,  2.0,  2.0},
    {-1.0, -2.0, -2.0, -2.0, -2.0, -2.0, -2.0, -1.0},
    {-2.0, -3.0, -3.0, -4.0, -4.0, -3.0, -3.0, -2.0},
    {-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
    {-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
    {-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
    {-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0}
};

namespace ai
{
    board::PgnMove ai (int depth, board::ChessBoard game, bool black)
    {
        auto raw_data = game.possible_moves(true);
        int bestmove = -9999;
        int i = 0;
        int index = 0;
        for(auto it = raw_data.begin(); it != raw_data.end(); it++)
        {
            game.do_move(*it);
            int val = minimax(depth -1 , game, -10000, 10000, !black);
            game.undo_move();
            if(val >= bestmove)
            {
                bestmove = val;
                index = i;
            }
            i++;
        }
        auto move =  *(std::next(raw_data.begin(), index));
        auto oppcol = (Color::WHITE == game.get_turn()) ? Color::BLACK : Color::WHITE;

        game.do_move(move);
        if(game.is_check(oppcol, 0))
        {
            if(game.is_checkmate(oppcol))
            {
                game.undo_move();
                move.report_set(ReportType::CHECKMATE);
            }
            else
            {
                game.undo_move();
                move.report_set(ReportType::CHECK);
            }
        }
        return move;
    }

    int minimax(int depth, board::ChessBoard game, int alpha, int beta, bool black)
    {
        if(depth == 0)
            return evalBoard(game);
        auto raw = game.possible_moves(true);
        if(black) // Maximizing for black pieces
        {
            int best = -9999;
            for(auto move : raw)
            {
                game.do_move(move);
                best = std::max(best, minimax(depth-1, game, alpha, beta, !black));
                game.undo_move();
                alpha = std::max(alpha, best);
                if(beta <= alpha)
                    return best;
            }
            return best;
        }
        else // Minizing for white pieces
        {
            int best = 9999;
            for(auto move : raw)
            {
                game.do_move(move);
                best = std::min(best, minimax(depth-1, game, alpha, beta, !black));
                game.undo_move();
                beta = std::min(beta, best);
                if(beta <= alpha)
                    return best;
            }
            return best;
        }
    }

    int evalBoard(board::ChessBoard game)
    {
        int total = 0;
        for(auto const& [pos, square] : game.get_board())
        {
            if(square != std::nullopt)
            {
                auto pt = square.value();
                int i = 9 - (pos/10);
                int j = (pos % 10 ) - 1;
                total += getPieceValue(pt, i , j);
            }
        }
        return total;
    }

    int getPieceValue(std::pair<board::PieceType, board::Color> pt, int x, int y)
    {
        int val = 0;
        switch(pt.first)
        {
            case (PieceType::PAWN):
                val =  10 + ((pt.second == Color::WHITE) ? PawnEvalWhite[y][x] : PawnEvalBlack[y][x]);
                break;
            case (PieceType::ROOK):
                val =  50 + ((pt.second == Color::WHITE) ? RookEvalWhite[y][x] : RookEvalBlack[y][x] );
                break;
            case (PieceType::KNIGHT):
                val =  30 + KnightEval[y][x];
                break;
            case (PieceType::BISHOP):
                val =  30 + ((pt.second == Color::WHITE) ? BishopEvalWhite[y][x] : BishopEvalBlack[y][x] );
                break;
            case (PieceType::QUEEN):
                val =  90 + QueenEval[y][x];
                break;
            default:
                val =  900 + ((pt.second == Color::WHITE) ? KingEvalWhite[y][x] : KingEvalBlack[y][x] );
                break;
        }
        return (pt.second == Color::WHITE) ? val : -val;
    }

    static File get_file_string(char a)
    {
        switch(a)
        {
            case 'a':
                return File::A;
            case 'b':
                return File::B;
            case 'c':
                return File::C;
            case 'd':
                return File::D;
            case 'e':
                return File::E;
            case 'f':
                return File::F;
            case 'g':
                return File::G;
            default:
                return File::H;
        }
    }
    static Rank get_rank_string(char a)
    {
        switch(a)
        {
            case '1':
                return Rank::ONE;
            case '2':
                return Rank::TWO;
            case '3':
                return Rank::THREE;
            case '4':
                return Rank::FOUR;
            case '5':
                return Rank::FIVE;
            case '6':
                return Rank::SIX;
            case '7':
                return Rank::SEVEN;
            default:
                return Rank::EIGHT;
        }
    }

    static PgnMove get_move(std::string move, ChessBoard board)
    {
        std::optional<PieceType> nnull = std::nullopt;
        std::optional<PieceType> queen = PieceType::QUEEN;
        auto capture = false;
        auto startfile = get_file_string(move.at(0));
        auto startrank = get_rank_string(move.at(1));
        auto endfile = get_file_string(move.at(2));
        auto endrank = get_rank_string(move.at(3));
        Position start(startfile, startrank);
        Position end(endfile, endrank);
        if(board[end] != std::nullopt)
        {
            capture = true;
        }
        auto pt = board[start].value().first;
        if((endrank == Rank::EIGHT || endrank == Rank::ONE) && (pt == PieceType::PAWN))
            return tools::create_pgnmove(startfile, startrank, endfile,\
                                        endrank, pt, capture, ReportType::NONE, queen);
        else
            return tools::create_pgnmove(startfile, startrank, endfile, \
                                        endrank, pt, capture, ReportType::NONE, nnull);
    }

    static ChessBoard parse_moves(std::string board, std::string color,\
                                    std::string castling, std::string en_passant,\
                                    std::stringstream& ss)
    {
        ChessBoard res(board);
        Color turn = (color.compare("w") == 0) ? Color::WHITE : Color::BLACK;
        res.set_turn(turn);
        res.set_castling(castling);
        res.set_en_passant(en_passant);
        std::string movestring;
        while(ss >> movestring)
        {
            auto move = get_move(movestring, res);
            res.do_move(move);
        }

        return res;
    }


    static ChessBoard parse_fen(std::stringstream& ss)
    {
        std::string board;
        std::string color;
        std::string en_passant;
        std::string castling;
        std::string ignore;
        std::string moves;
        ss >> board >> color >> castling >> en_passant >> ignore >> ignore;
        if(!ss)
        {
            ChessBoard res(board);
            Color turn = (color.compare("w") == 0) ? Color::WHITE : Color::BLACK;
            res.set_turn(turn);
            res.set_castling(castling);
            res.set_en_passant(en_passant);
            return res;
        }
        else
        {
            ss >> ignore; // the word moves
            return parse_moves(board, color, castling, en_passant, ss);
        }
    }

    static ChessBoard parse_startpos(std::stringstream& ss)
    {
        std::string word;
        if(!ss)//moves are given
            return ChessBoard (init_setup);
        else
        {
            ss >> word; // the word moves
            return parse_moves(init_setup, "w", "KQkq", "-", ss);
        }
    }

    ChessBoard parse_uci(std::string str)
    {
        std::stringstream ss(str);
        std::string word ;
        ss >> word; // always position
        ss >> word;
        if(word.compare("startpos") == 0)
        {
            return parse_startpos(ss);
        }
        else //fen
        {
            return parse_fen(ss);
        }
    }

    void engine(void)
    {
        std::string res = "";
        ai::init("Mithun");
        std::cerr << "\nbefore setup\n";
        auto str = ai::get_board();
        std::cerr << str;
        auto game = parse_uci(str);
        std::cerr << "\nafter setup\n";
        while(true)
        {
            std::cerr << "in loop\n";
            auto move = ai(2, game, game.get_turn() == Color::BLACK);
            res = res + (tools::string_from_pos(move.get_start()));
            res = res + (tools::string_from_pos(move.get_end()));
            std::cerr << move << "\n";
            std::cerr << "string : " << res << "\n";
            ai::play_move(res);
            game.calculate_moves(true);
            game.do_move(move);
            res.clear();
        }
    }

}
