#include "itemfactory.h"
#include "ChessEngine/board.h"

#include <functional>
#include <map>
#include <algorithm>

namespace chess {

namespace {

using Moves = std::vector<Move>;
using Positions = std::vector<Position>;

void removeInvalidPositions(Positions& positions)
{
    positions.erase(std::remove_if(positions.begin(), positions.end(),[](auto it){
        return !it.isValid();
    }), positions.end());
}

Moves processChainedPositions(Positions& positions, Side currentSide, const Board& board)
{
    removeInvalidPositions(positions);
    Moves moves;
    for ( auto pos : positions)
    {
        auto item = board.findItemByPosition(pos);
        if (!item)
            moves.push_back({pos,Move::Action::Walk});
        else if (currentSide != item->getSide())
        {
            moves.push_back({pos,Move::Action::Attack});
            break;
        }
        else
            break;
    }

    return moves;
}

Moves getRockPosibleMoves( const Item& rock, const Board& board)
{
    auto type = rock.getType();
    if (type != Type::Rock && type != Type::Queen)
        return {};

    auto posColumn = [](Position& pos) { pos.col_++; };
    auto negColumn = [](Position& pos) { pos.col_--; };
    auto posRow = [](Position& pos) { pos.row_++; };
    auto negRow = [](Position& pos) { pos.row_--; };

    std::vector<std::function<void(Position&)>> adjusters{
                                                posColumn,
                                                negColumn,
                                                posRow,
                                                negRow
    };

    Moves moves;
    for (auto& adj : adjusters)
    {
        auto currentPos = rock.getPosition();
        Positions positions;
        for (std::size_t i = 1; i < MAX_ROW; ++i )
        {
            adj(currentPos);
            positions.push_back(currentPos);

        }

        auto locMoves = processChainedPositions(positions, rock.getSide(), board);
        moves.insert(moves.end(), locMoves.begin(), locMoves.end() );
    }

    return moves;
}

Moves getBishopPosibleMoves( const Item& bishop, const Board& board )
{
    auto type = bishop.getType();
    if (type != Type::Bishop && type != Type::Queen)
        return {};

    auto posColumn = [](Position& pos) { pos.row_++; pos.col_++; };
    auto negColumn = [](Position& pos) { pos.row_--; pos.col_--; };
    auto posRow = [](Position& pos) { pos.row_++; pos.col_++; };
    auto negRow = [](Position& pos) { pos.row_--; pos.col_--; };

    std::vector<std::function<void(Position&)>> adjusters{
                                                posColumn,
                                                negColumn,
                                                posRow,
                                                negRow
    };

    Moves moves;
    for (auto& adj : adjusters)
    {
        auto currentPos = bishop.getPosition();
        Positions positions;
        for (std::size_t i = 1; i < MAX_ROW; ++i )
        {
            adj(currentPos);
            positions.push_back(currentPos);

        }

        auto locMoves = processChainedPositions(positions, bishop.getSide(), board);
        moves.insert(moves.end(), locMoves.begin(), locMoves.end() );
    }

    return moves;
}

// item implementations
// Pawn
class Pawn : public Item {
    Pawn(Side side, Position pos) : Item(Type::Pawn, side, pos)
    {}

    virtual std::vector<Move> getPosibleMoves(const Board& board) const override
    {
        Moves moves;
        auto currentPos = getPosition();
        Position moveTo = ( getSide() == Side::White ) ?
                          Position{currentPos.row_, currentPos.col_ + 1} :
                          Position{currentPos.row_, currentPos.col_ - 1};

        if (!board.findItemByPosition(moveTo))
            moves.push_back({moveTo, Move::Action::Walk});

        std::vector<Position> onlyAttackMoves{
            {currentPos.row_-1, currentPos.col_+1},
            {currentPos.row_+1, currentPos.col_+1}
        };

        if (getSide() == Side::Black)
        {
            onlyAttackMoves.clear();
            onlyAttackMoves = {
                {currentPos.row_-1, currentPos.col_-1},
                {currentPos.row_+1, currentPos.col_-1}
            };
        }

        for ( const auto& pos : onlyAttackMoves )
        {
            auto item = board.findItemByPosition(pos);
            if (item && getSide() != item->getSide())
                moves.push_back({pos,Move::Action::Attack});
        }

        return moves;
    }
public:
    static ItemPtr getPawn(Side side, Position pos)
    {
        return std::unique_ptr<Pawn>(new Pawn(side, pos));
    }
};

//Rock
class Rock : public Item {
    Rock(Side side, Position pos) : Item(Type::Rock, side, pos)
    {}

