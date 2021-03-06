#include <iostream>
#include "gtest/gtest.h"
#include "../given/pgn-move.hh"
#include "../given/chessboard-interface.hh"
#include "../board.hh"
#include "../tools.hh"


namespace test
{
    constexpr char setupqueen[] = "5B2/1k2q1b1/8/6R1/1r1Q3K/8/1R3p2/8";

    TEST(BoardQueen, BoardSetup)
    {
        ChessBoard game(setupqueen);
        ASSERT_EQ(game.dump_board(), tools::dump_board_from_fen(setupqueen));
    }

    TEST(QueenTest, ValidMoves) 
    {
        ChessBoard game(setupqueen);
        std::optional<PieceType> nnull = std::nullopt;

        /*std::cout << "\n";
        game.print_possible_moves(game.possible_moves(true));
        std::cout << "\n";*/

        PgnMove tmp1 = tools::create_pgnmove (File::D, Rank::FOUR, File::C,\
                Rank::FOUR, PieceType::QUEEN,\
                false, ReportType::NONE, nnull);
        PgnMove tmp5 = tools::create_pgnmove (File::D, Rank::FOUR, File::G, \
                Rank::FOUR, PieceType::QUEEN,\
                false, ReportType::NONE, nnull);


        PgnMove tmp9 = tools::create_pgnmove (File::E, Rank::SEVEN, File::C,\
                Rank::SEVEN, PieceType::QUEEN,\
                false, ReportType::NONE, nnull);
        PgnMove tmp10 = tools::create_pgnmove (File::E, Rank::SEVEN, File::F,\
                Rank::SIX, PieceType::QUEEN,\
                false, ReportType::NONE, nnull);
        PgnMove tmp11 = tools::create_pgnmove (File::E, Rank::SEVEN, File::E,\
                Rank::ONE, PieceType::QUEEN,\
                false, ReportType::NONE, nnull);
        PgnMove tmp12 = tools::create_pgnmove (File::E, Rank::SEVEN, File::C,\
                Rank::FIVE, PieceType::QUEEN,\
                false, ReportType::NONE, nnull);
        PgnMove tmp13 = tools::create_pgnmove (File::E, Rank::SEVEN, File::D,\
                Rank::EIGHT, PieceType::QUEEN,\
                false, ReportType::NONE, nnull);
        PgnMove tmp15 = tools::create_pgnmove (File::E, Rank::SEVEN, File::E,\
                Rank::EIGHT, PieceType::QUEEN,\
                false, ReportType::NONE, nnull);
        PgnMove tmp16 = tools::create_pgnmove (File::E, Rank::SEVEN, File::F,\
                Rank::SEVEN, PieceType::QUEEN,\
                false, ReportType::NONE, nnull);

        ASSERT_EQ(game.valid_move(tmp1, true), true);
        ASSERT_EQ(game.valid_move(tmp5, true), true);

        game.set_turn(Color::BLACK);
        game.calculate_moves(true);

        ASSERT_EQ(game.valid_move(tmp9, true), true);
        ASSERT_EQ(game.valid_move(tmp10, true), true);
        ASSERT_EQ(game.valid_move(tmp11, true), true);
        ASSERT_EQ(game.valid_move(tmp12, true), true);
        ASSERT_EQ(game.valid_move(tmp13, true), true);
        ASSERT_EQ(game.valid_move(tmp15, true), true);
        ASSERT_EQ(game.valid_move(tmp16, true), true);
    
    }
    

    TEST(QueenTest, CaptureMoves) 
    {
        ChessBoard game(setupqueen);
        std::optional<PieceType> nnull = std::nullopt;
        PgnMove tmp2 = tools::create_pgnmove (File::E, Rank::SEVEN, File::F, \
                Rank::EIGHT, PieceType::QUEEN,\
                true, ReportType::NONE, nnull);


        game.set_turn(Color::BLACK);
        game.calculate_moves(true);
        ASSERT_EQ(game.valid_move(tmp2, true), true);

    }

