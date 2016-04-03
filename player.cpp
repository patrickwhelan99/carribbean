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

        double start = std::clock();
        double duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

        while(duration < hexTo->movementPoints)
        {
            duration = (std::clock()-start) / (double)CLOCKS_PER_SEC;
        }


        p.character->x = hexTo->x;
        p.character->y = hexTo->y;
        p.character->z = hexTo->z;
        p.character->currentHex = hexTo;

    p.character->setPosition(hexTo->resource.icon.getPosition());
    }

}

std::vector<hexagon*> player::findPath(hexagon* tileTo, std::vector<hexagon> &hexs, int gridSize)
{
    std::vector<hexagon*> hexPath;
    std::vector<hexagon*> openHexs;

    hexagon* currentTile = this->currentHex;
    currentTile->f = currentTile->g + currentTile->distanceTo(tileTo);
    currentTile->parent = nullptr;
    openHexs.push_back(currentTile);
    hexPath.push_back(currentTile);

    while(openHexs.begin() != openHexs.end())
    {
        ///Find best tile in open list

        for(auto &adjTiles : openHexs)
        {
            adjTiles->f = adjTiles->g + adjTiles->distanceTo(tileTo);
        }

        int bestF = 99999999;

        for(auto &adjTiles : openHexs)
        {
            if(adjTiles->f < bestF)
                bestF = adjTiles->f;
        }

        for(auto &adjTiles : openHexs)
        {
            if(adjTiles->f == bestF)
                currentTile = adjTiles;
        }

        ///We now have the best tile

        auto it = find(openHexs.begin(), openHexs.end(), currentTile);
        openHexs.erase(it);

        hexPath.push_back(currentTile);

        if(currentTile == tileTo)
            break;

        int gTotal = 0;
        hexagon* gTotalTile = hexPath.back();
        while(gTotalTile->parent != nullptr)
        {
            gTotal += gTotalTile->g;
            gTotalTile = gTotalTile->parent;
        }

        for(auto &adjTile : currentTile->adjacentTiles(hexs, gridSize))
        {
            bool closed = false;

            for(auto &pathTile : hexPath) //if in closed list
            {
                if(pathTile->index == adjTile->index)
                    closed = true;
            }

            if(adjTile->terrain == sea && !closed) ///if not sea or already on closed list, ignore
            {

                for(auto &pathTile : hexPath) //if in open list
                {
                    if(pathTile->index == adjTile->index)
                        closed = true;
                }

                adjTile->parent = currentTile;
                if(!closed) //if not in open list
                {
                    openHexs.push_back(adjTile);
                }

            }


            if(closed)
                {

                    int gTotalLocal = 0;
                    hexagon* gTotalTileLocal = hexPath.back();
                    while(gTotalTileLocal->parent != nullptr)
                    {
                        gTotalLocal += gTotalTileLocal->g;
                        gTotalTileLocal = gTotalTileLocal->parent;
                    }

                    //printf("Gtotal:\t%i\nGtotalLocal:\t%i\n", gTotal, gTotalLocal);

                    if(gTotalLocal < gTotal) /// FIX THIS
                    {
                        std::cout << "Parent Changed!\n";
                        adjTile->parent = currentTile;
                        adjTile->f = adjTile->g + adjTile->distanceTo(tileTo);
                    }
                }


        }


    ///Pretty Colours!

    for(auto &hex : hexs)
    {
        for(auto &tile : openHexs)
        {
            if(tile->index == hex.index)
            {
                hex.hex.setFillColor(sf::Color::Magenta);
            }
        }
    }


    }

    /* Reconstruct path from end to start by following parents */

    std::vector<hexagon*> path;
    hexagon* currentThing = hexPath.back();
    while(currentThing->parent != nullptr)
    {
        auto parent = currentThing->parent;
        path.push_back(parent);
        currentThing = parent;
    }

    std::reverse(path.begin(), path.end()); // reverse the path; was finish->start, now start->finish

    return path;
}