    virtual std::vector<Move> getPosibleMoves(const Board& board) const override
    {
        return getRockPosibleMoves(*this, board);
    }
public:
    static ItemPtr getRock(Side side, Position pos)
    {
        return std::unique_ptr<Rock>(new Rock(side, pos));
    }
};

// Bishop
class Bishop : public Item {
    Bishop(Side side, Position pos) : Item(Type::Bishop, side, pos)
    {}

    virtual std::vector<Move> getPosibleMoves(const Board& board) const override
    {
        return getBishopPosibleMoves(*this, board);
    }
public:
    static ItemPtr getBishop(Side side, Position pos)
    {
        return std::unique_ptr<Bishop>(new Bishop(side, pos));
    }
};

// Knight
class Knight : public Item {
    Knight(Side side, Position pos) : Item(Type::Knight, side, pos)
    {}

    virtual std::vector<Move> getPosibleMoves(const Board& board) const override
    {
        auto currentPos = getPosition();
        std::vector<Position> positionsToCheck{
            {currentPos.row_+1, currentPos.col_+2},
            {currentPos.row_+2, currentPos.col_+1},
            {currentPos.row_+2, currentPos.col_-1},
            {currentPos.row_+1, currentPos.col_-2},
            {currentPos.row_-1, currentPos.col_-2},
            {currentPos.row_-2, currentPos.col_-1},
            {currentPos.row_-1, currentPos.col_+1},
            {currentPos.row_-2, currentPos.col_+2}
        };

        removeInvalidPositions(positionsToCheck);

        Moves moves;
        for ( const auto& pos : positionsToCheck )
        {
            auto item = board.findItemByPosition(pos);
            if (!item)
                moves.push_back({pos,Move::Action::Walk});
            else if (getSide() != item->getSide())
                moves.push_back({pos,Move::Action::Attack});
        }

        return moves;
    }
public:
    static ItemPtr getKnight(Side side, Position pos)
    {
        return std::unique_ptr<Knight>(new Knight(side, pos));
    }
};

// Queen
class Queen : public Item {
    Queen(Side side, Position pos) : Item(Type::Queen, side, pos)
    {}

    virtual std::vector<Move> getPosibleMoves(const Board& board) const override
    {
        auto allMoves = getRockPosibleMoves(*this, board);
        auto bishopMoves = getBishopPosibleMoves(*this, board);
        allMoves.insert(allMoves.end(), bishopMoves.begin(), bishopMoves.end());

        return allMoves;
    }
public:
    static ItemPtr getQueen(Side side, Position pos)
    {
        return std::unique_ptr<Queen>(new Queen(side, pos));
    }
};

//King
class King : public Item {
    King(Side side, Position pos) : Item(Type::King, side, pos)
    {}

    virtual std::vector<Move> getPosibleMoves(const Board& board) const override
    {
        auto currentPos = getPosition();
        std::vector<Position> positionsToCheck{
            {currentPos.row_-1, currentPos.col_-1},
            {currentPos.row_-1, currentPos.col_+1},
            {currentPos.row_+1, currentPos.col_-1},
            {currentPos.row_+1, currentPos.col_+1},
            {currentPos.row_, currentPos.col_+1},
            {currentPos.row_, currentPos.col_-1},
            {currentPos.row_+1, currentPos.col_},
            {currentPos.row_-1, currentPos.col_}
        };

        removeInvalidPositions(positionsToCheck);

        Moves moves;
        for ( const auto& pos : positionsToCheck )
        {
            auto item = board.findItemByPosition(pos);
            if (!item)
                moves.push_back({pos,Move::Action::Walk});
            else if (getSide() != item->getSide())
                moves.push_back({pos,Move::Action::Attack});
        }

        return moves;
    }
public:
    static ItemPtr getKing(Side side, Position pos)
    {
        return std::unique_ptr<King>(new King(side, pos));
    }
};



using ItemCreator_t = std::function<ItemPtr (Side, Position)>;
std::map<Type, ItemCreator_t> itemFactory{
    {Type::Pawn, Pawn::getPawn},
    {Type::Bishop, Bishop::getBishop},
    {Type::Knight, Knight::getKnight},
    {Type::Rock, Rock::getRock},
    {Type::Queen, Queen::getQueen},
    {Type::King, King::getKing}
};

} // anonymous


ItemPtr createItem(Type type, Side side, Position startPos)
{
    auto foundIt = itemFactory.find(type);
    if (foundIt == itemFactory.end())
        throw std::logic_error("Invalid Type");

    return foundIt->second(side, startPos);
}

} // chess
