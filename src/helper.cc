#include "helper.hh"

namespace board
{
    Previous::Previous(std::map<int, std::optional<std::pair<PieceType, Color>>> b, Color t, std::string cast,std::string en_p)
        : b_(b), t_(t), cast_(cast), en_p_(en_p) {}
}
