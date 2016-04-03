#include "custom.h"
#include <iostream>
#include <string>

hexagon::hexagon()
{
    this->hex = sf::CircleShape(25*200, 6);
    this->hex.setFillColor(sf::Color::Blue);
    this->ownerHex = sf::CircleShape(25*200, 6);
    this->ownerHex.setFillColor(sf::Color(255, 255, 255));
    this->terrain = sea;
    this->owner = noOne;
    this->resourceIcon = sf::CircleShape(15*200, 6);
    this->x = 0;
    this->y = 0;
    this->z = 0;
    this->movementPoints = 1;
}

std::vector<hexagon*> hexagon::adjacentTiles(std::vector<hexagon> &hexs, int gridSize)
{
    std::vector<hexagon*> adjHexs;
    int vectorSize = gridSize*gridSize;

    int ting = index - (gridSize+1); //-x,-y TL
    if((this->y % 2) == 0)
    {
        ting++;
    }
    if(!(ting < 0))
    {
        adjHexs.push_back(&hexs.at(ting));
    }


    ting = index - gridSize; // x, -y TR
    if((this->y % 2) == 0)
    {
        ting++;
    }
    if(!(ting < 0))
    {
        adjHexs.push_back(&hexs.at(ting));
    }


    ting = index - 1; // -x, y L
    if(!(ting < 0))
    {
        adjHexs.push_back(&hexs.at(ting));
    }


/********************************************************/


    ting = index + 1; // +x, y R
    if(!(ting >= vectorSize))
    {
        adjHexs.push_back(&hexs.at(ting));
    }

    ting = index + (gridSize-1); // x, +y BL
    if((this->y % 2) == 0)
    {
        ting++;
    }
    if(!(ting >= vectorSize))
    {
        adjHexs.push_back(&hexs.at(ting));
    }

    ting = index + gridSize; // +x, +y BR
    if((this->y % 2) == 0)
    {
        ting++;
    }
    if(!(ting >= vectorSize))
    {
        adjHexs.push_back(&hexs.at(ting));
    }


    return adjHexs;
}


int hexagon::distanceTo(hexagon* to)
{
    int distancex = (to->x)-(this->x);
    int distancey = (to->y)-(this->y);
    int distancez = (to->z)-(this->z);

    if(distancex<0)
        distancex *= -1;
    if(distancey<0)
        distancey *= -1;
    if(distancez<0)
        distancez *= -1;


    return (distancex+distancey+distancez)/2;
}

/*
std::vector<hexagon> hexagon::adjacentTiles(std::vector<hexagon> &hexs)
{
    std::vector<hexagon> adjHexs;
    for (auto &others : hexs)
    {
        if((others.x == this->x - 1 && others.y == this->y - 1) || (others.x == this->x && others.y == this->y - 1) || (others.x == this->x - 1 && others.y == this->y ) || (others.x == this->x + 1 && others.y == this->y) || (others.x == this->x && others.y == this->y + 1) || (others.x == this->x + 1 && others.y == this->y + 1))
        {
            adjHexs.push_back(others);
        }
    }

    return adjHexs;
}
*/
