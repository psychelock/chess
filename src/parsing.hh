#pragma once
#include "board.hh"
#include "given/pgn-parser.hh"
#include "given/pgn-move.hh"
#include "given/pgn-exception.hh"
#include "perft.hh"
#include <fstream>
#include <optional>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
int create_chessboard_perft(std::string file);
