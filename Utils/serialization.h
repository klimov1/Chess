#ifndef SERIALIZATION_H
#define SERIALIZATION_H

#include "ChessEngine/itemfactory.h"

#include <vector>

namespace chess_utils {

// serialize items into file
bool serializeToJSON(const std::vector<chess::ItemPtr>& board, const std::string& fileName);
std::vector<chess::ItemPtr> derializeFromJSON(const std::string& fileName);

}

#endif // SERIALIZATION_H
