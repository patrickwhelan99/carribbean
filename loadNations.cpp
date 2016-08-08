#include "custom.h"
#include <fstream>

std::vector<nationClass> loadNations(void)
{
     printf("Loading Nations...\n");

    std::vector<nationClass> nations;

    std::ifstream nationCfg;
    nationCfg.open("nations.txt");
    std::string line;

    if (nationCfg.is_open())
    {
            while ( std::getline (nationCfg,line) )
            {
                nationClass newNation;

                if(std::count(line.begin(), line.end(), ',') > 0)
                {
                    newNation.name = "none";

                    std::string token = line.substr(0, line.find(", "));
                    line.erase(0, line.find(", ") + 2);
                    newNation.name = token;

                    token = line.substr(0, line.find(", "));
                    line.erase(0, line.find(", ") + 2);
                    newNation.possessive = token;

                    token = line.substr(0, line.find("\n"));
                    std::string colourStr = token.c_str();
                    int colourOne = atoi(colourStr.substr(0, colourStr.find("|")).c_str());
                    colourStr.erase(0, colourStr.find("|") + 1);

                    int colourTwo = atoi(colourStr.substr(0, colourStr.find("|")).c_str());
                    colourStr.erase(0, colourStr.find("|") + 1);

                    int colourThree = atoi(colourStr.substr(0, colourStr.find("\n")).c_str());

                    newNation.colour = sf::Color(colourOne, colourTwo, colourThree, 175);
                }


                if (newNation.name != "none")
                    nations.push_back(newNation);
            }
    }

    else
       printf("Failed to Load nations.txt!\n");

    return nations;
}
