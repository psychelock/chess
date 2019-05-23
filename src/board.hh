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
    using board_t = std::map<int, std::optional<std::pair<PieceType, Color>>>;
    class ChessBoard : public ChessboardInterface
    {
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
            void print_possible_moves(const std::list<PgnMove>& moves);
            bool is_check(board_t& , Color kingcolor);
            bool is_checkmove(PgnMove move, board_t board, Color turn);

            int perft_score(int depth);
            void do_move(board_t&, PgnMove);
            void undo_move(PgnMove);
            void create_board(std::string);

            opt_piece_t operator[](const Position& position) const;

            board_t get_board(void) { return board_; }
            Color get_turn(void) { return turn_; }
            void set_board(board_t board) { board_ = board; }
            void set_turn(Color color) { turn_ = color; }
            void set_castling(std::string castling) { castling_ = castling; }
            void set_en_passant(std::string enp) { en_passant_ = enp; }
            ~ChessBoard() = default;
    };
}
