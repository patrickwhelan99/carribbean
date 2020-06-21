#include "../include/custom.h"

void buildBuilding(buildingClass &building, std::vector<resourceClass> &resources, std::vector<goodClass> &goods, townClass* currentTown)
{
    bool canBuild = true;

///Check if building already built in town
    for(auto &b : currentTown->buildings)
    {
        if(building.name == b.name)
            canBuild = false;
    }

///Check if town has resources neccesary
    for(auto &r : resources)
    {
        int (townClass::*fPtr) (resourceClass resource);
        fPtr = &townClass::resourceCount;
        int a = (currentTown->*fPtr)(r);
        int b = 0;
        for(auto &res : building.requiredMaterials)
        {
            if(res.name == r.name)
                b += 1;
        }

        if(a < b)
            canBuild = false;
    }

///Check if town is producting enough goods for building


            for(auto &good : currentTown->goods)
            {
                if(building.outputGood.name == good.name)
                {
                    if(building.outputGoodVolume < good.num)
                        canBuild = false;
                    break;
                }

            }

///If so remove resources and add building to towns vector
    if(canBuild)
    {
        for(auto &resource : resources)
        {
            int b = 0;
            for(auto &res : building.requiredMaterials)
            {
                if(res.name == resource.name)
                    b += 1;
            }

            int n = 0;

        while(n<b)
            {
                for(auto &t : currentTown->ownedTiles)
                {
                    if(t->resource.name == resource.name)
                    {
                        t->resource = resources.at(0);
                        t->resourceIcon.setFillColor(sf::Color(0, 0, 0, 255));
                        n++;
                    }

                    if(n>=b)
                        break;
                }

            }
        }
        ///Update towns stats and townwindow
        currentTown->buildings.push_back(building);
        currentTown->food += building.foodOutput;
        currentTown->production += building.productionOutput;
        currentTown->manPower += building.manpowerOutput;
        printf("%s has built a %s", currentTown->name.c_str(), building.name.c_str());
    }
}
