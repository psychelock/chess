#include "board.hh"

namespace board
{
    ChessBoard::ChessBoard(std::string setup)
    {
        turn_ = Color::WHITE;
        castling_ = "KQkq";
        en_passant_ = "-";
        for(int i = 0; i < 21; i++)
        {
            board_[i] = std::nullopt;
        }
        for(int i = 101; i < 120; i++)
        {
            board_[i] = std::nullopt;
        }
        create_board(setup);
    }

    ChessBoard::opt_piece_t ChessBoard::create_piece(char c)
    {
        PieceType type;
        if (islower(c))
        {
            type = pgn_parser::parse_piecetype(toupper(c));
            side_piece_t tmp = std::make_pair(type, Color::BLACK);
            return tmp;
        }
        else if (!islower(c))
        {   
            type = pgn_parser::parse_piecetype(c);
            side_piece_t tmp = std::make_pair(type, Color::WHITE);
            return tmp;
        }
        std::cerr << "Invalid symbol, should never happend " << c;
        return std::nullopt;
    }

    void ChessBoard::create_board(std::string setup)
    {
        int count = 0;
        int pos = 21;
        for (auto c: setup)
        {
            if (isalpha(c))
            {
                opt_piece_t tmp = create_piece(c);
                if(tmp == std::nullopt)
                    return;
                board_[pos] = tmp;
                pos++;
            }
            else if (isdigit(c))
            {
                count = c - '0';
                for(int i = 0; i < count; i++)
                {
                    board_[pos] = std::nullopt;
                    pos++;
                }
            }
            else if (c == '/')
            {
                board_[pos] = std::nullopt;
                board_[pos+1] = std::nullopt;
                pos += 2;
            }
            else
            {
                std::cerr << "Invalid symbol, should never happend " << c;
                exit(1);
            }
        }
    }

    ChessBoard::opt_piece_t ChessBoard::operator[](const Position& position) const
    {
        int file = utils::utype(position.file_get());
        int rank = utils::utype(position.rank_get());
        return board_.at(file * 10 + rank);
    }

    void ChessBoard::dump_board()
    {
        for(int i = 0; i <120; i++)
        {
            if(board_[i] == std::nullopt)
                std::cout << "-";
            else
                std::cout << utils::utype(board_[i]->first);
            if(i % 10 == 9)
                std::cout << "\n";

        }
    }

}
