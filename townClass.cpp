#include "custom.h"
#include <fstream>

townClass::townClass(hexagon* tile, std::vector<hexagon*> &adjTiles, std::vector<hexagon> &hexs, int gridSize, std::vector<goodClass> &goods)
{
    this->income = 2;
    this->expenditure = 0;
    this->population = 100;
    this->garrison = 0;
    this->manPower = 10;
    this->tile = tile;
    this->food = 1;
    this->production = 1;
    this->townSize = 1;
    this->ownedTiles = std::vector<hexagon*>();
    this->buildings = std::vector<buildingClass>();

    for(auto &t : this->tile->adjacentTiles(hexs, gridSize))
        this->ownedTiles.push_back(t);

    for(auto &g : goods)
        this->goods.push_back(g);
}

int townClass::resourceCount(resourceClass resource)
{
    int resourceCounter = 0;

    for(auto &t : this->ownedTiles)
    {
        if(t->resource.name == resource.name)
            resourceCounter += 1;
    }

    return resourceCounter;
}

void townClass::setTownName(std::vector<townClass> &towns)
{
    std::vector<std::string> names;

        std::ifstream nameFile;
        std::string line;
        nameFile.open(std::string(this->tile->owner + std::string(".txt")));

        if (nameFile.is_open())
        {
            while ( std::getline (nameFile,line) )
                if(line.size() > 1)
                    names.push_back(line);
        }

        for(auto &t : towns)
        {
            for(auto &n : names)
            {
                if(t.name == n)
                    names.erase(std::remove(names.begin(), names.end(), n), names.end()); //if name already taken by another town, find & remove from names vector
            }
        }
        if(names.size() > 0)
        {
            std::random_shuffle(names.begin(), names.end());
            this->name = names.at(0);
        }
        else this->name = std::string("NO_MORE_NAMES!");


}

void townClass::monthTick(std::vector<hexagon> &hexs)
{
            this->population += (this->food-(this->population/100))*5;
            if(this->manPower < this->population/7)
                this->manPower += this->population/12;
            if(this->manPower > this->population/7)
                this->manPower = this->population/7;

            if(floor(this->population/100) > this->townSize)
            {
                int newSize = floor(this->population/100);
                for(auto &tile : hexs)
                {
                    if(tile.distanceTo(this->tile) <= newSize && tile.owner == "noOne" && newSize < 11)
                    {
                        this->ownedTiles.push_back(&tile);
                        tile.owner = this->tile->owner;
                        sf::Color colour = this->tile->ownerHex.getFillColor();
                        tile.ownerHex.setFillColor(colour);
                        this->food += tile.resource.food;
                        this->production += tile.resource.production;

                    }
                }
            }
}

void townClass::generateTradeDeals(std::vector<goodClass> &goods, std::vector<std::vector<hexagon*> > &townPaths)
{
    this->openDeals = std::vector<tradeDealClass>();

    for(auto &tp : townPaths)
    {
        if(tp.at(0)->index == this->tile->index)
        {
            for(auto &g : goods)
            {
                if(g.name != "none")
                {
                    std::string tradeName = g.name;

                    if(tp.size() > 1)
                    {/*
                        if(tp.back()->townOnTile != nullptr)
                            tradeName = g.name + std::string(" from ") + this->name + std::string(" to ") + std::string(tp.back()->townOnTile->name);
                        else
                            tradeName = g.name + std::string(" from ") + this->name + std::string(" to unknown");
                    */}

                    float tradeVolMultiplier = float(rand() % 5 + 20) / float(1000);
                    float tradeVolume = tradeVolMultiplier*g.stdNum;

                    int freqNum = rand() % 5 + 0;
                    timeFrequency tradeFreq = static_cast<timeFrequency>(freqNum);

                    float priceMultiplier = float(rand() % 75 + 98) / float(100);
                    double tradePrice = double(g.price) * double(priceMultiplier) * double(tradeVolume);

                    tradeDealClass newTradeDeal(tradeName, g, tradeVolume, tradePrice, tradeFreq);
                    this->openDeals.push_back(newTradeDeal);
                }
            }
        }
    }

    std::random_shuffle(this->openDeals.begin(), this->openDeals.end());
    this->openDeals.erase(this->openDeals.begin()+3, this->openDeals.end());
    printf("\n\n%s\n%s\n", this->name.c_str(), std::string(50, '*').c_str());
    for(auto &od : this->openDeals)
        printf("%s\t%f\tfor\t%i %s\n", od.name.c_str(), od.payment, static_cast<int>(od.tradeGoodVolume), od.tradeGood.unit.c_str());
}
