#include "custom.h"

terrainClass::terrainClass(Terrain terrain, std::string name, int movementPoints)
{
    this->terrain = terrain;
    this->name = name;
    this->movementPoints = movementPoints;
}
