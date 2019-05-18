#include "given/chessboard-interface.hh"
#include "given/pgn-move.hh"
#include "given/pgn-parser.hh"
#include "given/color.hh"

#include <map>
#include <list>
#include <string>
#include <memory>
#include <iostream>


namespace board
{
    class ChessBoard : public ChessboardInterface
    {
        private:
            std::map<int, opt_piece_t> board_;
            Color turn_;
            std::string castling_;
            std::string en_passant_;
            //std::list<Piece> piece_list_;

        public:
            ChessBoard(std::string setup);
            
            void dump_board();
            bool valid_move(PgnMove);
            std::list<PgnMove> possible_moves(void);
            int perft_score(int depth);
            void do_move(PgnMove);
            void undo_move(PgnMove);
            void create_board(std::string);
            opt_piece_t create_piece(char c);

            opt_piece_t operator[](const Position& position) const;
    };
}
