#include <chrono>
#include <iostream>
#include "gtest/gtest.h"
#include "given/pgn-move.hh"
#include "given/chessboard-interface.hh"
#include "board.hh"

using namespace board;

namespace test
{
    
    TEST(PawnTest, ValidSingleStep) 
    {
        ChessBoard board(setup);
        PgnMove tmp1 = create_pgnmove (File::A, Rank::TWO, File::A, \
                Rank::THREE, PieceType::PAWN,\
                false, ReportType::NONE, nullopt);
        PgnMove tmp2 = create_pgnmove (File::B, Rank::TWO, File::B, \
                Rank::THREE, PieceType::PAWN,\
                false, ReportType::NONE, nullopt);
        PgnMove tmp3 = create_pgnmove (File::H, Rank::TWO, File::H, \
                Rank::THREE, PieceType::PAWN,\
                false, ReportType::NONE, nullopt);
        
        ASSERT_EQ(valid_move(tmp1), true);
        ASSERT_EQ(valid_move(tmp2), true);
        ASSERT_EQ(valid_move(tmp3), true);
    
    }
    
    TEST(PawnTest, ValidDoubleStep) 
    {
        ChessBoard board(setup);
        PgnMove tmp = create_pgnmove (File::A, Rank::TWO, File::A, \
                Rank::FOUR, PieceType::PAWN,\
                false, ReportType::NONE, nullopt);

        ASSERT_EQ(valid_move(tmp), true);
    
    }

    TEST(PawnTest, InvalidStep) 
    {
        ChessBoard board(setup);
        PgnMove tmp1 = create_pgnmove (File::A, Rank::TWO, File::A, \
                Rank::FIVE, PieceType::PAWN,\
                false, ReportType::NONE, nullopt);
        PgnMove tmp2 = create_pgnmove (File::A, Rank::TWO, File::B, \
                Rank::TWO, PieceType::PAWN,\
                false, ReportType::NONE, nullopt);
        
        ASSERT_EQ(valid_move(tmp1), false);
        ASSERT_EQ(valid_move(tmp2), false);
    
    }

    int main (int argc, char *argv[])
    {
        testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    }
}
