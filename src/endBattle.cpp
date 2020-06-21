#include "../include/custom.h"

void endBattle(playerClass &player, std::vector<AIBoat> &AIBoats, const bool &playerVictory)
{
    if(playerVictory)
    {
        for(goodClass &g : player.inventory)
            printf("%s:\t%i\n", g.name.c_str(), g.num);

        int i = 0;
        for(AIBoat &b : AIBoats)
        {
            for(goodClass &g : b.inventory)
            {
                player.inventory.at(i).num += g.num;
            }
            i++;
        }

        printf("\nAFTERWARDS\n\n");
        for(goodClass &g : player.inventory)
            printf("%s:\t%i\n", g.name.c_str(), g.num);
    }
    else
    {

    }
    player.setPosition(player.currentHex->resourceIcon.getPosition().x - player.currentHex->hex.getLocalBounds().width/4, player.currentHex->resourceIcon.getPosition().y - player.currentHex->hex.getLocalBounds().height/4);
}
