#include "parsing.hh"
constexpr char init_setup[] = \
                            "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";

std::optional<ChessBoard> create_chessboard_perft(std::string file, int& depth)
{
    std::string board;
    std::string color;
    std::string en_passant;
    std::string castling;
    std::ifstream infile(file);
    int ignore = 0;
    if(infile.good())
    {
        infile >> board >> color >> castling >> en_passant >> ignore >> ignore >> depth;
        ChessBoard res(board);
        Color turn = (color.compare("w") == 0) ? Color::WHITE : Color::BLACK;
        res.set_turn(turn);
        res.set_castling(castling);
        res.set_en_passant(en_passant);
        infile.close();
        return res;
    }
    return std::nullopt;
}
