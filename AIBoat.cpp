#include "custom.h"
#include <iostream>

AIBoat::AIBoat(sf::Texture &texture, std::vector<hexagon> &hexs, std::vector< std::vector<hexagon*> > &townPaths)
{
    this->setScale(10, 10);
    this->setTexture(texture);
    this->name = "Boaty McBoatFace";
    this->currentHex = nullptr;
    /*
    int randNum;
    while(true)
    {
        randNum = rand() % (hexs.size()-1) + 1;
        if(hexs.at(randNum).terrain == sea)
            break;
    }

    this->setPosition(hexs.at(randNum).resource.icon.getPosition());
    this->x = hexs.at(randNum).x;
    this->y = hexs.at(randNum).y;
    this->z = hexs.at(randNum).z;
    this->currentHex = &(hexs.at(randNum));
    */

    for(auto &hex : hexs)
    {
        if(hex.terrain == town)
        {
            this->setPosition(hex.resource.icon.getPosition());
            this->x = hex.x;
            this->y = hex.y;
            this->z = hex.z;
            this->currentHex = &hex;
            printf("Spawning boat at:\t{%i,%i,%i}\n", hex.x, hex.y, hex.z);
            break;
        }
    }

    int randnum = rand() % ((townPaths.size()-1) + 1);
    if(townPaths.at(randnum).at(0) == this->currentHex)
    {
        this->currentPath = townPaths.at(randnum);

    }
    for (auto &t : this->currentPath)
    {
        printf("{%i, %i, %i}\n", t->x, t->y, t->z);
    }
}


bool AIBoat::moveNext(std::vector<hexagon> &hexs, int &gridSize)
{
    int counter = 0;
    hexagon* tileTo = nullptr;
    std::vector<hexagon*> a; // blank vector

    for(auto &tile : this->currentPath)
    {
        if(counter >= static_cast<int>(this->currentPath.size()-1))
        {
            //printf("Counter:\t%i\t\tCurrentPathSize:\t%i\n", counter, static_cast<int>(this->currentPath.size()-1));
            //std::cout << "Returning FALSE!\n";
            this->currentPath = a;
            return false;
        }

            if(tile->index == this->currentHex->index)
            {
                tileTo = currentPath.at(counter+1);
                if(tileTo != nullptr)
                {
                    this->setPosition(tileTo->resource.icon.getPosition());
                    this->x = tileTo->x;
                    this->y = tileTo->y;
                    this->z = tileTo->z;
                    this->currentHex = tileTo;
                    printf("New Tile:\t{%i, %i, %i}\n", this->x, this->y, this->z);
                    break;
                }
            }


        counter++;
    }
/*
    int iter = 1;
    printf("----------------------------------------------------------");
    for(auto &path : this->currentPath)
    {
        printf("Path:\t%i:\t{%i,%i,%i}\n", iter, path->x, path->y, path->z);
        iter++;
    }
*/

return true;
}
