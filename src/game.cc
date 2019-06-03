#include "game.hh"

namespace gameloop
{
    int gameloop(ChessBoard board, std::vector<PgnMove> list)
    {  
        void *handle = dlopen("../src/given/tests/libbasic-output.so", RTLD_LAZY);
        void *create = dlsym(handle, "listener_create");
        listener::Listener *lis = reinterpret_cast<listener::Listener*(*)()>(create)();
        lis->register_board(board);
        long unsigned int i = 0;
        do
        {
            if(i >= list.size())
                break;
            /*{
                auto gen = ai::ai(1, board, (board.get_turn() == Color::BLACK)); // 1st param is depth
                if(gen == std::nullopt)
                    break;
                else
                    auto move = gen.value();
            }
            else
            {*/
                auto move = list.at(i); i++;
            //}
            if(!board.valid_move(move)) 
                break;
            if(move.get_piece() == PieceType::KING) // castling
            {
                int start = tools::get_index(move.get_start());
                int end = tools::get_index(move.get_end());
                if((start == 25 || start == 95) && (end == 27 || end == 97))
                {
                    lis->on_piece_moved(move.get_piece(), move.get_start(), move.get_end());
                    lis->on_kingside_castling(board.get_turn());
                }
                if((start == 25 || start == 95) && (end == 23 || end == 93))
                {
                    lis->on_piece_moved(move.get_piece(), move.get_start(), move.get_end());
                    lis->on_queenside_castling(board.get_turn());
                }
            }
            else //moved piece
            {
                int end = tools::get_index(move.get_end());
                lis->on_piece_moved(move.get_piece(), move.get_start(), move.get_end());
                if(move.get_capture()) // capture
                {
                    lis->on_piece_taken(move.get_piece(), move.get_end());
                }
                if(move.get_piece() == PieceType::PAWN && (end <=  98 && end >= 91)) //promotion
                    lis->on_piece_promoted(move.get_piece(), move.get_end());
            }
            if(board.is_checkmate(board.get_turn()))
            {
                lis->on_player_mat(board.get_turn());
                break;
            }
            else if(board.is_check(board.get_turn(), 0))
            {
                lis->on_player_check(board.get_turn());
            }
            if(board.is_stalemate())
            {
                lis->on_player_pat(board.get_turn());
                lis->on_draw();
                break;
            }
            board.calculate_moves();
            board.dump_board();
            getchar();
            // Check for special draws !
        }while(true);
        board.dump_board();
        lis->on_game_finished();
        free(lis);
        dlclose(handle);
        return 0;
    }
}
