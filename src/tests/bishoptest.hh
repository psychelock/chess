#include <iostream>
#include "gtest/gtest.h"
#include "../given/pgn-move.hh"
#include "../given/chessboard-interface.hh"
#include "../board.hh"
#include "../tools.hh"


namespace test
{
    constexpr char setup[] = "B3k3/8/2n2r2/8/3Bb3/8/1R2K1P1/b7";

    TEST(Board, BoardSetup)
    {
        ChessBoard game(setup);
        ASSERT_EQ(game.dump_board(), tools::dump_board_from_fen(setup));

    }
    TEST(BishopTest, ValidMoves) 
    {
        ChessBoard game(setup);
        std::optional<PieceType> nnull = std::nullopt;

/*
        std::cout << "\n";
        game.print_possible_moves(game.possible_moves());
        std::cout << "\n";
        */

        PgnMove tmp1 = tools::create_pgnmove (File::A, Rank::EIGHT, File::B, \
                Rank::SEVEN, PieceType::BISHOP,\
                false, ReportType::NONE, nnull);
        PgnMove tmp2 = tools::create_pgnmove (File::D, Rank::FOUR, File::G, \
                Rank::ONE, PieceType::BISHOP,\
                false, ReportType::NONE, nnull);
        PgnMove tmp3 = tools::create_pgnmove (File::E, Rank::FOUR, File::H, \
                Rank::SEVEN, PieceType::BISHOP,\
                false, ReportType::NONE, nnull);
        PgnMove tmp4 = tools::create_pgnmove (File::E, Rank::FOUR, File::B, \
                Rank::ONE, PieceType::BISHOP,\
                false, ReportType::NONE, nnull);
        PgnMove tmp5 = tools::create_pgnmove (File::E, Rank::FOUR, File::D,\
                Rank::FIVE, PieceType::BISHOP,\
                false, ReportType::NONE, nnull);

        ASSERT_EQ(game.valid_move(tmp1), true);
        ASSERT_EQ(game.valid_move(tmp2), true);

        game.set_turn(Color::BLACK);
        game.calculate_moves();
        /*
        std::cout << "\n";
        game.print_possible_moves(game.possible_moves());
        std::cout << "\n";
        */

        ASSERT_EQ(game.valid_move(tmp3), true);
        ASSERT_EQ(game.valid_move(tmp4), true);
        ASSERT_EQ(game.valid_move(tmp5), true);
    
    }
    

    TEST(BishopTest, CaptureMoves) 
    {
        ChessBoard game(setup);
        std::optional<PieceType> nnull = std::nullopt;

        PgnMove tmp1 = tools::create_pgnmove (File::A, Rank::ONE, File::B, \
                Rank::TWO, PieceType::BISHOP,\
                true, ReportType::NONE, nnull);
        PgnMove tmp2 = tools::create_pgnmove (File::E, Rank::FOUR, File::G, \
                Rank::TWO, PieceType::BISHOP,\
                true, ReportType::NONE, nnull);
        PgnMove tmp4 = tools::create_pgnmove (File::D, Rank::FOUR, File::F, \
                Rank::SIX, PieceType::BISHOP,\
                true, ReportType::NONE, nnull);

        ASSERT_EQ(game.valid_move(tmp4), true);

        game.set_turn(Color::BLACK);
        game.calculate_moves();

        ASSERT_EQ(game.valid_move(tmp1), true);
        ASSERT_EQ(game.valid_move(tmp2), true);

    }

