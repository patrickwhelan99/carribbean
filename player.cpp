#include "custom.h"
#include <iostream>
#include <algorithm>

playerClass::playerClass(sf::Texture &texture, std::vector<hexagon> &hexs, std::string &name, std::vector<townClass> &towns)
{
    this->setScale(15, 15);
    this->setTexture(texture);
    this->name = "No-name";
    this->money = 1000;
    this->speed = 2;
    int randNum = rand() % towns.size() + 0;
    hexagon* spawnTile = towns.at(randNum).tile;
    this->setPosition(spawnTile->resource.icon.getPosition());
    this->x = spawnTile->x;
    this->y = spawnTile->y;
    this->z = spawnTile->z;
    this->currentHex = spawnTile;
    this->currentPath = std::vector<hexagon*>();
}

void playerClass::moveNext(void)
{
    if(static_cast<int>(this->currentPath.size() <= 0))
        return;

    if(static_cast<int>(this->currentPath.size()) <= this->speed-1)
    {
        currentHex = this->currentPath.at(this->currentPath.size()-1);
        this->x = this->currentHex->x;
        this->y = this->currentHex->y;
        this->z = this->currentHex->z;
        this->setPosition(this->currentHex->resource.icon.getPosition());
        return;
    }

    this->currentHex = this->currentPath.at(this->speed-1);
    this->x = this->currentHex->x;
    this->y = this->currentHex->y;
    this->z = this->currentHex->z;
    this->setPosition(this->currentHex->resource.icon.getPosition());
    std::reverse(this->currentPath.begin(), this->currentPath.end());
    this->currentPath.pop_back();
    std::reverse(this->currentPath.begin(), this->currentPath.end());

    return;
}

