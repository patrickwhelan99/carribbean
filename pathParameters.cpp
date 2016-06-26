#include "custom.h"

pathParameters::pathParameters(hexagon* tile1, hexagon* tile2, std::vector<hexagon> &hexs/*CHANGE THIS BACK!!!!!!!*/, int gridSize)
{
    this->tile1 = tile1;
    this->tile2 = tile2;
    this->hexs = hexs;
    this->gridSize = gridSize;
}


pathParameters::pathParameters(void)
{
    this->tile1 = nullptr;
    this->tile2 = nullptr;
    std::vector<hexagon> a;
    this->hexs = a;
    this->gridSize = 0;
}
