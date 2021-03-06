#include <iostream>
#include "gtest/gtest.h"
#include "../given/pgn-move.hh"
#include "../given/chessboard-interface.hh"
#include "../board.hh"
#include "../tools.hh"


namespace test
{
    constexpr char setuprook[] = "n3k3/3Rbr2/1n3R1N/1r1N4/8/2K1Q3/8/8";

    TEST(BoardRook, BoardSetup)
    {
        ChessBoard game(setuprook);
        ASSERT_EQ(game.dump_board(), tools::dump_board_from_fen(setuprook));
    }

    TEST(RookTest, ValidMoves) 
    {
        ChessBoard game(setuprook);
        std::optional<PieceType> nnull = std::nullopt;


        PgnMove tmp1 = tools::create_pgnmove (File::D, Rank::SEVEN, File::D, \
                Rank::SIX, PieceType::ROOK,\
                false, ReportType::NONE, nnull);
        PgnMove tmp3 = tools::create_pgnmove (File::D, Rank::SEVEN, File::A, \
                Rank::SEVEN, PieceType::ROOK,\
                false, ReportType::NONE, nnull);
        PgnMove tmp4 = tools::create_pgnmove (File::F, Rank::SIX, File::F, \
                Rank::ONE, PieceType::ROOK,\
                false, ReportType::NONE, nnull);
        PgnMove tmp5 = tools::create_pgnmove (File::F, Rank::SIX, File::C,\
                Rank::SIX, PieceType::ROOK,\
                false, ReportType::NONE, nnull);

        PgnMove tmp6 = tools::create_pgnmove (File::F, Rank::SEVEN, File::F,\
                Rank::EIGHT, PieceType::ROOK,\
                false, ReportType::NONE, nnull);
        PgnMove tmp7 = tools::create_pgnmove (File::F, Rank::SEVEN, File::G,\
                Rank::SEVEN, PieceType::ROOK,\
                false, ReportType::NONE, nnull);
        PgnMove tmp8 = tools::create_pgnmove (File::B, Rank::FIVE, File::B,\
                Rank::ONE, PieceType::ROOK,\
                false, ReportType::NONE, nnull);
        PgnMove tmp9 = tools::create_pgnmove (File::B, Rank::FIVE, File::A,\
                Rank::FIVE, PieceType::ROOK,\
                false, ReportType::NONE, nnull);

        ASSERT_EQ(game.valid_move(tmp1, true), true);
        ASSERT_EQ(game.valid_move(tmp3, true), true);
        ASSERT_EQ(game.valid_move(tmp4, true), true);
        ASSERT_EQ(game.valid_move(tmp5, true), true);

        game.set_turn(Color::BLACK);
        game.calculate_moves(true);

        ASSERT_EQ(game.valid_move(tmp6, true), true);
        ASSERT_EQ(game.valid_move(tmp7, true), true);
        ASSERT_EQ(game.valid_move(tmp8, true), true);
        ASSERT_EQ(game.valid_move(tmp9, true), true);
    
    }
    

    TEST(RookTest, CaptureMoves) 
    {
        ChessBoard game(setuprook);
        std::optional<PieceType> nnull = std::nullopt;

        PgnMove tmp2 = tools::create_pgnmove (File::F, Rank::SIX, File::B, \
                Rank::SIX, PieceType::ROOK,\
                true, ReportType::NONE, nnull);
        PgnMove tmp3 = tools::create_pgnmove (File::F, Rank::SIX, File::F, \
                Rank::SEVEN, PieceType::ROOK,\
                true, ReportType::NONE, nnull);
        PgnMove tmp4 = tools::create_pgnmove (File::B, Rank::FIVE, File::D, \
                Rank::FIVE, PieceType::ROOK,\
                true, ReportType::NONE, nnull);


        ASSERT_EQ(game.valid_move(tmp2, true), true);
        ASSERT_EQ(game.valid_move(tmp3, true), true);
        game.set_turn(Color::BLACK);
        game.calculate_moves(true);
        ASSERT_EQ(game.valid_move(tmp4, true), true);

    }

