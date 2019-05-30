#include "perft.hh"


int perft(board::ChessBoard& board, const std::list<PgnMove>& moves, const int& depth)
{
    if(depth == 0)
        return 1;
    int score = 0;
    Color turn = board.get_turn();
    Color oppturn; 
    for (auto move : moves)
    {
        if(!board.is_checkmove(move, board.get_board(), turn))
        {
//            std::string turn_str = turn == Color::WHITE ? "White "  : "Black ";
//            std::cout << turn_str << move;
            board.do_move(board.get_board(), move);     // get_board returns board representation. different from class chessboard!
            oppturn = turn == Color::WHITE ? Color::BLACK : Color::WHITE; 
            board.set_turn(oppturn);
            score += perft(board, board.possible_moves(), depth - 1);
            board.undo_move();
            board.set_turn(turn);
        }
    }
    return score;
}
