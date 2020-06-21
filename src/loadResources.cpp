#include "../include/custom.h"
#include <fstream>
#include <iostream>

std::vector<resourceClass> loadResources(std::vector<terrainClass> &terrains)
{
        printf("Loading Resources...\n");

    std::vector<resourceClass> resources;
    resourceClass none;
    resources.push_back(none);

    std::ifstream resourceCfg;
    resourceCfg.open("configs/resources.txt");

    std::string line;

    if (resourceCfg.is_open())
    {
            while ( std::getline (resourceCfg,line) )
            {
                resourceClass newResource;
                newResource.name = "none";


                std::string token = line.substr(0, line.find(", "));
                line.erase(0, line.find(", ") + 2);
                newResource.name = token;

                token = line.substr(0, line.find(", "));
                line.erase(0, line.find(", ") + 2);
                newResource.textureName = token;

                token = line.substr(0, line.find(", "));
                line.erase(0, line.find(", ") + 2);
                newResource.spawnChance = atoi(token.c_str());

                int n = std::count(line.begin(), line.end(), '|');
                for(n;n>=0;n--)
                {
                    token = line.substr(0, line.find("|"));
                    line.erase(0, line.find("|")+1);
                    for(auto &terr : terrains)
                        if(token == terr.name)
                            newResource.requiredTerrain.push_back(terr.terrain);
                }


                if(newResource.name != "none")
                    resources.push_back(newResource);

            }
    }
    else
    {
        printf("Failed to Load resources.txt!\n");
    }

    for(auto &r : resources)
        printf("%s    ", r.name.c_str());

    printf("\n");

    return resources;

}
