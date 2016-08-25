#include "custom.h"

std::vector<terrainClass> loadTerrains(void)
{
    std::vector<terrainClass> terrains;

    terrainClass newTerrain(sea, std::string("sea"), 3);
    terrains.push_back(newTerrain);

    newTerrain.terrain = land;
    newTerrain.name = std::string("land");
    newTerrain.movementPoints = 1;
    terrains.push_back(newTerrain);

    newTerrain.terrain = sand;
    newTerrain.name = std::string("sand");
    newTerrain.movementPoints = 2;
    terrains.push_back(newTerrain);

    newTerrain.terrain = lake;
    newTerrain.name = std::string("lake");
    newTerrain.movementPoints = 1;
    terrains.push_back(newTerrain);

    newTerrain.terrain = jungle;
    newTerrain.name = std::string("jungle");
    newTerrain.movementPoints = 3;
    terrains.push_back(newTerrain);

    newTerrain.terrain = mountain;
    newTerrain.name = std::string("mountain");
    newTerrain.movementPoints = 3;
    terrains.push_back(newTerrain);

    newTerrain.terrain = town;
    newTerrain.name = std::string("town");
    newTerrain.movementPoints = 1;
    terrains.push_back(newTerrain);

    newTerrain.terrain = none;
    newTerrain.name = std::string("none");
    newTerrain.movementPoints = 1;
    terrains.push_back(newTerrain);

    return terrains;
}
