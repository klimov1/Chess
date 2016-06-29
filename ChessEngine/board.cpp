#include "board.h"

#include <tuple>
#include <algorithm>

namespace chess {

bool Board::PositionLess::operator ()(Position lhs, Position rhs) const
{
    return std::tie(lhs.row_, lhs.col_) < std::tie(rhs.row_, rhs.col_);
}

Board::Board(std::vector<ItemPtr> items, std::size_t step)
    : items_(std::move(items)), step_(step)
{
    fillInMoves();
}

const Item *Board::findItemByPosition(Position pos)const
{    
    auto foundIt = std::find_if(items_.begin(), items_.end(), [pos](const auto& item){
        auto currPos = item->getPosition();
        return pos.col_ == currPos.col_ && pos.row_ == currPos.row_;
    });

    if (foundIt == items_.end())
        return nullptr;

    return foundIt->get();
}

void Board::fillInMoves()
{
    for ( const auto& item : items_ )
        allMoves_[item->getPosition()] = item->getPosibleMoves(*this);
}

} // chess
