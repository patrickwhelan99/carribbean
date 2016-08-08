#include "custom.h"
#include <iostream>

void genGrid(std::vector<hexagon> &hexs, int gridSize, int seed, sf::View &camera, std::vector<nationClass> &nations, std::vector<resourceClass> &resources, std::vector<textureClass> &textures, std::vector<townClass> &towns, std::vector<AIBoat> &AIBoats, std::vector<int> &edgeTiles)
{

/*******************************************Config Values****************************************************************/

    int jungleChance = 3;
    int landChance = 5;
    int sandChance = 65;
    int mountainChance = 10;
    int townChance = 5;

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
                    hexagon.hex.setPosition(i*43.75*200 + 43.75*100, n*38*200);
                else
                    hexagon.hex.setPosition(i*43.75*200, n*38*200); // 43.75 is 25*1.75     |   40 is 25*1.6

                hexagon.resource.icon.setPosition(hexagon.hex.getPosition().x + 10*200, hexagon.hex.getPosition().y + 10*200);
                hexagon.ownerHex.setPosition(hexagon.hex.getPosition().x, hexagon.hex.getPosition().y);
                hexagon.x += (i + jumpCounter);
                hexagon.y = gridSize - n;
                hexagon.z = (hexagon.x + hexagon.y)*-1;
                hexagon.index = index;
                hexagon.resource = resources.at(0); // Default | none
                hexs.push_back(hexagon);

                if(n == 0 || n == gridSize-1 || i == 0 || i == gridSize-1)
                    edgeTiles.push_back(index);

                if((i == gridSize/2) && (n == gridSize/2))
                    camera.setCenter(hexagon.hex.getPosition());

                index++;

            }
        }
/************************************************************************************************************************/

/**********************************Generate initial land/jungle*****************************************************************/

        srand(seed);  // Seed the random number generator

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

/********************************************Place JUNGLE/MOUNTAIN/LAKE**************************************************/

            for (auto &tile : hexs)
            {
                adjTileCounter TC = tile.countAdjacentTiles(hexs, gridSize);

                    int randNum = rand() % 100 + 1;

                    if (randNum <= jungleChance && TC.adjSea != 6)
                    {
                        tile.terrain = jungle;
                        tile.hex.setFillColor(sf::Color(50, 200, 50));
                        tile.movementPoints = 3;
                    }

                    randNum = rand() % 100 + 1;

                    if (randNum <= mountainChance && TC.adjSea < 1)
                    {
                        tile.terrain = mountain;
                        tile.hex.setFillColor(sf::Color(0, 0, 0));
                        tile.movementPoints = 4;
                    }

                    randNum = rand() % 100 + 1;

                    if(TC.adjSea < 1 && tile.terrain == sea)
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
                        tile.resource.icon.setTexture(&texture);
                }

            }


/************************************************************************************************************************/

/********************************************Place Towns*****************************************************************/

                int adjResource = 0;

                for (auto &adjTile : tile.adjacentTiles(hexs, gridSize))
                {
                    if(adjTile->resource.name != "none")
                        adjResource += 1;
                }

                    auto TC = tile.countAdjacentTiles(hexs, gridSize);

                    int randNum = rand() % 100 + 1;

                    if(tile.terrain == land && TC.adjLand > 0 && randNum <= townChance && TC.adjTown == 0 && TC.adjSea > 0 && tile.resource.name == "none" && adjResource > 0)
                    {
                        tile.terrain = town;
                        tile.hex.setFillColor(sf::Color::White);
                        tile.movementPoints = 1;
                        randNum = rand() % nations.size() + 0;

                        tile.owner = nations.at(randNum).name;
                        tile.ownerHex.setFillColor(nations.at(randNum).colour);

                        for(auto &adj : tile.adjacentTiles(hexs, gridSize))
                        {
                            adj->owner = nations.at(randNum).name;
                            adj->ownerHex.setFillColor(nations.at(randNum).colour);
                        }


                        std::vector<hexagon*> adjTiles = tile.adjacentTiles(hexs, gridSize);
                        townClass newTown(&hexs.at(tile.index), adjTiles, hexs, gridSize);
                        newTown.setTownName(towns);
                        towns.push_back(newTown);
                        hexs.at(tile.index).townOnTile = &towns.back();

                    }
            }


/************************************************************************************************************************/

/****************************************Print tiles*********************************************************************/

///WORLD SEED
                printf("\n\n\n%s\nWORLD SEED:\t%i\n%s\n\n\n", std::string(50, '*').c_str(), seed, std::string(50, '*').c_str());
///TERRAIN
                std::vector<Terrain> terrains;
                for(auto &t : hexs)
                    terrains.push_back(t.terrain);

                int seaCount = std::count(terrains.begin(), terrains.end(), sea);
                int landCount = std::count(terrains.begin(), terrains.end(), land);
                int sandCount = std::count(terrains.begin(), terrains.end(), sand);
                int lakeCount = std::count(terrains.begin(), terrains.end(), lake);
                int jungleCount = std::count(terrains.begin(), terrains.end(), jungle);
                int mountainCount = std::count(terrains.begin(), terrains.end(), mountain);
                int townCount = std::count(terrains.begin(), terrains.end(), town);
                printf("%s\n%sTERRAIN%s\n%s\nSea - %i\nLand - %i\nSand - %i\nLake - %i\nJungle - %i\nMountain - %i\nTown - %i\n", std::string(50, '*').c_str(), std::string(3, '\t').c_str(), std::string(3, '\t').c_str(), std::string(50, '*').c_str(), seaCount, landCount, sandCount, lakeCount, jungleCount, mountainCount, townCount);

///RESOURCES
                std::vector<std::string> resourceSpawns;
                for(auto &t : hexs)
                    if(t.resource.name != "none")
                        resourceSpawns.push_back(t.resource.name);
                printf("%s\n%sRESOURCES%s\n%s\n", std::string(50, '*').c_str(), std::string(3, '\t').c_str(), std::string(3, '\t').c_str(), std::string(50, '*').c_str());
                for(auto &r : resources)
                    printf("%s - %i\n", r.name.c_str(), std::count(resourceSpawns.begin(), resourceSpawns.end(), r.name));


///TOWNS
                std::vector<std::string> townSpawns;
                for(auto &t : hexs)
                    if(t.terrain == town)
                        townSpawns.push_back(t.owner);
                printf("%s\n%sTOWNS%s\n%s\n", std::string(50, '*').c_str(), std::string(3, '\t').c_str(), std::string(3, '\t').c_str(), std::string(50, '*').c_str());
                for(auto &n : nations)
                    printf("%s - %i\n", n.name.c_str(), std::count(townSpawns.begin(), townSpawns.end(), n.name));


                for(auto &tile : hexs)
                {
                    tile.g = tile.movementPoints;
                }

}
