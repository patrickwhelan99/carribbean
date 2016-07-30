#include "custom.h"

void spawnBoats(std::vector<textureClass> &textures, std::vector<AIBoat> &AIBoats, std::vector<hexagon> &hexs, std::vector<std::vector<hexagon*> > &townPaths)
{
    for(auto &texture : textures)
    {
        if(texture.name == "boatTexture")
        {
            for(int i = 0; i<100; i++)
            {
                AIBoat newBoat(texture, hexs, townPaths);
                AIBoats.push_back(newBoat);
            }
            break;
        }
    }
}
