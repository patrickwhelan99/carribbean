#include "custom.h"

void genLandTexture(std::vector<hexagon> &hexs, std::vector<sf::Texture> &landTextures)
{
    for(hexagon &hex : hexs)
    {
        hex.setupHexs();
        for(hexagon adjHex : hex.adjacentTiles())
        {
            int i = 0;

            if(hex.terrain < adjHex.terrain)
            {
                hex.adjHexTextures.at(i).setFillColor(adjHex.getFillColor());

            }

            i++;
        }
    }
}
