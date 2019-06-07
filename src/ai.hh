#pragma once
#include "given/pgn-move.hh"
#include "given/color.hh"
#include "given/uci.hh"
#include "given/position.hh"
#include "given/piece-type.hh"
#include "board.hh"
#include "tools.hh"
#include <optional>
#include <string>
#include <iostream>

namespace ai
{
    board::PgnMove ai(int depth, board::ChessBoard game, bool black);
    int minimax(int depth, board::ChessBoard game, int alpha, int beta, bool black);
    int evalBoard(board::ChessBoard game);
    int getPieceValue(std::pair<PieceType, Color> pt, int x, int y);
    ChessBoard parse_uci(std::string str);
    void engine(void);
}
