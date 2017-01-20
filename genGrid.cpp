#include "custom.h"
#include <iostream>

void genGrid(std::vector<hexagon> &hexs, int gridSize, uint32_t seed, sf::View &camera, std::vector<std::shared_ptr<nationClass> > &nations, std::vector<resourceClass> &resources, std::vector<textureClass> &textures, std::vector<townClass> &towns, std::vector<AIBoat> &AIBoats, std::vector<int> &edgeTiles, std::vector<goodClass> &goods, sf::RenderWindow &app)
{

/*********************************************Config Values****************************************************************/

    int jungleChance = 3;
    int landChance = 5;
    int sandChance = 65;
    int mountainChance = 10;
    int townChance = 30;
    int minTowns = 13;
    int maxTowns = 13;


/*********************************************Generating hex grid*********************************************************/
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
                if((n % 2) == 0) /// every other y
                    hexagon.hex.setPosition(i*hexagon.hex.getLocalBounds().width + hexagon.hex.getLocalBounds().width/2, n*hexagon.hex.getLocalBounds().height*.75);
                else
                    hexagon.hex.setPosition(i*hexagon.hex.getLocalBounds().width, n*hexagon.hex.getLocalBounds().height*.75);

                hexagon.resourceIcon.setPosition(hexagon.hex.getPosition().x, hexagon.hex.getPosition().y);
                hexagon.ownerHex.setPosition(hexagon.hex.getPosition().x, hexagon.hex.getPosition().y);
                hexagon.x += (i + jumpCounter);
                hexagon.y = gridSize - n;
                hexagon.z = (hexagon.x + hexagon.y)*-1;
                hexagon.index = index;
                hexs.push_back(hexagon);

                if(n == 0 || n == gridSize-1 || i == 0 || i == gridSize-1)
                    edgeTiles.push_back(index);

                if((i == gridSize/2) && (n == gridSize/2))
                    camera.setCenter(hexagon.hex.getPosition());

                index++;

            }
        }
/************************************************************************************************************************/

/**********************************Generate initial land*****************************************************************/

        srand(seed);  /// Seed the random number generator

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
                    switch (adjTile->terrain.terrain)
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


                if(tile.terrain.terrain != land && adjLand > 1 && randNum <= sandChance)    //Gen Sand
                    {
                        if (adjSand > 1)    ///if sand > 1 thick; then Sand -> Land
                        {
                            tile.terrain = land;
                            tile.movementPoints = 1;
                        }
                        else /// Place Sand
                        {
                            tile.terrain = sand;
                            tile.movementPoints = 2;
                        }

                    }

                    if (adjSea > 4)
                    {
                        tile.terrain = sea;
                        tile.movementPoints = 3;
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
                        tile.movementPoints = 3;
                    }

                    randNum = rand() % 100 + 1;

                    if (randNum <= mountainChance && TC.adjSea < 1)
                    {
                        tile.terrain = mountain;
                        tile.movementPoints = 4;
                    }
            }


/// LAKE CHECK
            for (auto &tile : hexs)
            {
                adjTileCounter TC = tile.countAdjacentTiles(hexs, gridSize);
                    if(TC.adjSea < 1 && tile.terrain == sea)
                    {
                        tile.terrain = lake;
                        tile.movementPoints = 1;
                    }
                    else if(TC.adjSea < 3 && tile.terrain == sea)
                    {
                        bool canLake = true;

                        for(auto &t : tile.adjacentTiles(hexs, gridSize))
                        {
                            if(t->terrain == sea)
                            {
                                adjTileCounter tCounter = t->countAdjacentTiles(hexs, gridSize);
                                if(tCounter.adjSea > 2)
                                    canLake = false;
                            }
                        }

                        if(canLake)
                        {
                            tile.terrain = lake;
                            for(auto &t : tile.adjacentTiles(hexs, gridSize))
                            {
                                if(t->terrain == sea)
                                {
                                    t->terrain = lake;
                                }
                            }
                        }
                    }
            }


            for(auto &tile : hexs)
                if(tile.terrain == lake)
                {
                    adjTileCounter TC = tile.countAdjacentTiles(hexs, gridSize);
                    if(TC.adjSea > 0)
                        for(auto &t : tile.adjacentTiles(hexs, gridSize))
                        {
                            if(t->terrain == sea)
                            {
                                t->terrain = sand;
                            }
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
                                    tile.resource = resourceThing;
                                }
                            }
                        }

                    for (auto &texture : textures)
                    {
                        if(texture.name == tile.resource.textureName)
                            tile.resourceIcon.setTexture(&texture);
                    }

                }
            }

