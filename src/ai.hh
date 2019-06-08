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
    board::PgnMove ai(int depth, board::ChessBoard game, bool black);
    int minimax(int depth, board::ChessBoard game, int alpha, int beta, bool black);
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
 
