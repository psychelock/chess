#include <chrono>
#include <iostream>
#include "gtest/gtest.h"
#include "../given/pgn-move.hh"
#include "../given/chessboard-interface.hh"
#include "../board.hh"
#include "../tools.hh"

using namespace board;

namespace test
{
    
    TEST(PawnTest, ValidSingleStep) 
    {
        ChessBoard game(setup);

        std::optional<PieceType> nnull = std::nullopt;


        PgnMove tmp1 = tools::create_pgnmove (File::A, Rank::TWO, File::A, \
                Rank::THREE, PieceType::PAWN,\
                false, ReportType::NONE, nnull);
        PgnMove tmp2 = tools::create_pgnmove (File::B, Rank::TWO, File::B, \
                Rank::THREE, PieceType::PAWN,\
                false, ReportType::NONE, nnull);
        PgnMove tmp3 = tools::create_pgnmove (File::H, Rank::TWO, File::H, \
                Rank::THREE, PieceType::PAWN,\
                false, ReportType::NONE, nnull);
        
        ASSERT_EQ(game.valid_move(tmp1), true);
        ASSERT_EQ(game.valid_move(tmp2), true);
        ASSERT_EQ(game.valid_move(tmp3), true);
    
    }
    
    TEST(PawnTest, ValidDoubleStep) 
    {
        ChessBoard game(setup);
        std::optional<PieceType> nnull = std::nullopt;
        PgnMove tmp = tools::create_pgnmove (File::A, Rank::TWO, File::A, \
                Rank::FOUR, PieceType::PAWN,\
                false, ReportType::NONE, nnull);

        ASSERT_EQ(game.valid_move(tmp), true);
    
    }

    TEST(PawnTest, InvalidStep) 
    {
        ChessBoard game(setup);
        std::optional<PieceType> nnull = std::nullopt;
        PgnMove tmp1 = tools::create_pgnmove (File::A, Rank::TWO, File::A, \
                Rank::FIVE, PieceType::PAWN,\
                false, ReportType::NONE, nnull);
        PgnMove tmp2 = tools::create_pgnmove (File::A, Rank::TWO, File::B, \
                Rank::TWO, PieceType::PAWN,\
                false, ReportType::NONE, nnull);
        
        ASSERT_EQ(game.valid_move(tmp1), false);
        ASSERT_EQ(game.valid_move(tmp2), false);
    
    }
}
