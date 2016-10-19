#include "custom.h"

void spawnBoats(std::vector<textureClass> &textures, std::vector<AIBoat> &AIBoats, std::vector<hexagon> &hexs, std::vector<std::vector<hexagon*> > &townPaths, std::vector<townClass> &towns, std::vector<goodClass> &goods)
{
    for(auto &texture : textures)
    {
        if(texture.name == "boatTexture")
        {
            for(int i = 0; i<1000; i++)
            {
                AIBoat newBoat(texture, hexs, townPaths, towns, goods);
                AIBoats.push_back(newBoat);
            }
            break;
        }
    }
}
