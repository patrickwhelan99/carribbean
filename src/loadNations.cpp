#include "../include/custom.h"
#include <fstream>

bool constructNation(std::shared_ptr<colonialNation> &newNation, std::vector<std::shared_ptr<nationClass> > &nations, std::string line)
{
    std::string token = line.substr(0, line.find(", "));
    line.erase(0, line.find(", ") + 2);
    newNation->name = token;

    token = line.substr(0, line.find(", "));
    line.erase(0, line.find(", ") + 2);
    newNation->possessive = token;

    token = line.substr(0, line.find(", "));
    line.erase(0, line.find(", ") + 2);
    sf::Texture flagTexture;
    flagTexture.loadFromFile(token);
    newNation->flag = flagTexture;

    token = line.substr(0, line.find("\n"));
    std::string colourStr = token.c_str();
    int colourOne = atoi(colourStr.substr(0, colourStr.find("|")).c_str());
    colourStr.erase(0, colourStr.find("|") + 1);

    int colourTwo = atoi(colourStr.substr(0, colourStr.find("|")).c_str());
    colourStr.erase(0, colourStr.find("|") + 1);

    int colourThree = atoi(colourStr.substr(0, colourStr.find("\n")).c_str());

    newNation->colour = sf::Color(colourOne, colourTwo, colourThree, 175);

    if (newNation->name != "none")
        return true;
    else
        return false;
}

bool constructNation(std::shared_ptr<tribalNation> &newNation, std::vector<std::shared_ptr<nationClass> > &nations, std::string line)
{
    std::string token = line.substr(0, line.find(", "));
    line.erase(0, line.find(", ") + 2);
    newNation->name = token;

    token = line.substr(0, line.find(", "));
    line.erase(0, line.find(", ") + 2);
    newNation->possessive = token;

    token = line.substr(0, line.find(", "));
    line.erase(0, line.find(", ") + 2);
    sf::Texture flagTexture;
    flagTexture.loadFromFile(token);
    newNation->flag = flagTexture;

    token = line.substr(0, line.find("\n"));
    std::string colourStr = token.c_str();
    int colourOne = atoi(colourStr.substr(0, colourStr.find("|")).c_str());
    colourStr.erase(0, colourStr.find("|") + 1);

    int colourTwo = atoi(colourStr.substr(0, colourStr.find("|")).c_str());
    colourStr.erase(0, colourStr.find("|") + 1);

    int colourThree = atoi(colourStr.substr(0, colourStr.find("\n")).c_str());

    newNation->colour = sf::Color(colourOne, colourTwo, colourThree, 175);

    if (newNation->name != "none")
        return true;
    else
        return false;
}

std::vector<std::shared_ptr<nationClass> > loadNations(void)
{
     printf("Loading Nations...\n");

    std::vector<std::shared_ptr<nationClass> > nations;

    std::ifstream nationCfg;
    nationCfg.open("nations/nations.txt");
    std::string line;

    if (nationCfg.is_open())
    {
            while ( std::getline (nationCfg,line) )
            {
                if(std::count(line.begin(), line.end(), ',') > 0)
                {

                    std::string token = line.substr(0, line.find(", "));
                    line.erase(0, line.find(", ") + 2);
                    if(token == "col")
                    {
                        std::shared_ptr<colonialNation> colNation(new colonialNation);
                        if(constructNation(colNation, nations, line))
                            nations.push_back(colNation);
                    }
                    else if(token == "tri")
                    {
                        std::shared_ptr<tribalNation> triNation(new tribalNation);
                        if(constructNation(triNation, nations, line))
                            nations.push_back(triNation);
                    }
                    else
                    {
                        std::cerr << "Error loading nation, Nation type undefined!" << std::endl;
                        break;
                    }


                }
            }
    }

    else
       printf("Failed to Load nations.txt!\n");

    return nations;
}
