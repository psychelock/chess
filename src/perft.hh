#pragma once
#include <list>
#include "given/pgn-move.hh"
#include "board.hh"

int perft(ChessBoard&, const std::list<PgnMove>&, const int& depth);
