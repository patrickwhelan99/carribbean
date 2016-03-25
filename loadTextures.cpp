#include "custom.h"
#include <iostream>
#include <fstream>

std::vector<textureClass> loadTextures(void)
{
        printf("Loading Textures...\n");

    std::vector<textureClass> textures;

    std::ifstream textureCfg;
    textureCfg.open("textures.txt");
    std::string line;

    if (textureCfg.is_open())
    {
            while ( std::getline (textureCfg,line) )
            {
                textureClass newTexture;
                newTexture.name = "none";

                    std::string token = line.substr(0, line.find(", "));
                    line.erase(0, line.find(", ") + 2);

                        newTexture.name = token;


                    token = line.substr(0, line.find(", "));
                    line.erase(0, line.find(", ") + 2);

                        newTexture.loadFromFile(token);





                if (newTexture.name != "none")
                    textures.push_back(newTexture);
            }
    }
    else
    {
        //EXIT_FAILURE;
    }

    return textures;
}
