#ifndef CHESSUTILS_H
#define CHESSUTILS_H

#include "ChessEngine/defines.h"

#include <string>
#include <vector>

namespace chess_utils {

// Side helper functions
std::string convertSideToString(chess::Side side);
chess::Side parseSideFromString(const std::string& side);
std::vector<std::string> getAllSidesAsString();

// Type helper functions
std::string convertTypeToString(chess::Type type);
chess::Type parseTypeFromString(const std::string& type);
std::vector<std::string> getAllTypesAsString();

}

#endif // CHESSUTILS_H
