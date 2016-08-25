#include "custom.h"

void monthtick(std::vector<townClass> &towns, std::vector<hexagon> &hexs, std::vector<resourceClass> resources, std::vector<goodClass> &goods, std::vector<std::vector<hexagon*> > &townPaths)
{
    for(auto &town : towns)
        {
            town.monthTick(hexs);
            town.generateTradeDeals(goods, townPaths);
        }
}