    TEST(QueenTest, InvalidMoves) 
    {
        ChessBoard game(setupqueen);
        std::optional<PieceType> nnull = std::nullopt;
        PgnMove tmp1 = tools::create_pgnmove (File::D, Rank::FOUR, File::A,\
                Rank::FOUR, PieceType::QUEEN,\
                false, ReportType::NONE, nnull);
        PgnMove tmp2 = tools::create_pgnmove (File::D, Rank::FOUR, File::F, \
                Rank::EIGHT, PieceType::QUEEN,\
                false, ReportType::NONE, nnull);
        PgnMove tmp3 = tools::create_pgnmove (File::D, Rank::FOUR, File::H, \
                Rank::FOUR, PieceType::QUEEN,\
                false, ReportType::NONE, nnull);
        PgnMove tmp4 = tools::create_pgnmove (File::D, Rank::FOUR, File::G, \
                Rank::ONE, PieceType::QUEEN,\
                false, ReportType::NONE, nnull);
        PgnMove tmp5 = tools::create_pgnmove (File::D, Rank::FOUR, File::B, \
                Rank::TWO, PieceType::QUEEN,\
                false, ReportType::NONE, nnull);


        PgnMove tmp6 = tools::create_pgnmove (File::E, Rank::SEVEN, File::B,\
                Rank::SEVEN, PieceType::QUEEN,\
                false, ReportType::NONE, nnull);
        PgnMove tmp7 = tools::create_pgnmove (File::E, Rank::SEVEN, File::G,\
                Rank::SEVEN, PieceType::QUEEN,\
                false, ReportType::NONE, nnull);
        PgnMove tmp8 = tools::create_pgnmove (File::E, Rank::SEVEN, File::H,\
                Rank::FOUR, PieceType::QUEEN,\
                false, ReportType::NONE, nnull);
        PgnMove tmp9 = tools::create_pgnmove (File::E, Rank::SEVEN, File::A,\
                Rank::THREE, PieceType::QUEEN,\
                false, ReportType::NONE, nnull);
        PgnMove tmp10 = tools::create_pgnmove (File::E, Rank::SEVEN, File::B,\
                Rank::FOUR, PieceType::QUEEN,\
                false, ReportType::NONE, nnull);
        PgnMove tmp11 = tools::create_pgnmove (File::E, Rank::SEVEN, File::A,\
                Rank::SEVEN, PieceType::QUEEN,\
                false, ReportType::NONE, nnull);

        ASSERT_EQ(game.valid_move(tmp1, true), false);
        ASSERT_EQ(game.valid_move(tmp2, true), false);
        ASSERT_EQ(game.valid_move(tmp3, true), false);
        ASSERT_EQ(game.valid_move(tmp4, true), false);
        ASSERT_EQ(game.valid_move(tmp5, true), false);
        game.set_turn(Color::BLACK);
        game.calculate_moves(true);
        ASSERT_EQ(game.valid_move(tmp6, true), false);
        ASSERT_EQ(game.valid_move(tmp7, true), false);
        ASSERT_EQ(game.valid_move(tmp8, true), false);
        ASSERT_EQ(game.valid_move(tmp9, true), false);
        ASSERT_EQ(game.valid_move(tmp10, true), false);
        ASSERT_EQ(game.valid_move(tmp11, true), false);

    }

    TEST(QueenTest, RandomMoves) 
    {
        ChessBoard game(setupqueen);
        std::optional<PieceType> nnull = std::nullopt;

        PgnMove tmp1 = tools::create_pgnmove (File::D, Rank::FOUR, File::B, \
                Rank::ONE, PieceType::QUEEN,\
                false, ReportType::NONE, nnull);
        PgnMove tmp2 = tools::create_pgnmove (File::D, Rank::FOUR, File::A, \
                Rank::TWO, PieceType::QUEEN,\
                false, ReportType::NONE, nnull);
        PgnMove tmp3 = tools::create_pgnmove (File::D, Rank::FOUR, File::A, \
                Rank::ONE, PieceType::QUEEN,\
                false, ReportType::NONE, nnull);
        PgnMove tmp4 = tools::create_pgnmove (File::E, Rank::SEVEN, File::A, \
                Rank::ONE, PieceType::QUEEN,\
                false, ReportType::NONE, nnull);
        PgnMove tmp5 = tools::create_pgnmove (File::E, Rank::SEVEN, File::G, \
                Rank::SEVEN, PieceType::QUEEN,\
                false, ReportType::NONE, nnull);
        PgnMove tmp6 = tools::create_pgnmove (File::E, Rank::SEVEN, File::H, \
                Rank::TWO, PieceType::QUEEN,\
                false, ReportType::NONE, nnull);
        ASSERT_EQ(game.valid_move(tmp1, true), false);
        ASSERT_EQ(game.valid_move(tmp2, true), false);
        ASSERT_EQ(game.valid_move(tmp3, true), false);
        game.set_turn(Color::BLACK);
        game.calculate_moves(true);
        ASSERT_EQ(game.valid_move(tmp4, true), false);
        ASSERT_EQ(game.valid_move(tmp5, true), false);
        ASSERT_EQ(game.valid_move(tmp6, true), false);

    } 
    
    TEST(QueenTest, Check)
    { 
        ChessBoard game(setupqueen);
        std::optional<PieceType> nnull = std::nullopt;

        PgnMove tmp1 = tools::create_pgnmove (File::D, Rank::FOUR, File::B, \
                Rank::FOUR, PieceType::QUEEN,\
                true, ReportType::CHECK, nnull);
        PgnMove tmp3 = tools::create_pgnmove (File::E, Rank::SEVEN, File::G, \
                Rank::FIVE, PieceType::QUEEN,\
                true, ReportType::CHECK, nnull);
        PgnMove tmp4 = tools::create_pgnmove (File::E, Rank::SEVEN, File::E, \
                Rank::FOUR, PieceType::QUEEN,\
                false, ReportType::CHECK, nnull);
        ASSERT_EQ(game.valid_move(tmp1, true), true);
        game.set_turn(Color::BLACK);
        game.calculate_moves(true);
        ASSERT_EQ(game.valid_move(tmp3, true), true);
        ASSERT_EQ(game.valid_move(tmp4, true), true);
    }



}
