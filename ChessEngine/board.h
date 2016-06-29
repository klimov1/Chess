#ifndef BOARD_H
#define BOARD_H

#include "item.h"

#include <vector>
#include <map>

namespace chess {


// holds all figures on a board in particular moment of time (step)
class Board
{
    using Moves = std::vector<Move>;
    struct PositionLess
    {
        bool operator ()(Position lhs, Position rhs) const;
    };
public:
    Board(std::vector<ItemPtr> item, std::size_t step);

    const Item* findItemByPosition(Position pos) const;

private:
    void fillInMoves();
private:
    std::vector<ItemPtr> items_;
    std::map<Position, Moves, Board::PositionLess> allMoves_; // all possible moves for every item we have
    std::size_t step_;
};

}

#endif // BOARD_H
