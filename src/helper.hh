#pragma once
#include "given/pgn-move.hh"
#include "given/piece-type.hh"
#include "given/color.hh"

#include <map>
#include <list>
#include <string>

namespace board
{
    struct Previous
    {
        std::map<int, std::optional<std::pair<PieceType, Color>>> b_;
        Color t_;
        std::string cast_;
        std::string en_p_;
        
        Previous(std::map<int, std::optional<std::pair<PieceType, Color>>> b, Color t, std::string cast,std::string en_p);
        
        Previous(void);
    };

}
