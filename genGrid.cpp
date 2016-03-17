#include "custom.h"
#include <iostream>

std::vector<hexagon> genGrid(int gridSize)
{

/*******************************************Config Values****************************************************************/
    float jungleChance = 40;
    int landChance = 5;
    int mountainChance = 10;
    int townChance = 2;

/************************************************************************************************************************/
/********************************************Generating hex grid*********************************************************/
    std::vector<hexagon> hexs;
    int jumpCounter = 0;
    int index = 0;

    for (int n = 0; n<gridSize; n++)
        {

        if((n % 2) == 0)
        {
            jumpCounter++;
        }

        for (int i = 0; i<gridSize; i++)
            {
                hexagon hexagon(25, 6);
                if((n % 2) == 0) // every other y
                    hexagon.hex.setPosition(i*43.75 + 43.75*0.5, n*38);
                else
                    hexagon.hex.setPosition(i*43.75, n*38); // 43.75 is 25*1.75     |   40 is 25*1.6
/*
                hexagon.terrain = sea;
                hexagon.setFillColor(sf::Color::Blue);
*/
                hexagon.x = i + jumpCounter;
                hexagon.y = n;
                hexagon.index = index;
                hexs.push_back(hexagon);

                index++;
            }
        }
/************************************************************************************************************************/

/**********************************Generate initial land/jungle*****************************************************************/

        srand(time(NULL));  // Seed the random number generator

        for (auto &tile : hexs)
        {
            int tempLandChance = landChance;

                for(auto &adjacent : tile.adjacentTiles(hexs, gridSize))

                    if (adjacent->terrain == land)
                    {
                        tempLandChance += 20;
                    }

            int randNum = rand() % 100 + 1;
            if (randNum <= tempLandChance)
            {
                tile.terrain = land;
                tile.hex.setFillColor(sf::Color::Green);

            }

        }

/************************************************************************************************************************/

/*********************************Generate Sand and chip away************************************************************/
            for (auto &tile : hexs)
            {
                int randNum = rand() % 100 + 1;

                int adjSea = 0;
                int adjLand = 0;
                int adjSand = 0;
                int adjTown = 0;
                int adjLake = 0;

                for (auto &adjTile : tile.adjacentTiles(hexs, gridSize))
                {
                    switch (adjTile->terrain)
                    {
                        case sea:
                            adjSea++;
                            break;

                        case land:
                            adjLand++;
                            break;

                        case sand:
                            adjSand++;
                            break;

                        case town:
                            adjTown++;
                            break;

                        case lake:
                            adjLake++;
                            break;

                        default:
                            break;
                    }
                }


                if(tile.terrain != land && adjLand > 1 && randNum <= 65)    //Gen Sand
                    {
                        if (adjSand > 1)    //if sand > 1 thick; then Sand -> Land
                        {
                            tile.terrain = land;
                            tile.hex.setFillColor(sf::Color::Green);
                        }
                        else // Make SAND BABIES
                        {
                            tile.terrain = sand;
                            tile.hex.setFillColor(sf::Color::Yellow);
                        }

                    }

                    if (adjSea > 4)
                        {
                            //std::cout << "Chipping away!" << std::endl;
                            tile.terrain = sea;
                            tile.hex.setFillColor(sf::Color::Blue);
                        }



            }
/************************************************************************************************************************/

/********************************************Place SEA/LAND/TOWN/LAKE****************************************************/
            for (auto &tile : hexs)
            {
                int adjSea = 0;
                int adjLand = 0;
                int adjSand = 0;
                int adjTown = 0;
                int adjLake = 0;

                for (auto &adjTile : tile.adjacentTiles(hexs, gridSize))
                {
                    switch (adjTile->terrain)
                    {
                        case sea:
                            adjSea++;
                            break;

                        case land:
                            adjLand++;
                            break;

                        case sand:
                            adjSand++;
                            break;

                        case town:
                            adjTown++;
                            break;

                        case lake:
                            adjLake++;
                            break;

                        default:
                            break;
                    }

                }


                    int randNum = rand() % 100 + 1;

                    if (randNum <= jungleChance && adjSea == 0)
                    {
                        tile.terrain = jungle;
                        tile.hex.setFillColor(sf::Color(50, 200, 50));
                    }

                    randNum = rand() % 100 + 1;

                    if(tile.terrain == land && adjLand > 0 && randNum <= townChance && adjTown == 0 && adjSea > 0)
                    {
                        tile.terrain = town;
                        tile.hex.setFillColor(sf::Color::White);
                    }

                    randNum = rand() % 100 + 1;

                    if (randNum <= mountainChance && adjSea < 1)
                    {
                        tile.terrain = mountain;
                        tile.hex.setFillColor(sf::Color(0, 0, 0));
                    }

                    randNum = rand() % 100 + 1;

                    if(adjSea < 1 && tile.terrain == sea)
                    {
                        tile.terrain = lake;
                        tile.hex.setFillColor(sf::Color(0, 200, 255));
                    }
                }

/************************************************************************************************************************/

/****************************************Print tiles*********************************************************************/
        int landCountWhole = 0;
        int seaCountWhole = 0;
        int sandCountWhole = 0;
        int jungleCountWhole = 0;
        int mountainCountWhole = 0;
        int townCountWhole = 0;
        int lakeCountWhole = 0;
        int total = 0;
                for (auto &tile : hexs)
                {
                    if(tile.terrain == sea)
                    {
                        seaCountWhole ++;
                    }
                    if(tile.terrain == land)
                    {
                        landCountWhole ++;
                    }
                    if(tile.terrain == sand)
                    {
                        sandCountWhole ++;
                    }
                    if(tile.terrain == jungle)
                    {
                        jungleCountWhole ++;
                    }
                    if(tile.terrain == mountain)
                    {
                        mountainCountWhole ++;
                    }
                    if(tile.terrain == town)
                    {
                        townCountWhole ++;
                    }
                    if(tile.terrain == lake)
                    {
                        lakeCountWhole ++;
                    }

                    total++;
                }





printf("Tiles: %i\nSeaTiles: %i\nLandTiles: %i\nBeaches: %i\nJungles: %i\nMountains: %i\nTowns: %i\nLakes: %i\n", total, seaCountWhole, landCountWhole, sandCountWhole, jungleCountWhole, mountainCountWhole, townCountWhole, lakeCountWhole);



    return hexs;
}
