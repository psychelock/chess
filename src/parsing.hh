#pragma once
#include "board.hh"
#include "given/pgn-parser.hh"
#include "given/pgn-move.hh"
#include "given/pgn-exception.hh"

#include <fstream>
#include <optional>
#include <vector>

std::optional<ChessBoard> create_chessboard_perft(std::string file);
std::optional<ChessBoard> create_chessboard_pgn(std::string file);
