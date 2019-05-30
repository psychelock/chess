#include <iostream>
#include <vector>
#include "given/chessboard-interface.hh"
#include "given/pgn-move.hh"
#include "given/pgn-parser.hh"
#include "given/color.hh"
#include "given/listener.hh"
#include "tools.hh"
#include <dlfcn.h>
#include <cassert>

namespace gameloop
{
    int gameloop(ChessBoard board, std::vector<PgnMove> list);
}
