#include <iostream>
#include "gtest/gtest.h"
#include "../given/pgn-move.hh"
#include "../given/chessboard-interface.hh"
#include "../board.hh"
#include "../tools.hh"


namespace test
{
    constexpr char setupknight[] = "n7/3Rb3/1n3R1N/3N4/8/2K1Q3/8/8";

    TEST(BoardKnight, BoardSetup)
    {
        ChessBoard game(setupknight);
        ASSERT_EQ(game.dump_board(), tools::dump_board_from_fen(setupknight));
    }

    TEST(KnightTest, ValidMoves)
    {
        ChessBoard game(setupknight);
        std::optional<PieceType> nnull = std::nullopt;


        PgnMove tmp1 = tools::create_pgnmove (File::D, Rank::FIVE, File::F, \
                Rank::FOUR, PieceType::KNIGHT,\
                false, ReportType::NONE, nnull);
        PgnMove tmp2 = tools::create_pgnmove (File::D, Rank::FIVE, File::B, \
                Rank::FOUR, PieceType::KNIGHT,\
                false, ReportType::NONE, nnull);
        PgnMove tmp3 = tools::create_pgnmove (File::H, Rank::SIX, File::F, \
                Rank::SEVEN, PieceType::KNIGHT,\
                false, ReportType::NONE, nnull);
        PgnMove tmp4 = tools::create_pgnmove (File::H, Rank::SIX, File::F, \
                Rank::FIVE, PieceType::KNIGHT,\
                false, ReportType::NONE, nnull);


        PgnMove tmp5 = tools::create_pgnmove (File::A, Rank::EIGHT, File::C,\
                Rank::SEVEN, PieceType::KNIGHT,\
                false, ReportType::NONE, nnull);
        PgnMove tmp6 = tools::create_pgnmove (File::B, Rank::SIX, File::C,\
                Rank::FOUR, PieceType::KNIGHT,\
                false, ReportType::NONE, nnull);

        ASSERT_EQ(game.valid_move(tmp1, true), true);
        ASSERT_EQ(game.valid_move(tmp2, true), true);
        ASSERT_EQ(game.valid_move(tmp3, true), true);
        ASSERT_EQ(game.valid_move(tmp4, true), true);

        game.set_turn(Color::BLACK);
        game.calculate_moves();
        ASSERT_EQ(game.valid_move(tmp5, true), true);
        ASSERT_EQ(game.valid_move(tmp6, true), true);
    }

    TEST(KnightTest, CaptureMoves)
    {
        ChessBoard game(setupknight);
        std::optional<PieceType> nnull = std::nullopt;

        PgnMove tmp1 = tools::create_pgnmove (File::D, Rank::FIVE, File::B, \
                Rank::SIX, PieceType::KNIGHT,\
                true, ReportType::NONE, nnull);
        PgnMove tmp2 = tools::create_pgnmove (File::B, Rank::SIX, File::D, \
                Rank::SEVEN, PieceType::KNIGHT,\
                true, ReportType::NONE, nnull);


        ASSERT_EQ(game.valid_move(tmp1, true), true);
        game.set_turn(Color::BLACK);
        game.calculate_moves();
        /*std::cout << "\n";
        game.print_possible_moves(game.possible_moves());
        std::cout << "\n";*/
        ASSERT_EQ(game.valid_move(tmp2, true), true);

    }

    TEST(KnightTest, InvalidMoves)
    {
        ChessBoard game(setupknight);
        std::optional<PieceType> nnull = std::nullopt;

        PgnMove tmp1 = tools::create_pgnmove (File::D, Rank::FIVE, File::C, \
                Rank::THREE, PieceType::KNIGHT,\
                false, ReportType::NONE, nnull);
        PgnMove tmp2 = tools::create_pgnmove (File::D, Rank::FIVE, File::E, \
                Rank::THREE, PieceType::KNIGHT,\
                true, ReportType::NONE, nnull);
        PgnMove tmp3 = tools::create_pgnmove (File::D, Rank::FIVE, File::F, \
                Rank::SIX, PieceType::KNIGHT,\
                false, ReportType::NONE, nnull);
        PgnMove tmp4 = tools::create_pgnmove (File::B, Rank::SIX, File::A, \
                Rank::EIGHT, PieceType::KNIGHT,\
                false, ReportType::NONE, nnull);


        ASSERT_EQ(game.valid_move(tmp1, true), false);
        ASSERT_EQ(game.valid_move(tmp2, true), false);
        ASSERT_EQ(game.valid_move(tmp3, true), false);
        game.set_turn(Color::BLACK);
        game.calculate_moves();
        ASSERT_EQ(game.valid_move(tmp4, true), false);
    }

    TEST(KnightTest, RandomMoves)
    {
        ChessBoard game(setupknight);
        std::optional<PieceType> nnull = std::nullopt;

        PgnMove tmp1 = tools::create_pgnmove (File::D, Rank::FIVE, File::B, \
                Rank::ONE, PieceType::KNIGHT,\
                false, ReportType::NONE, nnull);
        PgnMove tmp2 = tools::create_pgnmove (File::D, Rank::FIVE, File::A, \
                Rank::TWO, PieceType::KNIGHT,\
                false, ReportType::NONE, nnull);
        PgnMove tmp3 = tools::create_pgnmove (File::H, Rank::SIX, File::A, \
                Rank::ONE, PieceType::KNIGHT,\
                false, ReportType::NONE, nnull);
        PgnMove tmp4 = tools::create_pgnmove (File::B, Rank::SIX, File::A, \
                Rank::ONE, PieceType::KNIGHT,\
                false, ReportType::NONE, nnull);
        PgnMove tmp5 = tools::create_pgnmove (File::B, Rank::SIX, File::G, \
                Rank::SEVEN, PieceType::KNIGHT,\
                false, ReportType::NONE, nnull);
        PgnMove tmp6 = tools::create_pgnmove (File::A, Rank::EIGHT, File::H, \
                Rank::TWO, PieceType::KNIGHT,\
                false, ReportType::NONE, nnull);
        ASSERT_EQ(game.valid_move(tmp1, true), false);
        ASSERT_EQ(game.valid_move(tmp2, true), false);
        ASSERT_EQ(game.valid_move(tmp3, true), false);
        game.set_turn(Color::BLACK);
        game.calculate_moves();
        ASSERT_EQ(game.valid_move(tmp4, true), false);
        ASSERT_EQ(game.valid_move(tmp5, true), false);
        ASSERT_EQ(game.valid_move(tmp6, true), false);

    }

    TEST(KnightTest, Check)
    {

        ChessBoard game(setupknight);
        std::optional<PieceType> nnull = std::nullopt;

        PgnMove tmp1 = tools::create_pgnmove (File::B, Rank::SIX, File::A, \
                Rank::FOUR, PieceType::KNIGHT,\
                false, ReportType::CHECK, nnull);
        PgnMove tmp2 = tools::create_pgnmove (File::B, Rank::SIX, File::D, \
                Rank::FIVE, PieceType::KNIGHT,\
                true, ReportType::CHECK, nnull);
        game.set_turn(Color::BLACK);
        game.calculate_moves();
        ASSERT_EQ(game.valid_move(tmp1, true), true);
        ASSERT_EQ(game.valid_move(tmp2, true), true);
    }

}
