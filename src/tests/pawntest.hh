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
    constexpr char setuppawn[] = "rnbqk1nr/pppp3p/2P5/4pp2/3P1P1b/6p1/PP2P1PP/RNBQKBNR";

    TEST(BoardPawn, BoardSetup)
    {
        ChessBoard game(setuppawn);
        ASSERT_EQ(game.dump_board(), tools::dump_board_from_fen(setuppawn));
    }

    TEST(PawnTest, ValidSingleStep) 
    {
        ChessBoard game(setuppawn);

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
        PgnMove tmp4 = tools::create_pgnmove (File::D, Rank::FOUR, File::D, \
                Rank::FIVE, PieceType::PAWN,\
                false, ReportType::NONE, nnull);
        PgnMove tmp5 = tools::create_pgnmove (File::E, Rank::FIVE, File::E, \
                Rank::FOUR, PieceType::PAWN,\
                false, ReportType::NONE, nnull);
        PgnMove tmp6 = tools::create_pgnmove (File::B, Rank::SEVEN, File::B, \
                Rank::SIX, PieceType::PAWN,\
                false, ReportType::NONE, nnull);
                /*
           std::cout << "\n";
           game.print_possible_moves(game.possible_moves());
           std::cout << "\n";
           */

        ASSERT_EQ(game.valid_move(tmp1), true);
        ASSERT_EQ(game.valid_move(tmp2), true);
        ASSERT_EQ(game.valid_move(tmp3), true);
        ASSERT_EQ(game.valid_move(tmp4), true);

        game.set_turn(Color::BLACK);
        game.calculate_moves();

        ASSERT_EQ(game.valid_move(tmp5), true);
        ASSERT_EQ(game.valid_move(tmp6), true);

    }

    TEST(PawnTest, ValidDoubleStep) 
    {
        ChessBoard game(setuppawn);
        std::optional<PieceType> nnull = std::nullopt;
        PgnMove tmp = tools::create_pgnmove (File::A, Rank::TWO, File::A, \
                Rank::FOUR, PieceType::PAWN,\
                false, ReportType::NONE, nnull);
        PgnMove tmp1 = tools::create_pgnmove (File::E, Rank::TWO, File::E, \
                Rank::FOUR, PieceType::PAWN,\
                false, ReportType::NONE, nnull);
        PgnMove tmp2 = tools::create_pgnmove (File::B, Rank::SEVEN, File::B, \
                Rank::FIVE, PieceType::PAWN,\
                false, ReportType::NONE, nnull);
        PgnMove tmp3 = tools::create_pgnmove (File::H, Rank::SEVEN, File::H, \
                Rank::FIVE, PieceType::PAWN,\
                false, ReportType::NONE, nnull);

        ASSERT_EQ(game.valid_move(tmp), true);
        ASSERT_EQ(game.valid_move(tmp1), true);

        game.set_turn(Color::BLACK);
        game.calculate_moves();

        ASSERT_EQ(game.valid_move(tmp2), true);
        ASSERT_EQ(game.valid_move(tmp3), true);

    }

    TEST(PawnTest, InvalidStep) 
    {
        ChessBoard game(setuppawn);
        std::optional<PieceType> nnull = std::nullopt;
        PgnMove tmp1 = tools::create_pgnmove (File::A, Rank::TWO, File::A, \
                Rank::FIVE, PieceType::PAWN,\
                false, ReportType::NONE, nnull);
        PgnMove tmp2 = tools::create_pgnmove (File::A, Rank::TWO, File::B, \
                Rank::TWO, PieceType::PAWN,\
                false, ReportType::NONE, nnull);
        PgnMove tmp3 = tools::create_pgnmove (File::G, Rank::TWO, File::G, \
                Rank::THREE, PieceType::PAWN,\
                false, ReportType::NONE, nnull);
        PgnMove tmp4 = tools::create_pgnmove (File::C, Rank::SEVEN, File::C, \
                Rank::SIX, PieceType::PAWN,\
                false, ReportType::NONE, nnull);
        PgnMove tmp5 = tools::create_pgnmove (File::G, Rank::THREE, File::G, \
                Rank::TWO, PieceType::PAWN,\
                false, ReportType::NONE, nnull);
        PgnMove tmp6 = tools::create_pgnmove (File::F, Rank::SEVEN, File::F, \
                Rank::SIX, PieceType::PAWN,\
                false, ReportType::NONE, nnull);
        PgnMove tmp7 = tools::create_pgnmove (File::F, Rank::SEVEN, File::F, \
                Rank::FIVE, PieceType::PAWN,\
                false, ReportType::NONE, nnull);

        ASSERT_EQ(game.valid_move(tmp1), false);
        ASSERT_EQ(game.valid_move(tmp2), false);
        ASSERT_EQ(game.valid_move(tmp3), false);
        ASSERT_EQ(game.valid_move(tmp4), false);

        game.set_turn(Color::BLACK);
        game.calculate_moves();

        ASSERT_EQ(game.valid_move(tmp5), false);
        ASSERT_EQ(game.valid_move(tmp6), false);
        ASSERT_EQ(game.valid_move(tmp7), false);

    }

    TEST(PawnTest, Capture) 
    {
        ChessBoard game(setuppawn);
        std::optional<PieceType> nnull = std::nullopt;
        PgnMove tmp1 = tools::create_pgnmove (File::D, Rank::FOUR, File::E, \
                Rank::FIVE, PieceType::PAWN,\
                true, ReportType::NONE, nnull);
        PgnMove tmp2 = tools::create_pgnmove (File::F, Rank::FOUR, File::E, \
                Rank::FIVE, PieceType::PAWN,\
                true, ReportType::NONE, nnull);
        PgnMove tmp3 = tools::create_pgnmove (File::E, Rank::FIVE, File::F, \
                Rank::FOUR, PieceType::PAWN,\
                true, ReportType::NONE, nnull);
        PgnMove tmp4 = tools::create_pgnmove (File::D, Rank::SEVEN, File::C, \
                Rank::SIX, PieceType::PAWN,\
                true, ReportType::NONE, nnull);

        ASSERT_EQ(game.valid_move(tmp1), true);
        ASSERT_EQ(game.valid_move(tmp2), true);

        game.set_turn(Color::BLACK);
        game.calculate_moves();

        ASSERT_EQ(game.valid_move(tmp3), true);
        ASSERT_EQ(game.valid_move(tmp4), true);
    }

    TEST(PawnTest, Check) 
    {
        ChessBoard game(setuppawn);
        std::optional<PieceType> nnull = std::nullopt;
        PgnMove tmp1 = tools::create_pgnmove (File::C, Rank::SIX, File::D, \
                Rank::SEVEN, PieceType::PAWN,\
                true, ReportType::CHECK, nnull);
        PgnMove tmp2 = tools::create_pgnmove (File::G, Rank::THREE, File::H, \
                Rank::TWO, PieceType::PAWN,\
                true, ReportType::CHECK, nnull);

        ASSERT_EQ(game.valid_move(tmp1), true);

        game.set_turn(Color::BLACK);
        game.calculate_moves();

        ASSERT_EQ(game.valid_move(tmp2), true);

    }
}
