#include "custom.h"
#include <iostream>
#include <algorithm>

void playerClass::setPath(hexagon &tile, std::vector<hexagon> &hexs, int &gridSize)
{
    this->currentPath = std::vector<hexagon*>(); // clear current path
    pathParameters p(this->currentHex, &tile, hexs, gridSize);
    this->currentPath = findPath(p);
}

