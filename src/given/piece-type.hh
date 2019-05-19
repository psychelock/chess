#pragma once

#include <array>
#include <optional>

namespace board
{
    /* PieceType is an enum representing every possible
     * piece type present on the board. The char associated
     * with each value is the ascii char representing the
     * piece on the board */
    enum class PieceType
    {
        KING,
        QUEEN,
        ROOK,
        BISHOP,
        KNIGHT,
        PAWN
    };

    using opt_piecetype_t = std::optional<PieceType>;

    /* Can be useful to iterate over PieceTypes */
    constexpr std::array<PieceType, 6> piecetype_array{
        PieceType::KING,   PieceType::QUEEN,  PieceType::ROOK,
        PieceType::BISHOP, PieceType::KNIGHT, PieceType::PAWN};


} // namespace board
