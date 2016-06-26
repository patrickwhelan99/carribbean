#include "custom.h"

townClass::townClass(hexagon* tile, std::vector<hexagon*> &adjTiles, Owner owner)
{
    this->income = 2;
    this->expenditure = 0;
    this->population = 100;
    this->garrison = 0;
    this->manPower = 10;
    this->tile = tile;
    this->food = 1;
    this->production = 1;
    this->townSize = 1;

    for(auto &adjTile : adjTiles)
    {
        switch(owner)
        {
            case england:
                adjTile->owner = england;
                adjTile->ownerHex.setFillColor(sf::Color(255, 0, 50, 200));
                break;

            case portugal:
                adjTile->owner = portugal;
                adjTile->ownerHex.setFillColor(sf::Color(255, 50, 255, 200));
                break;

            case spain:
                adjTile->owner = spain;
                adjTile->ownerHex.setFillColor(sf::Color(255, 255, 50, 200));
                break;

            case france:
                adjTile->owner = france;
                adjTile->ownerHex.setFillColor(sf::Color(0, 255, 255, 200));
                break;

            default:
                adjTile->owner = noOne;
                break;
        }

            this->food += adjTile->resource.food;
            this->production += adjTile->resource.production;
    }
}
