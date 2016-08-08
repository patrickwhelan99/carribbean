#include "custom.h"
#include <fstream>

townClass::townClass(hexagon* tile, std::vector<hexagon*> &adjTiles, std::vector<hexagon> &hexs, int gridSize)
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
    this->ownedTiles = std::vector<hexagon*>();
    this->buildings = std::vector<buildingClass>();

    for(auto &t : this->tile->adjacentTiles(hexs, gridSize))
        this->ownedTiles.push_back(t);
}

int townClass::resourceCount(resourceClass resource)
{
    int resourceCounter = 0;

    for(auto &t : this->ownedTiles)
    {
        if(t->resource.name == resource.name)
            resourceCounter += 1;
    }

    return resourceCounter;
}

void townClass::setTownName(std::vector<townClass> &towns)
{
    std::vector<std::string> names;

        std::ifstream nameFile;
        std::string line;
        nameFile.open(std::string(this->tile->owner + std::string(".txt")));

        if (nameFile.is_open())
        {
            while ( std::getline (nameFile,line) )
                if(line.size() > 1)
                    names.push_back(line);
        }

        for(auto &t : towns)
        {
            for(auto &n : names)
            {
                if(t.name == n)
                    names.erase(std::remove(names.begin(), names.end(), n), names.end()); //if name already taken by another town, find & remove from names vector
            }
        }
        if(names.size() > 0)
        {
            std::random_shuffle(names.begin(), names.end());
            this->name = names.at(0);
        }
        else this->name = std::string("NO_MORE_NAMES!");


}
