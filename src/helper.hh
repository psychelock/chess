#pragma once
#include "given/pgn-move.hh"
#include "given/piece-type.hh"
#include "given/color.hh"

#include <map>
#include <list>
#include <string>

namespace board
{
    class Previous
    {
        private:
            std::map<int, std::optional<std::pair<PieceType, Color>>> b_;
            Color t_;
            std::string cast_;
            std::string en_p_;

        public:
            Previous(std::map<int, std::optional<std::pair<PieceType, Color>>> b, Color t, std::string cast,std::string en_p);
            std::string get_cast(void) { return cast_; }
            std::string get_en_p(void) { return en_p_; }
            Color get_t(void)      { return t_; }
            std::map<int, std::optional<std::pair<PieceType, Color>>> get_b(void) { return b_; }
            ~Previous() = default;
    };

}
