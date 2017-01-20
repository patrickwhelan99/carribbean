#include "custom.h"

std::vector<hexagon*> popTownTiles(std::vector<townClass> &towns, std::vector<hexagon> &hexs, std::vector<int> &edgeTiles)
{
    std::vector<hexagon*> townTiles;

    for(auto &i : towns)
        townTiles.push_back(i.tile);

    for(auto &i : edgeTiles)
    {
        if(hexs.at(i).terrain.terrain != sea)
        {
            edgeTiles.erase(std::remove(edgeTiles.begin(), edgeTiles.end(), i), edgeTiles.end());
        }
        else
        {
            if(i%29==0) /// Add every tile whom's index is divisable by 29
                townTiles.push_back(&hexs.at(i));
        }
    }

    return townTiles;
}
