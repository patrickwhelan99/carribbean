#include "custom.h"
#include <math.h>

void monthtick(std::vector<townClass> &towns, std::vector<hexagon> &hexs, std::vector<resourceClass> resources)
{
    for(auto &town : towns)
        {
            town.population += (town.food-(town.population/100))*5;
            if(town.manPower < town.population/7)
                town.manPower += town.population/12;
            if(town.manPower > town.population/7)
                town.manPower = town.population/7;

            if(floor(town.population/100) > town.townSize)
            {
                int newSize = floor(town.population/100);
                for(auto &tile : hexs)
                {
                    if(tile.distanceTo(town.tile) <= newSize && tile.owner == "noOne" && newSize < 11)
                    {
                        town.ownedTiles.push_back(&tile);
                        tile.owner = town.tile->owner;
                        sf::Color colour = town.tile->ownerHex.getFillColor();
                        tile.ownerHex.setFillColor(colour);
                        town.food += tile.resource.food;
                        town.production += tile.resource.production;

                    }
                }
            }
        }
}
