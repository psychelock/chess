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
/*
std::optional<ChessBoard> create_chessboard_pgn(std::string file)
{
    std::vector moves = pgn_parser::parse_pgn(file);
    ChessBoard game(init_setup);
    board::board_t check = game.get_board();
    Color side;
    for(auto i : moves)
    {
        game.do_move(check, i);
        side = (game.get_turn() == Color::WHITE) ? Color::BLACK : Color::WHITE;
        if (!game.valid_move(i))
        {
            //FIXME add how to handl logging before exiting
            // Got an invalid move
            exit(0);
        }
        game.set_board(check);
        game.set_turn(side);
    }
    return game;
}*/
