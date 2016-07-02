#include "custom.h"
#include <iostream>

AIBoat::AIBoat(sf::Texture &texture, std::vector<hexagon> &hexs, std::vector< std::vector<hexagon*> > &townPaths)
{
    this->setScale(10, 10);
    this->setTexture(texture);
    this->name = "Boaty McBoatFace";
    this->currentHex = nullptr;
    this->speed = rand() % ((3) + 1);

    int randnum = rand() % ((townPaths.size()-1) + 1);
    this->currentPath = townPaths.at(randnum);

}


bool AIBoat::moveNext(void)
{
    if(static_cast<int>(this->currentPath.size() <= 0))
        return false;

    if(static_cast<int>(this->currentPath.size() <= this->speed-1))
    {
        currentHex = this->currentPath.at(this->currentPath.size()-1);
        this->x = this->currentHex->x;
        this->y = this->currentHex->y;
        this->z = this->currentHex->z;
        this->setPosition(this->currentHex->resource.icon.getPosition());
        return false;
    }

    this->currentHex = this->currentPath.at(this->speed-1);
    this->x = this->currentHex->x;
    this->y = this->currentHex->y;
    this->z = this->currentHex->z;
    this->setPosition(this->currentHex->resource.icon.getPosition());
    std::reverse(this->currentPath.begin(), this->currentPath.end());
    this->currentPath.pop_back();
    std::reverse(this->currentPath.begin(), this->currentPath.end());

    return true;
}