    TEST(BishopTest, InvalidMoves) 
    {
        ChessBoard game(setup);
        std::optional<PieceType> nnull = std::nullopt;

        PgnMove tmp1 = tools::create_pgnmove (File::A, Rank::ONE, File::C, \
                Rank::THREE, PieceType::BISHOP,\
                false, ReportType::NONE, nnull);
        PgnMove tmp2 = tools::create_pgnmove (File::A, Rank::ONE, File::D, \
                Rank::FOUR, PieceType::BISHOP,\
                true, ReportType::NONE, nnull);
        PgnMove tmp3 = tools::create_pgnmove (File::A, Rank::ONE, File::D, \
                Rank::FOUR, PieceType::BISHOP,\
                false, ReportType::NONE, nnull);
        PgnMove tmp4 = tools::create_pgnmove (File::E, Rank::FOUR, File::C, \
                Rank::SIX, PieceType::BISHOP,\
                false, ReportType::NONE, nnull);
        PgnMove tmp5 = tools::create_pgnmove (File::E, Rank::FOUR, File::F, \
                Rank::THREE, PieceType::BISHOP,\
                true, ReportType::NONE, nnull);
        PgnMove tmp6 = tools::create_pgnmove (File::A, Rank::EIGHT, File::D, \
                Rank::FIVE, PieceType::BISHOP,\
                false, ReportType::NONE, nnull);
        PgnMove tmp7 = tools::create_pgnmove (File::A, Rank::EIGHT, File::G, \
                Rank::TWO, PieceType::BISHOP,\
                false, ReportType::NONE, nnull);

        ASSERT_EQ(game.valid_move(tmp6), false);
        ASSERT_EQ(game.valid_move(tmp7), false);

        game.set_turn(Color::BLACK);
        game.calculate_moves();

        ASSERT_EQ(game.valid_move(tmp1), false);
        ASSERT_EQ(game.valid_move(tmp2), false);
        ASSERT_EQ(game.valid_move(tmp3), false);
        ASSERT_EQ(game.valid_move(tmp4), false);
        ASSERT_EQ(game.valid_move(tmp5), false);
    }

    TEST(BishopTest, RandomMoves) 
    {
        ChessBoard game(setup);
        std::optional<PieceType> nnull = std::nullopt;

        PgnMove tmp1 = tools::create_pgnmove (File::A, Rank::ONE, File::B, \
                Rank::ONE, PieceType::BISHOP,\
                false, ReportType::NONE, nnull);
        PgnMove tmp2 = tools::create_pgnmove (File::A, Rank::ONE, File::A, \
                Rank::TWO, PieceType::BISHOP,\
                false, ReportType::NONE, nnull);
        PgnMove tmp3 = tools::create_pgnmove (File::A, Rank::ONE, File::A, \
                Rank::ONE, PieceType::BISHOP,\
                false, ReportType::NONE, nnull);
        PgnMove tmp4 = tools::create_pgnmove (File::A, Rank::EIGHT, File::A, \
                Rank::ONE, PieceType::BISHOP,\
                false, ReportType::NONE, nnull);
        PgnMove tmp5 = tools::create_pgnmove (File::A, Rank::EIGHT, File::G, \
                Rank::SEVEN, PieceType::BISHOP,\
                false, ReportType::NONE, nnull);
        PgnMove tmp6 = tools::create_pgnmove (File::A, Rank::ONE, File::H, \
                Rank::TWO, PieceType::BISHOP,\
                false, ReportType::NONE, nnull);
    
        ASSERT_EQ(game.valid_move(tmp1), false);
        ASSERT_EQ(game.valid_move(tmp2), false);
        ASSERT_EQ(game.valid_move(tmp3), false);
        ASSERT_EQ(game.valid_move(tmp4), false);
        ASSERT_EQ(game.valid_move(tmp5), false);
        ASSERT_EQ(game.valid_move(tmp6), false);

    }

    TEST(BishopTest, Check)
    { 
        ChessBoard game(setup);
        std::optional<PieceType> nnull = std::nullopt;

        PgnMove tmp1 = tools::create_pgnmove (File::A, Rank::EIGHT, File::C, \
                Rank::SIX, PieceType::BISHOP,\
                true, ReportType::CHECK, nnull);
        PgnMove tmp2 = tools::create_pgnmove (File::E, Rank::FOUR, File::D, \
                Rank::THREE, PieceType::BISHOP,\
                false, ReportType::CHECK, nnull);
        PgnMove tmp3 = tools::create_pgnmove (File::E, Rank::FOUR, File::F, \
                Rank::THREE, PieceType::BISHOP,\
                false, ReportType::CHECK, nnull);
        ASSERT_EQ(game.valid_move(tmp1), true);
        game.set_turn(Color::BLACK);
        game.calculate_moves();
        ASSERT_EQ(game.valid_move(tmp2), true);
        ASSERT_EQ(game.valid_move(tmp3), true);
    }


}
