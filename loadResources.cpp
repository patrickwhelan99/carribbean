#include "custom.h"
#include <fstream>
#include <iostream>

std::vector<resourceClass> loadResources(void)
{
        printf("Loading Resources...\n");

    std::vector<resourceClass> resources;
    resourceClass none;
    resources.push_back(none);

    std::ifstream resourceCfg;
    resourceCfg.open("resources.txt");

    std::string line;

    if (resourceCfg.is_open())
    {
            while ( std::getline (resourceCfg,line) )
            {
                size_t n = std::count(line.begin(), line.end(), ',');
                size_t i = n;

                resourceClass newResource;
                newResource.name = "none";


                for(n+1;0<n;n--)
                {
                    std::string token = line.substr(0, line.find(", "));
                    line.erase(0, line.find(", ") + 2);

                    if(n == i)
                        newResource.name = token;

                    if(n == i-1)
                        newResource.textureName = token;

                    if(n == i-2)
                        newResource.spawnChance = atoi(token.c_str());

                    if(n == i-3)
                        newResource.food = atoi(token.c_str());

                    if(n <= i-4)
                        newResource.production = atoi(token.c_str());

                        if(token == "sea")
                            newResource.requiredTerrain.push_back(sea);
                        if(token == "land")
                            newResource.requiredTerrain.push_back(land);
                        if(token == "jungle")
                            newResource.requiredTerrain.push_back(jungle);
                        if(token == "mountain")
                            newResource.requiredTerrain.push_back(mountain);
                        if(token == "sand")
                            newResource.requiredTerrain.push_back(sand);
                        if(token == "town")
                            newResource.requiredTerrain.push_back(town);
                        if(token == "lake")
                            newResource.requiredTerrain.push_back(lake);

                }

                if(newResource.name != "none")
                    resources.push_back(newResource);

            }
    }
    else
    {
        printf("Failed to Load resources.txt!\n");
    }

    return resources;

}
