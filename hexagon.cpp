#include "custom.h"
#include <iostream>
#include <string>

hexagon::hexagon()
{
    this->hex = sf::CircleShape(5000, 6);
    this->hex.setOrigin(5000, 5000);
    this->hex.scale(sf::Vector2f(1.2, 1.2));
    this->hex.setFillColor(sf::Color(200, 200, 200, 255));
    this->ownerHex = sf::CircleShape(5000, 6);
    this->ownerHex.setOrigin(5000, 5000);
    //this->ownerHex.setFillColor(sf::Color(255, 255, 255));
    //this->terrain = sea;
    this->owner = "noOne";
    this->resourceIcon = sf::CircleShape(2000, 6);
    this->resourceIcon.setOrigin(1000, 1000);
    this->x = 0;
    this->y = 0;
    this->z = 0;
    this->g = 0;
    this->h = 0;
    this->movementPoints = 1;
    this->parent = nullptr;
    this->townOnTile = nullptr;
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

adjTileCounter hexagon::countAdjacentTiles(std::vector<hexagon> &hexs, int gridSize)
{
    int adjSea = 0;
    int adjLand = 0;
    int adjSand = 0;
    int adjTown = 0;
    int adjLake = 0;
    int adjMountain = 0;
    int adjJungle = 0;

    for(auto &adjTile : this->adjacentTiles(hexs, gridSize))
    {
        switch (adjTile->terrain.terrain)
        {
            case sea:
                adjSea++;
                break;

            case land:
                adjLand++;
                break;

            case sand:
                adjSand++;
                break;

            case town:
                adjTown++;
                break;

            case lake:
                adjLake++;
                break;

            case mountain:
                adjMountain++;
                break;

            case jungle:
                adjJungle++;
                break;

            default:
                break;
        }

    }

    adjTileCounter newCounter(adjSea, adjLand, adjSand, adjJungle, adjLake, adjTown, adjMountain);
    return newCounter;
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


std::vector<hexagon*> hexagon::adjacentTilesByCoords(std::vector<hexagon> &hexs, int &gridSize)
{
    std::vector<hexagon*> adjHexs;
    for (auto &others : hexs)
    {
        if((others.x == this->x - 1 && others.y == this->y - 1) || (others.x == this->x && others.y == this->y - 1) || (others.x == this->x - 1 && others.y == this->y ) || (others.x == this->x + 1 && others.y == this->y) || (others.x == this->x && others.y == this->y + 1) || (others.x == this->x + 1 && others.y == this->y + 1))
        {
            adjHexs.push_back(&others);
        }
    }

    return adjHexs;
}


void hexagon::setupTris(std::vector<sf::Texture> &alphaTextures)
{
    int radius = 3500;
    for(int i=0;i<6;i++)
    {
        int rotation = 30+i*60;
        triangle newTriangle(alphaTextures, radius, 3, this, rotation);
    }
}

