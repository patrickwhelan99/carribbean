#include "custom.h"
#include <iostream>
#include <algorithm>

player::player(sf::Texture &texture, std::vector<hexagon> &hexs)
{
    this->setScale(15, 15);
    this->setTexture(texture);
    this->name = "No-name";
    this->money = 1000;
    this->setPosition(hexs.at(0).resource.icon.getPosition());
    this->x = hexs.at(0).x;
    this->y = hexs.at(0).y;
    this->z = hexs.at(0).z;
    this->currentHex = &(hexs.at(0));
}

void playerMovement(parameters p)
{
    for(auto &hexTo : p.hexPath)
    {
        hexTo->hex.setFillColor(sf::Color::Red);

        p.character->x = hexTo->x;
        p.character->y = hexTo->y;
        p.character->z = hexTo->z;
        p.character->currentHex = hexTo;

        p.character->setPosition(hexTo->resource.icon.getPosition());
    }

}
