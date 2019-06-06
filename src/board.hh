#pragma once
#include "given/chessboard-interface.hh"
#include "given/pgn-move.hh"
#include "given/pgn-parser.hh"
#include "given/color.hh"
#include "tools.hh"
#include "helper.hh"


#include <map>
#include <list>
#include <string>
#include <optional>
#include <memory>
#include <algorithm>
#include <iostream>
#include <stack>

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
            std::list<PgnMove> all_moves_;
            std::stack<Previous> pvs_;

        public:
            ChessBoard(std::string setup);
            opt_piece_t create_piece(char c);
            std::string dump_board();

            bool valid_move(const PgnMove&, bool test = false);
            void create_board(std::string);
            std::list<PgnMove> possible_moves(bool reduce);
            std::list<PgnMove> reduce_possible(std::list<PgnMove> list);
            void print_possible_moves(const std::list<PgnMove>& moves);
            bool is_check_aux(int pos, int dir, const Color kingcolor, int number);
            bool is_check(Color kingcolor, int position);
            std::optional<PgnMove> add_castling_aux(int pos, int side);
            std::list<PgnMove> add_castling(int pos, std::list<PgnMove> moves);
            bool is_checkmate(Color opp);
            bool is_stalemate(void);

            int perft_score(int depth);
            void do_move(PgnMove);
            void undo_move(void);

            opt_piece_t operator[](const Position& position) const;

            board_t& get_board(void) { return board_; }
            Color get_turn(void) { return turn_; }
            void set_board(board_t board) { board_ = board; }
            void set_turn(Color color) { turn_ = color; }
            void set_castling(std::string castling) { castling_ = castling; }
            void set_en_passant(std::string enp) { en_passant_ = enp; }
            void calculate_moves(bool reduce);
            ~ChessBoard() = default;
    };
}
