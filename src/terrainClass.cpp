#include "../include/custom.h"

terrainClass::terrainClass(Terrain terrain, std::string name, int movementPoints)
{
    this->terrain = terrain;
    this->name = name;
    this->movementPoints = movementPoints;
}

terrainClass &terrainClass::operator=(const Terrain &rhs)
{
    this->terrain = rhs;

    switch (rhs)
    {
        case none:
            this->name = "none";
            break;
        case sea:
            this->name = "sea";
            break;
        case sand:
            this->name = "sand";
            break;
        case land:
            this->name = "land";
            break;
        case jungle:
            this->name = "jungle";
            break;
        case mountain:
            this->name = "mountain";
            break;
        case town:
            this->name = "town";
            break;
        case lake:
            this->name = "lake";
            break;

        default:
            std::cerr << "Cannot Assign Terrain: Unknown Terrain type" << std::endl;
    }
    return *this;
}
