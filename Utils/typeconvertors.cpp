#include "typeconvertors.h"

#include <stdexcept>
#include <vector>
#include <algorithm>

namespace {

std::vector<std::pair<chess::Side, std::string>> sideStr{
    { chess::Side::Black, "Black" },
    { chess::Side::White, "White" }
};

std::vector<std::pair<chess::Type, std::string>> typeStr{
    { chess::Type::Pawn, "Pawn" },
    { chess::Type::Bishop, "Bishop" },
    { chess::Type::Knight, "Knight" },
    { chess::Type::Rock, "Rock" },
    { chess::Type::Queen, "Queen" },
    { chess::Type::King, "King" }
};

template< typename Container>
std::vector<std::string> getStringValues( const Container& cont)
{
    std::vector<std::string> res(cont.size());
    std::transform(cont.begin(), cont.end(), res.begin(),[](const auto& inPair){
        return inPair.second;
    });

    return res;
}

} // anonymous

namespace chess_utils {

std::string convertSideToString(chess::Side side)
{
    auto foundIt = std::find_if(sideStr.begin(), sideStr.end(), [side](const auto& inPair){
        return inPair.first == side;
    });

    if (foundIt != sideStr.end())
        return foundIt->second;

    throw std::logic_error("Unknown side");
}

chess::Side parseSideFromString(const std::string& side)
{
    auto foundit = std::find_if(sideStr.begin(), sideStr.end(),[&side](const auto& inPair){
       return inPair.second == side;
    });

    if (foundit != sideStr.end())
        return foundit->first;

    throw std::logic_error("Can't parse <" + side + "> as valid Side");
}

std::string convertTypeToString(chess::Type type)
{
    auto foundIt = std::find_if(typeStr.begin(), typeStr.end(), [type](const auto& inPair){
        return inPair.first == type;
    });

    if (foundIt != typeStr.end())
        return foundIt->second;

    throw std::logic_error("Unknown type");
}

chess::Type parseTypeFromString(const std::string& type)
{
    auto foundIt = std::find_if(typeStr.begin(), typeStr.end(), [&type](const auto& inPair){
        return inPair.second == type;
    });

    if (foundIt != typeStr.end())
        return foundIt->first;

    throw std::logic_error("Can't parse <" + type + "> as valid Type");
}

std::vector<std::string> getAllSidesAsString()
{
    return getStringValues(sideStr);
}

std::vector<std::string> getAllTypesAsString()
{
    return getStringValues(typeStr);
}

}

