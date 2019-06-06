#pragma once
#include "board.hh"
#include "given/pgn-move.hh"
#include <fstream>
#include <list>
#include <iostream>
#include <algorithm>
#include <array>
using namespace board;
namespace tools
{
    char get_char(std::optional<std::pair<board::PieceType, board::Color>> t);
    std::string dump_board_from_fen(std::string fen);
    PgnMove create_pgnmove (File f1, Rank r1, File f2, Rank r2,\
            PieceType type,\
            bool capture, ReportType report, PgnMove::opt_piece_t& promotion);
    std::optional<Position> get_position(int);
    char get_char(PieceType p);
    int get_index(Position p);
    std::string string_from_pos(Position p);
    std::string string_from_int(int pos);
}
