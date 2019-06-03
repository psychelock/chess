#pragma once
#include "given/pgn-move.hh"
#include "given/color.hh"
#include "board.hh"

namespace ai
{
    board::PgnMove minimaxroot (int depth, board::ChessBoard game, bool black);
    int minimax(int depth, board::ChessBoard game, int alpha, int beta, bool black);
    int evalBoard(board::ChessBoard game);
    int getPieceValue(std::pair<PieceType, Color> pt, int x, int y);
}
