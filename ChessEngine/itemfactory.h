#ifndef ITEMFACTORY_H
#define ITEMFACTORY_H

#include "item.h"

namespace chess {

ItemPtr createItem(Type type, Side side, Position startPos);

} // chess

#endif // ITEMFACTORY_H
