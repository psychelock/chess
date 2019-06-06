#include <iostream>
#include "gtest/gtest.h"
#include "../given/pgn-move.hh"
#include "../given/chessboard-interface.hh"
#include "../board.hh"
#include "../tools.hh"


namespace test
{
    constexpr char setupking[] = "P4B2/1k2q1b1/8/6Rp/1r1Q3K/8/1R3p2/8";

    TEST(BoardKing, BoardSetup)
    {
        ChessBoard game(setupking);
        ASSERT_EQ(game.dump_board(), tools::dump_board_from_fen(setupking));
    }

    TEST(KingTest, ValidMoves) 
    {
        ChessBoard game(setupking);
        std::optional<PieceType> nnull = std::nullopt;

        PgnMove tmp1 = tools::create_pgnmove (File::H, Rank::FOUR, File::H, \
                Rank::FIVE, PieceType::KING,\
                true, ReportType::NONE, nnull);
        PgnMove tmp2 = tools::create_pgnmove (File::H, Rank::FOUR, File::H, \
                Rank::THREE, PieceType::KING,\
                false, ReportType::NONE, nnull);
        
        PgnMove tmp3 = tools::create_pgnmove (File::H, Rank::FOUR, File::G, \
                Rank::THREE, PieceType::KING,\
                false, ReportType::NONE, nnull);
        PgnMove tmp7 = tools::create_pgnmove (File::B, Rank::SEVEN, File::C, \
                Rank::EIGHT, PieceType::KING,\
                false, ReportType::NONE, nnull);
        PgnMove tmp8 = tools::create_pgnmove (File::B, Rank::SEVEN, File::C, \
                Rank::SEVEN, PieceType::KING,\
                false, ReportType::NONE, nnull);
        PgnMove tmp9 = tools::create_pgnmove (File::B, Rank::SEVEN, File::C, \
                Rank::SIX, PieceType::KING,\
                false, ReportType::NONE, nnull);


        ASSERT_EQ(game.valid_move(tmp1, true), true);
        ASSERT_EQ(game.valid_move(tmp2, true), true);
        ASSERT_EQ(game.valid_move(tmp3, true), true);

        game.set_turn(Color::BLACK);
        game.calculate_moves(true);
        ASSERT_EQ(game.valid_move(tmp7, true), true);
        ASSERT_EQ(game.valid_move(tmp8, true), true);
        ASSERT_EQ(game.valid_move(tmp9, true), true);
    
    }
    

    TEST(KingTest, CaptureMoves) 
    {
        ChessBoard game(setupking);
        std::optional<PieceType> nnull = std::nullopt;
        
        PgnMove tmp1 = tools::create_pgnmove (File::H, Rank::FOUR, File::H, \
                Rank::FIVE, PieceType::KING,\
                true, ReportType::NONE, nnull);
        PgnMove tmp2 = tools::create_pgnmove (File::B, Rank::SEVEN, File::A, \
                Rank::EIGHT, PieceType::KING,\
                true, ReportType::NONE, nnull);
        PgnMove tmp5 = tools::create_pgnmove (File::B, Rank::SEVEN, File::A, \
                Rank::EIGHT, PieceType::KING,\
                true, ReportType::NONE, nnull);

        ASSERT_EQ(game.valid_move(tmp1, true), true);
        game.set_turn(Color::BLACK);
        game.calculate_moves(true);
        ASSERT_EQ(game.valid_move(tmp2, true), true);
        ASSERT_EQ(game.valid_move(tmp5, true), true);

    }

    TEST(KingTest, InvalidMoves) 
    {
        ChessBoard game(setupking);
        std::optional<PieceType> nnull = std::nullopt;

        PgnMove tmp1 = tools::create_pgnmove (File::H, Rank::FOUR, File::G, \
                Rank::FIVE, PieceType::KING,\
                false, ReportType::NONE, nnull);
        
        PgnMove tmp2 = tools::create_pgnmove (File::B, Rank::SEVEN, File::A, \
                Rank::SEVEN, PieceType::KING,\
                false, ReportType::NONE, nnull);
        PgnMove tmp3 = tools::create_pgnmove (File::B, Rank::SEVEN, File::B, \
                Rank::SIX, PieceType::KING,\
                false, ReportType::NONE, nnull);

        ASSERT_EQ(game.valid_move(tmp1, true), false);

        game.set_turn(Color::BLACK);
        game.calculate_moves(true);

        ASSERT_EQ(game.valid_move(tmp2, true), false);
        ASSERT_EQ(game.valid_move(tmp3, true), false);
    }

    TEST(KingTest, RandomMoves) 
    {
        ChessBoard game(setupking);
        std::optional<PieceType> nnull = std::nullopt;

        PgnMove tmp1 = tools::create_pgnmove (File::H, Rank::FOUR, File::B, \
                Rank::ONE, PieceType::KING,\
                false, ReportType::NONE, nnull);
        PgnMove tmp2 = tools::create_pgnmove (File::H, Rank::FOUR, File::A, \
                Rank::TWO, PieceType::KING,\
                false, ReportType::NONE, nnull);
        PgnMove tmp3 = tools::create_pgnmove (File::H, Rank::FOUR, File::A, \
                Rank::ONE, PieceType::KING,\
                false, ReportType::NONE, nnull);
        PgnMove tmp4 = tools::create_pgnmove (File::B, Rank::SEVEN, File::A, \
                Rank::ONE, PieceType::KING,\
                false, ReportType::NONE, nnull);
        PgnMove tmp5 = tools::create_pgnmove (File::B, Rank::SEVEN, File::G, \
                Rank::SEVEN, PieceType::KING,\
                false, ReportType::NONE, nnull);
        PgnMove tmp6 = tools::create_pgnmove (File::B, Rank::SEVEN, File::H, \
                Rank::TWO, PieceType::KING,\
                false, ReportType::NONE, nnull);
    
        ASSERT_EQ(game.valid_move(tmp1, true), false);
        ASSERT_EQ(game.valid_move(tmp2, true), false);
        ASSERT_EQ(game.valid_move(tmp3, true), false);
        ASSERT_EQ(game.valid_move(tmp4, true), false);
        ASSERT_EQ(game.valid_move(tmp5, true), false);
        ASSERT_EQ(game.valid_move(tmp6, true), false);

    }

}
