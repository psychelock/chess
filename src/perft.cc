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
//            std::string turn_str = turn == Color::WHITE ? "White "  : "Black ";
//            std::cout << turn_str << move;
            board.do_move(move);     // get_board returns board representation. different from class chessboard!
            score += perft(board, board.possible_moves(), depth - 1);
            board.undo_move();
        }
    }
    return score;
}
