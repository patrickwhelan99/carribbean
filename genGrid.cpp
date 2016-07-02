#include "custom.h"
#include <iostream>

void genGrid(std::vector<hexagon> &hexs, int gridSize, sf::View &camera, std::vector<resourceClass> &resources, std::vector<textureClass> &textures, std::vector<townClass> &towns, std::vector<AIBoat> &AIBoats)
{

/*******************************************Config Values****************************************************************/


    int jungleChance = 40;
    int landChance = 5;
    int sandChance = 65;
    int mountainChance = 10;
    int townChance = 2;


/************************************************************************************************************************/

/********************************************Generating hex grid*********************************************************/
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
                hexagon hexagon;
                if((n % 2) == 0) // every other y
                {
                    hexagon.hex.setPosition(i*43.75*200 + 43.75*100, n*38*200);
                }
                else
                {
                    hexagon.hex.setPosition(i*43.75*200, n*38*200); // 43.75 is 25*1.75     |   40 is 25*1.6
                }

                hexagon.resource.icon.setPosition(hexagon.hex.getPosition().x + 10*200, hexagon.hex.getPosition().y + 10*200);
                hexagon.ownerHex.setPosition(hexagon.hex.getPosition().x, hexagon.hex.getPosition().y);
                hexagon.x += (i + jumpCounter);
                hexagon.y = gridSize - n;
                hexagon.z = (hexagon.x + hexagon.y)*-1;
                hexagon.index = index;
                hexs.push_back(hexagon);

                if((i == gridSize/2) && (n == gridSize/2))
                {
                    camera.setCenter(hexagon.hex.getPosition());
                }

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
                tile.movementPoints = 1;

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


                if(tile.terrain != land && adjLand > 1 && randNum <= sandChance)    //Gen Sand
                    {
                        if (adjSand > 1)    //if sand > 1 thick; then Sand -> Land
                        {
                            tile.terrain = land;
                            tile.hex.setFillColor(sf::Color::Green);
                            tile.movementPoints = 1;
                        }
                        else // Make SAND BABIES
                        {
                            tile.terrain = sand;
                            tile.hex.setFillColor(sf::Color::Yellow);
                            tile.movementPoints = 2;
                        }

                    }

                    if (adjSea > 4)
                        {
                            //std::cout << "Chipping away!" << std::endl;
                            tile.terrain = sea;
                            tile.hex.setFillColor(sf::Color::Blue);
                            tile.movementPoints = 1;
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
                        tile.movementPoints = 3;
                    }
///TOWN WAS ERE

                    randNum = rand() % 100 + 1;

                    if (randNum <= mountainChance && adjSea < 1)
                    {
                        tile.terrain = mountain;
                        tile.hex.setFillColor(sf::Color(0, 0, 0));
                        tile.movementPoints = 4;
                    }

                    randNum = rand() % 100 + 1;

                    if(adjSea < 1 && tile.terrain == sea)
                    {
                        tile.terrain = lake;
                        tile.hex.setFillColor(sf::Color(0, 200, 255));
                        tile.movementPoints = 1;
                    }
                }

/************************************************************************************************************************/

/********************************************Place Resources*************************************************************/
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


                for(auto &resourceThing : resources)
                {
                    int randNum = rand() % 100 + 1;
                    for(auto &reqTerrain : resourceThing.requiredTerrain)
                    {

                        if(tile.terrain == reqTerrain)
                        {

                            if(randNum < resourceThing.spawnChance)
                            {
                                tile.resource.name = resourceThing.name;
                                tile.resource.textureName = resourceThing.textureName;
                                tile.resource.food = resourceThing.food;
                                tile.resource.production = resourceThing.production;
                            }
                        }
                    }

                for (auto &texture : textures)
                    {

                        if(texture.name == tile.resource.textureName)
                        {
                            tile.resource.icon.setTexture(&texture);
                        }

                    }

                }

            }

            for(auto &tile : hexs)
            {

                int adjSea = 0;
                int adjLand = 0;
                int adjSand = 0;
                int adjTown = 0;
                int adjLake = 0;
                int adjResource = 0;

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

                    if(adjTile->resource.name != "none")
                        adjResource += 1;

                }

                    int randNum = rand() % 100 + 1;

                    if(tile.terrain == land && adjLand > 0 && randNum <= townChance && adjTown == 0 && adjSea > 0 && tile.resource.name == "none" && adjResource > 0)
                    {
                        tile.terrain = town;
                        tile.hex.setFillColor(sf::Color::White);
                        tile.movementPoints = 1;
                        randNum = rand() % 100 + 1;
                        if (randNum < 25)
                         {tile.ownerHex.setFillColor(sf::Color(255, 0, 50, 50));    tile.owner = england;}; // England
                        if (24 < randNum && randNum < 51) {tile.ownerHex.setFillColor(sf::Color(255, 50, 255, 50));    tile.owner = portugal;}; // Portugal
                        if (50 < randNum && randNum < 76) {tile.ownerHex.setFillColor(sf::Color(0, 255, 255, 50));    tile.owner = france;}; // France
                        if (75 < randNum && randNum < 101) {tile.ownerHex.setFillColor(sf::Color(255, 255, 50, 50));    tile.owner = spain;}; // Spain


                        std::vector<hexagon*> adjTiles = tile.adjacentTiles(hexs, gridSize);
                        townClass newTown(&hexs.at(tile.index), adjTiles, tile.owner);
                        towns.push_back(newTown);

                    }
            }


