#pragma once
#include "given/chessboard-interface.hh"
#include "given/pgn-move.hh"
#include "given/color.hh"

namespace ai
{
    PgnMove minimaxroot (int depth, ChessBoard game, bool black);
    int minimax(int depth, ChessBoard game, int alpha, int beta, bool black);
    int evalBoard(ChessBoard game);
    int getPieceValue(std::pait<PieceType, Color> pt, int x, int y);
}