/************************************************************************************************************************/

/********************************************Place Towns*****************************************************************/



                std::vector<std::shared_ptr<colonialNation> > colNations;
                for(std::shared_ptr<nationClass> &nation : nations)
                {
                    std::shared_ptr<colonialNation> nationPtr = std::dynamic_pointer_cast<colonialNation>(nation);
                    if(nationPtr)   /// if downcast successful then push onto colonial nations
                        colNations.push_back(nationPtr);
                }

                while(towns.size() < minTowns)
                {
                    for (auto &tile : hexs)
                    {
                        if(maxTowns != 0 && towns.size() >= maxTowns)
                            break;

                        int adjResource = 0;

                        for (auto &adjTile : tile.adjacentTiles(hexs, gridSize))
                        {
                            if(adjTile->resource.name != "none")
                                adjResource += 1;
                        }


                        int randNum = rand() % 100 + 1;
                        auto TC = tile.countAdjacentTiles(hexs, gridSize);

                        if(tile.terrain == land && TC.adjLand > 0 && randNum <= townChance && TC.adjTown == 0 && TC.adjSea > 0 && tile.resource.name == "none" && adjResource > 1)
                        {
                            tile.terrain = town;
                            tile.movementPoints = 1;
                            randNum = rand() % colNations.size() + 0;

                            tile.owner = colNations.at(randNum)->name;
                            tile.ownerHex.setFillColor(colNations.at(randNum)->colour);
/*
                            for(auto &adj : tile.adjacentTiles(hexs, gridSize))
                            {
                                adj->owner = nations.at(randNum).name;
                                adj->ownerHex.setFillColor(nations.at(randNum).colour);
                            }
*/
                            std::vector<hexagon*> adjTiles = tile.adjacentTiles(hexs, gridSize);
                            std::shared_ptr<colonialNation> nation = colNations.at(randNum);
                            townClass newTown(&hexs.at(tile.index), adjTiles, hexs, gridSize, goods, nation.get());
                            newTown.setTownName(towns);
                            towns.push_back(newTown);
                            hexs.at(tile.index).townOnTile = &towns.back();

                        }
                    }
                }



            for(auto &t : textures)
            {
                for(auto &hex : hexs)
                {
                    if(t.name == std::string(hex.terrain.name + std::string("Texture"))) /// Terrain type: sea | resolves to "seaTexture"
                        hex.hex.setTexture(&t);
                }
            }

/************************************************************************************************************************/

/****************************************Print tiles*********************************************************************/

///WORLD SEED
                printf("\n\n\n%s\nWORLD SEED:\t%i\n%s\n\n\n", std::string(50, '*').c_str(), seed, std::string(50, '*').c_str());
///TERRAIN
                std::vector<Terrain> terrains;
                for(auto &t : hexs)
                    terrains.push_back(t.terrain.terrain);

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
                    printf("%s - %i\n", r.name.c_str(), static_cast<int>(std::count(resourceSpawns.begin(), resourceSpawns.end(), r.name)));


///TOWNS
                std::vector<std::string> townSpawns;
                for(auto &t : hexs)
                    if(t.terrain == town)
                        townSpawns.push_back(t.owner);
                printf("%s\n%sTOWNS%s\n%s\n", std::string(50, '*').c_str(), std::string(3, '\t').c_str(), std::string(3, '\t').c_str(), std::string(50, '*').c_str());
                for(auto &n : nations)
                    printf("%s - %i\n", n->name.c_str(), static_cast<int>(std::count(townSpawns.begin(), townSpawns.end(), n->name)));

                printf("Total - %i\n", static_cast<int>(townSpawns.size()));


                for(auto &tile : hexs)
                {
                    tile.g = tile.movementPoints;
                }

}
