#include "ai.hh"

constexpr char init_setup[] = \
                            "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";

constexpr double PawnEval[8][8]=
{
    { 0,  0,  0,  0,  0,  0,  0,  0},
    {50, 50, 50, 50, 50, 50, 50, 50},
    {10, 10, 20, 30, 30, 20, 10, 10},
    { 5,  5, 10, 25, 25, 10,  5,  5},
    { 0,  0,  0, 20, 20,  0,  0,  0},
    { 5, -5,-10,  0,  0,-10, -5,  5},
    { 5, 10, 10,-20,-20, 10, 10,  5},
    { 0,  0,  0,  0,  0,  0,  0,  0}
};

constexpr double KnightEval[8][8] =
{
    {-50,-40,-30,-30,-30,-30,-40,-50},
    {-40,-20,  0,  0,  0,  0,-20,-40},
    {-30,  0, 10, 15, 15, 10,  0,-30},
    {-30,  5, 15, 20, 20, 15,  5,-30},
    {-30,  0, 15, 20, 20, 15,  0,-30},
    {-30,  5, 10, 15, 15, 10,  5,-30},
    {-40,-20,  0,  5,  5,  0,-20,-40},
    {-50,-40,-30,-30,-30,-30,-40,-50},
};

constexpr double BishopEval[8][8] =
{
    {-20,-10,-10,-10,-10,-10,-10,-20},
    {-10,  0,  0,  0,  0,  0,  0,-10},
    {-10,  0,  5, 10, 10,  5,  0,-10},
    {-10,  5,  5, 10, 10,  5,  5,-10},
    {-10,  0, 10, 10, 10, 10,  0,-10},
    {-10, 10, 10, 10, 10, 10, 10,-10},
    {-10,  5,  0,  0,  0,  0,  5,-10},
    {-20,-10,-10,-10,-10,-10,-10,-20},
};

constexpr double RookEval[8][8] =
{
    { 0,  0,  0,  0,  0,  0,  0,  0},
    { 5, 10, 10, 10, 10, 10, 10,  5},
    {-5,  0,  0,  0,  0,  0,  0, -5},
    {-5,  0,  0,  0,  0,  0,  0, -5},
    {-5,  0,  0,  0,  0,  0,  0, -5},
    {-5,  0,  0,  0,  0,  0,  0, -5},
    {-5,  0,  0,  0,  0,  0,  0, -5},
    { 0,  0,  0,  5,  5,  0,  0,  0}
};

constexpr double QueenEval[8][8] =
{
    {-20,-10,-10, -5, -5,-10,-10,-20},
    {-10,  0,  0,  0,  0,  0,  0,-10},
    {-10,  0,  5,  5,  5,  5,  0,-10},
    { -5,  0,  5,  5,  5,  5,  0, -5},
    {  0,  0,  5,  5,  5,  5,  0, -5},
    {-10,  5,  5,  5,  5,  5,  0,-10},
    {-10,  0,  5,  0,  0,  0,  0,-10},
    {-20,-10,-10, -5, -5,-10,-10,-20}

};

constexpr double KingEval[8][8] =
{
    {-30,-40,-40,-50,-50,-40,-40,-30},
    {-30,-40,-40,-50,-50,-40,-40,-30},
    {-30,-40,-40,-50,-50,-40,-40,-30},
    {-30,-40,-40,-50,-50,-40,-40,-30},
    {-20,-30,-30,-40,-40,-30,-30,-20},
    {-10,-20,-20,-20,-20,-20,-20,-10},
    { 20, 20,  0,  0,  0,  0, 20, 20},
    { 20, 30, 10,  0,  0, 10, 30, 20}
};

namespace ai
{
    board::PgnMove ai (int depth, board::ChessBoard game)
    {
        auto raw_data = game.possible_moves(true);
        int bestmove = -99999999;
        int i = 0;
        int index = 0;
        for(auto it = raw_data.begin(); it != raw_data.end(); it++)
        {
            game.do_move(*it);
            int val = -alphabeta(-10000, 10000, depth -1,  game);
            game.undo_move();
            if(val >= bestmove)
            {
                bestmove = val;
                index = i;
            }
            i++;
        }
        auto move =  *(std::next(raw_data.begin(), index));
        return move;
    }

    int alphabeta(int alpha, int beta, int depth, ChessBoard game)
    {
        int best = -99999999;
        if(depth == 0)
        {
            if(Color::BLACK == game.get_turn())
                return -evalBoard(game);
            else
                return evalBoard(game);
        }
        auto raw = game.possible_moves(true);
        if(raw.size() == 0) // pat or a mat
        {
            if(game.is_check(game.get_turn(), 0))
                return best - depth;
            else
                return 0;
        }
        for(auto move : raw)
        {
            game.do_move(move);
            auto score = -alphabeta(-beta, -alpha, depth-1, game);
            game.undo_move();
            if(score >= beta)
                return score;
            if(score > best)
            {
                best = score;
                if(score > alpha)
                    alpha = score;
            }
        }
        return best;
    }

    int quiesce(int alpha, int beta, ChessBoard game)
    {
        int stand_pat = evalBoard(game);
        if(Color::BLACK == game.get_turn())
            stand_pat = -stand_pat;

        if(stand_pat >= beta)
            return beta;
        if(alpha < stand_pat)
            return stand_pat;
        auto raw = game.possible_moves(true);
        for(auto move : raw)
        {
            if(move.get_capture())
            {
                game.do_move(move);
                auto score = -quiesce( -beta, -alpha, game);
                game.undo_move();
                if(score >= beta)
                    return beta;
                if(score > alpha)
                    alpha = score;
            }
        }
        return alpha;
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
                total += getPieceValue(pt, i, j);
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
                val =  100 + ((pt.second == Color::WHITE) ? PawnEval[x][y] : PawnEval[7-x][y]);
                break;
            case (PieceType::ROOK):
                val =  500 + ((pt.second == Color::WHITE) ? RookEval[x][y] : RookEval[7-x][y] );
                break;
            case (PieceType::KNIGHT):
                val =  320 + KnightEval[x][y];
                break;
            case (PieceType::BISHOP):
                val =  330 + ((pt.second == Color::WHITE) ? BishopEval[x][y] : BishopEval[7-x][y] );
                break;
            case (PieceType::QUEEN):
                val =  900 + QueenEval[x][y];
                break;
            default:
                val =  20000 + ((pt.second == Color::WHITE) ? KingEval[x][y] : KingEval[7-x][y] );
                break;
        }
        val = (Color::WHITE == pt.second) ? val : -val;
        return val;
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
        while(true)
        {
            auto str = ai::get_board();
            auto game = parse_uci(str);
            auto move = ai(2, game);
            res = res + (tools::string_from_pos(move.get_start()));
            res = res + (tools::string_from_pos(move.get_end()));
            ai::play_move(res);
            game.calculate_moves(true);
            game.do_move(move);
            res.clear();
        }
    }

}
