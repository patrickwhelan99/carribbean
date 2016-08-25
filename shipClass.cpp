#include "custom.h"

shipClass::shipClass(std::vector<hexagon> &hexs, std::vector<townClass> &towns, std::vector<goodClass> &goods)
{
    ///Spawn the ship in a random town and initialize variables
    this->currentHex = nullptr;
    int randNum = rand() % towns.size() + 0;
    hexagon* spawnTile = towns.at(randNum).tile;
    this->setPosition(spawnTile->resource.icon.getPosition());
    this->x = spawnTile->x;
    this->y = spawnTile->y;
    this->z = spawnTile->z;
    this->currentHex = spawnTile;
    this->currentPath = std::vector<hexagon*>();

    for(auto &g : goods)
    {
        this->inventory.push_back(g);
    }
}

void shipClass::moveNext(void)
{
    if(static_cast<int>(this->currentPath.size() <= 0))
        return;

    this->movementPoints += this->speed;

    int moveCost = floor((this->currentHex->movementPoints + this->currentPath.front()->movementPoints)/2);
    if(this->movementPoints >= moveCost)
    {
        this->currentHex = this->currentPath.front();
        this->x = this->currentHex->x;
        this->y = this->currentHex->y;
        this->z = this->currentHex->z;
        this->setPosition(this->currentHex->resource.icon.getPosition());
        std::reverse(this->currentPath.begin(), this->currentPath.end());
            this->currentPath.pop_back();
        std::reverse(this->currentPath.begin(), this->currentPath.end());
        this->movementPoints = 0;
    }


    return;
}