    TEST(RookTest, InvalidMoves) 
    {
        ChessBoard game(setuprook);
        std::optional<PieceType> nnull = std::nullopt;

        PgnMove tmp1 = tools::create_pgnmove (File::D, Rank::SEVEN, File::F, \
                Rank::SEVEN, PieceType::ROOK,\
                false, ReportType::NONE, nnull);
        PgnMove tmp2 = tools::create_pgnmove (File::D, Rank::SEVEN, File::D, \
                Rank::FIVE, PieceType::ROOK,\
                true, ReportType::NONE, nnull);
        PgnMove tmp3 = tools::create_pgnmove (File::D, Rank::SEVEN, File::D, \
                Rank::FOUR, PieceType::ROOK,\
                false, ReportType::NONE, nnull);
        PgnMove tmp4 = tools::create_pgnmove (File::F, Rank::SIX, File::A, \
                Rank::SIX, PieceType::ROOK,\
                false, ReportType::NONE, nnull);
        
        PgnMove tmp5 = tools::create_pgnmove (File::F, Rank::SEVEN, File::E, \
                Rank::SEVEN, PieceType::ROOK,\
                false, ReportType::NONE, nnull);
        PgnMove tmp6 = tools::create_pgnmove (File::B, Rank::FIVE, File::E, \
                Rank::FIVE, PieceType::ROOK,\
                false, ReportType::NONE, nnull);
        PgnMove tmp7 = tools::create_pgnmove (File::B, Rank::FIVE, File::B, \
                Rank::SIX, PieceType::ROOK,\
                false, ReportType::NONE, nnull);
        PgnMove tmp8 = tools::create_pgnmove (File::B, Rank::FIVE, File::B, \
                Rank::SEVEN, PieceType::ROOK,\
                false, ReportType::NONE, nnull);


        ASSERT_EQ(game.valid_move(tmp1, true), false);
        ASSERT_EQ(game.valid_move(tmp2, true), false);
        ASSERT_EQ(game.valid_move(tmp3, true), false);
        ASSERT_EQ(game.valid_move(tmp4, true), false);
        game.set_turn(Color::BLACK);
        game.calculate_moves(true);
        ASSERT_EQ(game.valid_move(tmp5, true), false);
        ASSERT_EQ(game.valid_move(tmp6, true), false);
        ASSERT_EQ(game.valid_move(tmp7, true), false);
        ASSERT_EQ(game.valid_move(tmp8, true), false);
    }

    TEST(RookTest, RandomMoves) 
    {
        ChessBoard game(setuprook);
        std::optional<PieceType> nnull = std::nullopt;

        PgnMove tmp1 = tools::create_pgnmove (File::D, Rank::SEVEN, File::B, \
                Rank::ONE, PieceType::ROOK,\
                false, ReportType::NONE, nnull);
        PgnMove tmp2 = tools::create_pgnmove (File::D, Rank::SEVEN, File::A, \
                Rank::TWO, PieceType::ROOK,\
                false, ReportType::NONE, nnull);
        PgnMove tmp3 = tools::create_pgnmove (File::F, Rank::SIX, File::A, \
                Rank::ONE, PieceType::ROOK,\
                false, ReportType::NONE, nnull);
        PgnMove tmp4 = tools::create_pgnmove (File::B, Rank::FIVE, File::A, \
                Rank::ONE, PieceType::ROOK,\
                false, ReportType::NONE, nnull);
        PgnMove tmp5 = tools::create_pgnmove (File::B, Rank::FIVE, File::G, \
                Rank::SEVEN, PieceType::ROOK,\
                false, ReportType::NONE, nnull);
        PgnMove tmp6 = tools::create_pgnmove (File::F, Rank::SEVEN, File::H, \
                Rank::TWO, PieceType::ROOK,\
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

    TEST(RookTest, Check)
    { 
        ChessBoard game(setuprook);
        std::optional<PieceType> nnull = std::nullopt;

        PgnMove tmp1 = tools::create_pgnmove (File::D, Rank::SEVEN, File::E, \
                Rank::SEVEN, PieceType::ROOK,\
                true, ReportType::CHECK, nnull);
        PgnMove tmp2 = tools::create_pgnmove (File::B, Rank::FIVE, File::C, \
                Rank::FIVE, PieceType::ROOK,\
                false, ReportType::CHECK, nnull);


        ASSERT_EQ(game.valid_move(tmp1, true), true);
        game.set_turn(Color::BLACK);
        game.calculate_moves(true);
        /*
        std::cout << "\n";
        game.print_possible_moves(game.possible_moves(true));
        std::cout << "\n";
        */
        ASSERT_EQ(game.valid_move(tmp2, true), true);
    }

}
