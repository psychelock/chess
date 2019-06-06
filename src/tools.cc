#include <iostream>
#include <string>
#include "tools.hh"

namespace tools
{
    char get_char(std::optional<std::pair<board::PieceType, board::Color>> t)
    {
        char res;
        switch(utils::utype(t->first))
        {
            case (0):
                res ='K';
                break;
            case (1):
                res = 'Q';
                break;
            case (2):
                res = 'R';
                break;
            case (3):
                res = 'B';
                break;
            case (4):
                res = 'N';
                break;
            default:
                res = 'P';
                break;
        }
        if(t->second == board::Color::WHITE)
            return res;
        else
            return tolower(res);
    }

    char get_char(PieceType p)
    {
        char res;
        switch(utils::utype(p))
        {
            case (0):
                res ='K';
                break;
            case (1):
                res = 'Q';
                break;
            case (2):
                res = 'R';
                break;
            case (3):
                res = 'B';
                break;
            case (4):
                res = 'N';
                break;
            default:
                res = 'P';
                break;
        }
        return res;
    }

    std::string dump_board_from_fen(std::string fen)
    {
        std::string res = "";
        for(auto c : fen)
        {
            if(isalpha(c))
            {
                res += c;
                res += " ";
            }
            else if (isdigit(c))
            {
                for(int i = 0 ; i < c-'0'; i++)
                    res += "- ";
            }
            else
                res += "\n";
        }
        res += "\n";
        return res;
    }

    PgnMove create_pgnmove (File f1, Rank r1, File f2, Rank r2,\
            PieceType type,\
            bool capture, ReportType report, PgnMove::opt_piece_t& promotion)
    {
        Position from(f1, r1);
        Position to(f2, r2);
        return PgnMove(from, to, type, capture, report, promotion);
    }

    std::optional<Position> get_position(int p)
    {
        if(p % 10 == 0 || p % 10 == 9 || p < 21 || p > 98)
            return std::nullopt;

        File f = static_cast<File> (p % 10);
        Rank r = static_cast<Rank> ((p/10) - 1);
        return Position(f,r);
    }
    int get_index(Position p)
    {
        int file = utils::utype(p.file_get());
        int rank = utils::utype(p.rank_get());
        return (rank + 1) * 10 + file;
    }

    std::string string_from_pos(Position p)
    {
        char file = tolower(get_file(p.file_get()));
        std::string rank = std::to_string(utils::utype(p.rank_get()));
        std::string res = "";
        res + file + rank;
        return res;
    }
    std::string string_from_int(int pos)
    {
        Position p = get_position(pos).value();
        return string_from_pos(p);
    }
}
