#include "custom.h"

void monthtick(std::vector<townClass> &towns, std::vector<goodClass> &goods, std::vector<std::vector<hexagon*> > &townPaths, std::vector<AIBoat> &AIBoats, std::vector<textureClass> &textures, std::vector<hexagon> &hexs, std::vector<std::shared_ptr<nationClass> > &nations, std::vector<buildingClass> &buildings, std::vector<resourceClass> &resources)
{
    for(auto &town : towns)
        {
            town.monthTick(hexs);
            town.generateTradeDeals(goods, townPaths, AIBoats, textures, hexs, towns);

            for(buildingClass &b : buildings)
            {
                buildBuilding(b, resources, goods, &town);
            }
        }

    for(auto &n : nations)
    {
        for(auto &t : towns)
        {
            if(t.tile->owner == n->name)
            {
                n->money += t.income;
            }
        }
    }

    printf("%s\n", std::string(50, '*').c_str());
    printf("%s\tINCOME\t%s\n", std::string(10, '*').c_str(), std::string(10, '*').c_str());
    for(auto &n : nations)
        printf("%s:\t%f\n", n->name.c_str(), n->money);
    printf("%s\n", std::string(50, '*').c_str());

}
