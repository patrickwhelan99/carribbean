#include "custom.h"

void AIBattleLoop(std::vector<AIBoat> &AIBoats, playerClass &player, std::vector<sf::RectangleShape> &nodes, sf::FloatRect &intersectionRect, std::clock_t &start)
{
    double duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

    for(AIBoat &b : AIBoats)
    {
        if(!intersectionRect.contains(b.getPosition()))
            b.inactive = true;



        if(duration > 3.0f)
        {
            int randNumX = rand() % 5 + 1;
            int randNumY = rand() % 5 + 1;

            if(randNumX % 2 == 0)
                randNumX *= -1;

            if(randNumY % 2 != 0)
                randNumY *= -1;

            b.battleMovement = sf::Vector2f(float(randNumX)/float(400), float(randNumY)/float(400));
        }

        b.move(b.battleMovement);
    }

    if(duration > 3.0f)
        start = std::clock();
}
