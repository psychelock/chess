#include <iostream>
#include "gtest/gtest.h"
#include "../given/pgn-move.hh"
#include "../given/chessboard-interface.hh"
#include "../board.hh"
#include "../tools.hh"

namespace test
{
    constexpr char splsetup[] = "rn2k2r/8/8/1b6/8/8/8/R3K2R";

    TEST(SplBoard, BoardSetup)
    {
        ChessBoard game(splsetup);
        ASSERT_EQ(game.dump_board(), tools::dump_board_from_fen(splsetup));

    }
    TEST(SpecialTest, CastlingValidMoves) 
    {
        ChessBoard game(splsetup);
        std::optional<PieceType> nnull = std::nullopt;

        PgnMove tmp1 = tools::create_pgnmove (File::E, Rank::ONE, File::C,\
                Rank::ONE, PieceType::KING,\
                false, ReportType::NONE, nnull);

        PgnMove tmp2 = tools::create_pgnmove (File::E, Rank::EIGHT, File::G,\
                Rank::EIGHT, PieceType::KING,\
                false, ReportType::NONE, nnull);

        ASSERT_EQ(game.valid_move(tmp1), true);
        game.set_turn(Color::BLACK);
        ASSERT_EQ(game.valid_move(tmp2), true);
    }
    TEST(SpecialTest, CastlingInvalid) 
    {
        ChessBoard game(splsetup);
        std::optional<PieceType> nnull = std::nullopt;

        PgnMove tmp1 = tools::create_pgnmove (File::E, Rank::ONE, File::G,\
                Rank::ONE, PieceType::KING,\
                false, ReportType::NONE, nnull);

        PgnMove tmp2 = tools::create_pgnmove (File::E, Rank::EIGHT, File::B,\
                Rank::EIGHT, PieceType::KING,\
                false, ReportType::NONE, nnull);

        ASSERT_EQ(game.valid_move(tmp1), false);
        game.set_turn(Color::BLACK);
        ASSERT_EQ(game.valid_move(tmp2), false);
    }

}
