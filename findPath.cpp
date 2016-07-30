#include "custom.h"
#include <iostream>

bool compHexs(const hexagon* a, const hexagon* b) {return a->f < b->f;}
bool inVector(std::vector<hexagon*> vec, hexagon* adj)
{
    for(auto &a : vec)
        if(a->index == adj->index)
            return true;

    return false;
}

std::vector<hexagon*> buildPath(hexagon* tile)
{
    ///Reconstruct Path and Return
    std::vector<hexagon*> path;
    while(tile->parent != nullptr)
    {
        path.push_back(tile);
        tile = tile->parent;
    }

    path.push_back(tile);
    std::reverse(path.begin(), path.end());

    return path;
}

std::vector<hexagon*> findPath(pathParameters params)
{
    /*
    *** F represents a heurastic calculation for the path whilst G is the current known 'cost'
    */

    std::vector<hexagon*> openVec;
    std::vector<hexagon*> closedVec;

    ///Setup all tiles
    for(auto &t : params.hexs)
    {
        t.f = 9999999;
        t.g = 9999999;
    }

    ///Setup starting tile
    params.tile1->f = params.tile1->distanceTo(params.tile2); /// Heuraustics calculated by straight line distance formula
    params.tile1->g = 0;
    openVec.push_back(params.tile1);

    ///Main variable for loop; tile currently being used, it's adjecent tiles will be evaluated
    hexagon* currentTile;

    ///********************MAIN LOOP********************///

    while(openVec.size() > 0)
    {
        ///First sort the openVector
        std::sort(openVec.begin(), openVec.end(), compHexs); //CompHexes checks index of tiles and returns bool to sort

        ///Grab the lowest F scoring tile in the open list; then remove it from the open list and add it to the closed list
        currentTile = openVec.at(0);
        std::reverse(openVec.begin(), openVec.end());
        openVec.pop_back();
        closedVec.push_back(currentTile);


        ///If Current Tile is goal return path
        if(currentTile->index == params.tile2->index)
        {
            ///Grab the path before deleting as much data as possible; All data must be stored simultaniously due to the futures being collected later; Large maps can lead to a large RAM usage
            auto ret =  buildPath(currentTile);
            std::vector<hexagon> a;
            std::vector<hexagon*> b;
            params.hexs = a;
            openVec = b;
            closedVec = b;
            return ret;
        }


        for(auto &adj : currentTile->adjacentTiles(params.hexs, params.gridSize))
        {

            if(!inVector(closedVec, adj)) /// If not already evaluated (in closed list)
            {
                if(!inVector(openVec, adj) && (adj->terrain == sea || adj->terrain == town)) /// If not already queued to be evalued (in open list) then add
                    openVec.push_back(adj);

                int tentativeGScore = currentTile->g + currentTile->distanceTo(adj);

                if(tentativeGScore < adj->g) /// If distance to next tile is less than distance to current tile???
                {
                    adj->parent = currentTile;
                    adj->g = tentativeGScore;
                    adj->f = adj->g + adj->distanceTo(params.tile2);
                }
            }

        }

    }
    std::vector<hexagon*> a;
    printf("FIND PATH FAILED!\n");
    a.push_back(params.tile1);
    return a;
}


