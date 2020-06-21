#include "../include/custom.h"

std::vector<terrainClass> loadTerrains(void)
{
    std::vector<terrainClass> terrains;

    terrainClass noneObj(none, std::string("none"), 3);
    terrains.push_back(noneObj);

    terrainClass seaObj(sea, std::string("sea"), 1);
    terrains.push_back(seaObj);

    terrainClass lakeObj(lake, std::string("lake"), 1);
    terrains.push_back(lakeObj);

    terrainClass sandObj(sand, std::string("sand"), 3);
    terrains.push_back(sandObj);

    terrainClass landObj(land, std::string("land"), 2);
    terrains.push_back(landObj);

    terrainClass jungleObj(jungle, std::string("jungle"), 3);
    terrains.push_back(jungleObj);

    terrainClass townObj(town, std::string("town"), 1);
    terrains.push_back(townObj);

    terrainClass mountainObj(mountain, std::string("mountain"), 3);
    terrains.push_back(mountainObj);

    return terrains;
}
