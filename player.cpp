#include "custom.h"
#include <iostream>
#include <algorithm>

void playerClass::setPath(hexagon &tile, std::vector<hexagon> &hexs, int &gridSize)
{
    this->currentPath = std::vector<hexagon*>(); // clear current path
    pathParameters p(this->currentHex, &tile, hexs, gridSize);
    this->currentPath = findPath(p);
}

void playerClass::fireCannons(const bool &isIntersecting, AIBoat &enemyShip)
{
    if(!isIntersecting)
        return;

    this->currentReloadTime = this->reloadTime;
    float randDmg = float(rand()%75+25)/float(100);
    enemyShip.health -= randDmg;
    if(enemyShip.health <= 0.0f)
    {
        enemyShip.inactive = true;
    }
}

