#ifndef CHESSITEM_H
#define CHESSITEM_H

#include "defines.h"

#include <string>
#include <memory>
#include <vector>

namespace chess {

class Board;
// base class for all chess figures
class Item
{
protected:
    Item(Type type, Side side, Position pos) :
        type_(type), side_(side), pos_(pos)
    {}

public:
    virtual ~Item(){}

    Type getType() const { return type_; }
    Side getSide() const { return side_; }
    Position getPosition() const { return pos_; }

    // get possible moves for current item
    virtual std::vector<Move> getPosibleMoves(const Board& board) const = 0;

private:
    Type type_;
    Side side_;
    Position pos_;
};

// shorthand
using ItemPtr = std::unique_ptr<Item>;

} // chess

#endif // CHESSITEM_H
