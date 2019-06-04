#include <iostream>
#include "gtest/gtest.h"
#include "../given/pgn-move.hh"
#include "../given/chessboard-interface.hh"
#include "../board.hh"
#include "../tools.hh"

namespace test
{
    constexpr char splsetup[] = "rn2k2r/8/8/1b6/8/8/8/R3K2R";
    constexpr char checkmate1[] = "r6k/7p/8/3B4/8/p5K1/5B2/8";
    constexpr char checkmate2[] = "kr6/pp6/8/QN2P3/6p1/1P2q3/KP6/8";

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

        ASSERT_EQ(game.valid_move(tmp1, true), true);
        game.set_turn(Color::BLACK);
        game.calculate_moves();
        ASSERT_EQ(game.valid_move(tmp2, true), true);
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

        ASSERT_EQ(game.valid_move(tmp1, true), false);
        game.set_turn(Color::BLACK);
        game.calculate_moves();
        ASSERT_EQ(game.valid_move(tmp2, true), false);
    }
    TEST(SpecialTest, Checkmate)
    {
        ChessBoard game1(checkmate1);
        ChessBoard game2(checkmate2);
        std::optional<PieceType> nnull = std::nullopt;

        PgnMove tmp1 = tools::create_pgnmove(File::F, Rank::TWO, File::D,\
                Rank::FOUR, PieceType::BISHOP,\
                false, ReportType::CHECKMATE, nnull);
        PgnMove tmp2 = tools::create_pgnmove(File::B, Rank::FIVE, File::C,\
                Rank::SEVEN, PieceType::KNIGHT,\
                false, ReportType::CHECKMATE, nnull);
        
        ASSERT_EQ(game1.valid_move(tmp1, true), true);
        ASSERT_EQ(game2.valid_move(tmp2, true), true);
    }
}
