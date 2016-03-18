#include "custom.h"
#include <iostream>

hexagon::hexagon(int x, int y)
{
    this->hex = sf::CircleShape(25, 6);
    this->hex.setFillColor(sf::Color::Blue);
    this->terrain = sea;
    this->resource = none;

    this->resourceIcon = sf::CircleShape(15, 6);
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
