#include "perft.hh"


int perft(board::ChessBoard& board, const std::list<PgnMove>& moves, const int& depth)
{
    if(depth == 0)
        return 1;
    int score = 0;
    Color turn = board.get_turn();
    for (auto move : moves)
    {
        if(!board.is_check(turn, 0))
        {
            board.do_move(move);
            score += perft(board, board.possible_moves(true), depth - 1);
            board.undo_move();
        }
    }
    return score;
}
