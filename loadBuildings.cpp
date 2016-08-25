#include "custom.h"
#include <iostream>
#include <fstream>

std::vector<buildingClass> loadBuildings(std::vector<resourceClass> &resources, std::vector<goodClass> &goods)
{
        printf("Loading Buildings!...\n");

    std::vector<buildingClass> buildings;

    std::ifstream buildingCfg;
    buildingCfg.open("buildings.txt");
    std::string line;

    if (buildingCfg.is_open())
    {
            while ( std::getline (buildingCfg,line) )
            {

                if(std::count(line.begin(), line.end(), ',') > 0)
                {

                    buildingClass newBuilding;

                    std::string token = line.substr(0, line.find(", "));
                    line.erase(0, line.find(", ") + 2);
                    newBuilding.name = token;

                    token = line.substr(0, line.find(", "));
                    line.erase(0, line.find(", ") + 2);
                    newBuilding.desc = token;

                    token = line.substr(0, line.find(", "));
                    line.erase(0, line.find(", ") + 2);
                    newBuilding.textureStr = token;

                    token = line.substr(0, line.find(", "));
                    line.erase(0, line.find(", ") + 2);
                    newBuilding.foodOutput = atoi(token.c_str());

                    token = line.substr(0, line.find(", "));
                    line.erase(0, line.find(", ") + 2);
                    newBuilding.productionOutput = atoi(token.c_str());

                    token = line.substr(0, line.find(", "));
                    line.erase(0, line.find(", ") + 2);
                    newBuilding.manpowerOutput = atoi(token.c_str());

                    token = line.substr(0, line.find(", "));
                    line.erase(0, line.find(", ") + 2);
                    bool success = false;
                    for(auto &g : goods)
                        if(g.name == token)
                        {
                            newBuilding.outputGood = g;
                            success = true;
                        }

                    if(!success)
                        printf("ERROR: Loading Building: %s:\t%s is not a good!\n", newBuilding.name.c_str(), token.c_str());

                    token = line.substr(0, line.find(", "));
                    line.erase(0, line.find(", ") + 2);
                    newBuilding.outputGoodVolume = atoi(token.c_str());

                    ///Last Token is required materials to make Building
                    auto n = std::count(line.begin(), line.end(), '|');
                    for(n;n>=0;n--)
                    {
                        token = line.substr(0, line.find("|"));
                        line.erase(0, line.find("|")+1);
                        bool isResource = false;
                        for(auto &r : resources)
                        if(token == r.name)
                        {
                            newBuilding.requiredMaterials.push_back(token);
                            isResource = true;
                            break;
                        }

                        if(!isResource)
                            printf("ERROR: Loading Building: %s:\t%s is not a resource!\n", newBuilding.name.c_str(), token.c_str());
                    }


                if (newBuilding.name != "none")
                    buildings.push_back(newBuilding);
            }
            }
    }
    else
    {
       printf("Failed to Load buildings.txt!\n");
    }

    return buildings;
}
