#pragma once
#include "given/pgn-move.hh"
#include "given/color.hh"
#include "board.hh"
#include "tools.hh"
#include <optional>

namespace ai
{
    std::optional<board::PgnMove> ai(int depth, board::ChessBoard game, bool black);
    int minimax(int depth, board::ChessBoard game, int alpha, int beta, bool black);
    int evalBoard(board::ChessBoard game);
    int getPieceValue(std::pair<PieceType, Color> pt, int x, int y);
}
