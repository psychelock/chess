#include "perft-parser.hh"

ChessBoard create_chessboard_perft(std::string file)
{
    std::string board;
    std::string color;
    std::string en_passant;
    std::string castling;
    std::ifstream infile(file);
    infile >> board >> color >> castling >> en_passant;
    ChessBoard res(board);
    Color turn = (color.compare("w") == 0) ? Color::WHITE : Color::BLACK;
    res.set_turn(turn);
    res.set_castling(castling);
    res.set_en_passant(en_passant);
    infile.close();
    return res;
}
