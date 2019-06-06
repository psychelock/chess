#include "ai.hh"

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
        auto raw_data = game.possible_moves();
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
        if(game.is_check(oppcol, 0))
        {
            if(game.is_checkmate(oppcol))
                move.report_set(ReportType::CHECKMATE);
            else
                move.report_set(ReportType::CHECK);
        }
        return move;
    }

    int minimax(int depth, board::ChessBoard game, int alpha, int beta, bool black)
    {
        if(depth == 0)
            return evalBoard(game);
        auto raw = game.possible_moves();
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
}
