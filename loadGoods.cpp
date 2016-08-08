#include "custom.h"
#include <iostream>
#include <fstream>

std::vector<goodClass> loadGoods(std::vector<resourceClass> &resources)
{
        printf("Loading Goods...\n");

    std::vector<goodClass> goods;

    std::ifstream goodCfg;
    goodCfg.open("goods.txt");
    std::string line;

    if (goodCfg.is_open())
    {
            while ( std::getline (goodCfg,line) )
            {

                if(std::count(line.begin(), line.end(), ',') > 0)
                {

                    goodClass newGood;
                    newGood.name = "none";

                    std::string token = line.substr(0, line.find(", "));
                    line.erase(0, line.find(", ") + 2);
                    newGood.name = token;

                    token = line.substr(0, line.find(", "));
                    line.erase(0, line.find(", ") + 2);
                    newGood.unit = token;

                    token = line.substr(0, line.find(", "));
                    line.erase(0, line.find(", ") + 2);
                    newGood.stdNum = atoi(token.c_str());

                    token = line.substr(0, line.find(", "));
                    line.erase(0, line.find(", ") + 2);
                    newGood.price = atof(token.c_str());

                    token = line.substr(0, line.find(", "));
                    line.erase(0, line.find(", ") + 2);
                    newGood.textureName = token;

                    ///Last Token is required materials to make good
                    token = line.substr(0, line.find("/n"));
                    line.erase(0, line.find("/n") + 1);
                    auto n = std::count(line.begin(), line.end(), '|');
                    for(n;n>=0;n--)
                    {
                        token = line.substr(0, line.find("|"));
                        line.erase(0, line.find("|") + 1);
                        bool isResource = false;
                        for(auto &r : resources)
                        if(token == r.name)
                        {
                            newGood.materials.push_back(token);
                            isResource = true;
                            break;
                        }

                        if(!isResource)
                            printf("ERROR: Loading Good: %s:\t%s is not a resource!\n", newGood.name.c_str(), token.c_str());
                    }

                if (newGood.name != "none")
                    goods.push_back(newGood);
            }
            }
    }
    else
    {
       printf("Failed to Load goods.txt!\n");
    }

    return goods;
}
