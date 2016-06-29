#ifndef CHESSDEFINES
#define CHESSDEFINES

#include <cstddef>

namespace chess {

const std::size_t MAX_ROW = 8;
const std::size_t MAX_COL = 8;

enum class Side
{
    Black,
    White
};

enum class Type
{
    Pawn,
    Bishop,
    Knight,
    Rock,
    Queen,
    King
};

struct Position
{
    bool isValid() const { return row_ > 0 && row_ <= MAX_ROW &&
                                  col_ > 0 && col_ <= MAX_COL; }

    std::size_t row_;
    std::size_t col_;
};

struct Move
{
    enum class Action
    {
        Walk,
        Attack
    };

    Position toPos_;
    Action action_;
};

}

#endif // CHESSDEFINES

