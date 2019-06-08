#pragma once
#include "given/pgn-move.hh"
#include "given/color.hh"
#include "given/uci.hh"
#include "given/position.hh"
#include "given/piece-type.hh"
#include "board.hh"
#include "tools.hh"
#include <optional>
#include <string>
#include <iostream>

namespace ai
{
    board::PgnMove ai(int depth, board::ChessBoard game);
    //int minimax(int depth, board::ChessBoard game, int alpha, int beta, bool black);
    int alphabeta(int alpha, int beta, int depth, ChessBoard game);
    int quiesce(int alpha, int beta, ChessBoard game);
    int evalBoard(board::ChessBoard game);
    int getPieceValue(std::pair<PieceType, Color> pt, int x, int y);
    ChessBoard parse_uci(std::string str);
    void engine(void);
}

/*        auto oppcol = (Color::WHITE == game.get_turn()) ? Color::BLACK : Color::WHITE;

        game.do_move(move);
        if(game.is_check(oppcol, 0))
        {
            if(game.is_checkmate(oppcol))
            {
                game.undo_move();
                move.report_set(ReportType::CHECKMATE);
            }
            else
            {
                game.undo_move();
                move.report_set(ReportType::CHECK);
            }
        }*/
/*
    int minimax(int depth, board::ChessBoard game, int alpha, int beta, bool black)
    {
        if(depth == 0)
        {
            auto tmp = evalBoard(game);
            if(black)
                return -tmp;
            else
                return tmp;
        }
        auto raw = game.possible_moves(true);
        if(black) // Maximizing for black pieces
        {
            int best = -9999;
            for(auto move : raw)
            {
                game.do_move(move);
                best = std::max(best, minimax(depth-1, game, alpha, beta, !black));
                game.undo_move();
                alpha = std::max(alpha, best);
                if(beta <= alpha)
                    return best;
            }
            return best;
        }
        else // Minizing for white pieces
        {
            int best = 9999;
            for(auto move : raw)
            {
                game.do_move(move);
                best = std::min(best, minimax(depth-1, game, alpha, beta, !black));
                game.undo_move();
                beta = std::min(beta, best);
                if(beta <= alpha)
                    return best;
            }
            return best;
        }
    }*/


