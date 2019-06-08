#include <iostream>
#include "gtest/gtest.h"
#include "../given/pgn-move.hh"
#include "../given/chessboard-interface.hh"
#include "../board.hh"
#include "../tools.hh"
#include "../ai.hh"

namespace test
{
    TEST(Evalulate, Board)
    {
        ChessBoard game("n2r1n1k/3Rb3/1nq2R1N/3NP3/6B1/2K1Q3/P1q1PPP1/3R4");
        auto tmp = ai::evalBoard(game);
        std::cout << tmp;
    }
}
