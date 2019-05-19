#pragma once
#include "given/chessboard-interface.hh"
#include "given/pgn-move.hh"
#include "given/pgn-parser.hh"
#include "given/color.hh"
#include "tools.hh"

#include <map>
#include <list>
#include <string>
#include <memory>
#include <algorithm>
#include <iostream>


namespace board
{
    class ChessBoard : public ChessboardInterface
    {
        using board_t = std::map<int, opt_piece_t>;
        private:
            board_t board_;
            Color turn_;
            std::string castling_;
            std::string en_passant_;
            //std::list<Piece> piece_list_;

        public:
            ChessBoard(std::string setup);
            
            opt_piece_t create_piece(char c);
            std::string dump_board();

            bool valid_move(const PgnMove&);
            std::list<PgnMove> possible_moves(void);
            void set_turn(Color);
            int perft_score(int depth);
            void do_move(PgnMove);
            void undo_move(PgnMove);
            void create_board(std::string);
            void print_possible_moves(const std::list<PgnMove>& moves);

            opt_piece_t operator[](const Position& position) const;

            ~ChessBoard() = default;
    };
}