/************************************************************************************************************************/

/****************************************Print tiles*********************************************************************/

            std::vector<counter> tileCounters;

                for (int a = 1; a!=8; a++)
                {
                    counter newCounter;
                    newCounter.terrain = static_cast<Terrain>(a);
                    switch (newCounter.terrain)
                    {
                        case 1:
                            newCounter.name = "Sea Tiles";
                            break;
                        case 2:
                            newCounter.name = "Land Tiles";
                            break;
                        case 3:
                            newCounter.name = "Mountain Tiles";
                            break;
                        case 4:
                            newCounter.name = "Sand Tiles";
                            break;
                        case 5:
                            newCounter.name = "Jungle Tiles";
                            break;
                        case 6:
                            newCounter.name = "Town Tiles";
                            break;
                        case 7:
                            newCounter.name = "Lake Tiles";
                            break;

                        default:
                            break;
                    }
                tileCounters.push_back(newCounter);
                }


            std::vector<counter> ownerCounters;
                for (int a = 1; a!=5; a++)
                {
                    counter newCounter;
                    newCounter.owner = static_cast<Owner>(a);
                    switch (newCounter.owner)
                    {
                        case 1:
                            newCounter.name = "English";
                            break;
                        case 2:
                            newCounter.name = "Portruguese";
                            break;
                        case 3:
                            newCounter.name = "Spanish";
                            break;

                        case 4:
                            newCounter.name = "French";
                            break;

                        default:
                            break;
                    }
                ownerCounters.push_back(newCounter);
                }

            std::vector<counter> resourceCounters;
                for (auto &resource : resources)
                {
                    counter newCounter;
                    newCounter.name = resource.name;
                    newCounter.spawnTerrains = resource.requiredTerrain;
                    resourceCounters.push_back(newCounter);
                }



                for (auto &tile : hexs)
                {
                    for(auto &counter : resourceCounters)
                    {
                        if(tile.resource.name == counter.name) {counter.total++;};
                    }

                    for(auto &counter : tileCounters)
                    {
                        if(tile.terrain == counter.terrain) {counter.total++;};
                    }

                    for(auto &counter : ownerCounters)
                    {
                        if(tile.owner == counter.owner && tile.terrain == town) {counter.total++;};
                    }

                }


                printf("\n\nTiles:\n\n");
                for (auto &counter : tileCounters)
                {
                    counter.percentage = ((float(counter.total)/float((gridSize*gridSize)))*100);
                    printf("%s:    %i   %f%% of total\n", counter.name.c_str(), counter.total, counter.percentage);
                }

                printf("\n\nResources:\n\n");
                for (auto &counter : resourceCounters)
                {
                    int totalTiles = 0; // divide by 0 error possible
                    for(auto &terrain : counter.spawnTerrains)
                    {
                        for (auto &counter1 : tileCounters)
                        {
                            if(terrain == counter1.terrain)
                                totalTiles += counter1.total;
                        }

                    }

                    counter.percentage = ((float(counter.total)/float(totalTiles))*100);
                    printf("%s:    %i   %f%% of possible spawnable tiles\n", counter.name.c_str(), counter.total, counter.percentage);
                }

                printf("\n\nCountries:\n\n");
                for (auto &counter : ownerCounters)
                {
                    int townsTotal;
                    for (auto &counter : tileCounters)
                    {
                        if(counter.terrain == town)
                            townsTotal = counter.total;
                    }
                    counter.percentage = ((float(counter.total)/float((townsTotal)))*100);
                    printf("%s:    %i   %f%% of towns\n", counter.name.c_str(), counter.total, counter.percentage);
                }






                for(auto &tile : hexs)
                {
                    tile.g = tile.movementPoints;
                }

}
