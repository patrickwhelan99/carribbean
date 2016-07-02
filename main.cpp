#include "custom.h"

#include <SFML/Graphics.hpp>
#include <iostream>

/* The following are for rand*/
#include <stdlib.h>
#include <random>
#include <time.h>
/*---------------------------*/
#include <fstream>
#include <ctime> // for clock
#include <algorithm> // for clock
#include <thread>
#include <cmath>
#include <future>

int main(int argc, char* argv[])
{
    // Create the main window and camera
    sf::RenderWindow app(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "Gen that Land"/*, sf::Style::Fullscreen*/);
    int gridSize;

    if(argc > 1)
        gridSize = atoi(argv[1]);
    else
        gridSize = 100;

    sf::View camera;
    camera.setSize(sf::VideoMode::getDesktopMode().width*(gridSize/48)*200, sf::VideoMode::getDesktopMode().height*(gridSize/48)*200);
    camera.setCenter(0, 0);
    app.setView(camera);

    sf::View hudView;
    hudView.setSize(1000, 1000);
    hudView.setCenter(0, 0);

    //  Load textures and resources using *.txt files
    std::vector<textureClass> textures = loadTextures();
    if(textures.size() == 0)
        app.close();
    std::vector<resourceClass> resources = loadResources();
    if(resources.size() == 0)
        app.close();

    // Generate the grid
        // Setup timer
        std::clock_t start;
        double duration;
        start = std::clock();

    printf("Creating Grid!...\n");
    std::vector<hexagon> hexs;
    std::vector<townClass> towns;
    std::vector<AIBoat> AIBoats;
    std::vector<int> edgeTiles;
    genGrid(hexs, gridSize, camera, resources, textures, towns, AIBoats);

    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    std::cout << "Generation Time: "<< duration/4 << "s\n" << std::endl;


    std::cout << "Charting the Seas!\n" << std::endl;
    start = std::clock();

    std::vector<std::vector<hexagon*> > townPaths = initPathGen(towns, hexs, gridSize, edgeTiles);

    duration = (( std::clock() - start ) / (double) CLOCKS_PER_SEC)/4;
    std::cout << "Charting Time: "<< duration/4 << "s\n" << std::endl;


    for(auto &texture : textures)
    {
        if(texture.name == "boatTexture")
        {
            for(int i = 0; i<5; i++)
            {
                AIBoat newBoat(texture, hexs, townPaths);
                AIBoats.push_back(newBoat);
            }
            break;
        }
    }

    sf::Font mainFont;
    mainFont.loadFromFile("DroidSans.ttf");

    Date date;
    double daySpeed = 1; // days last for x sec(s)

    sf::Texture playerTexture;
    playerTexture.loadFromFile("tobacco.png");
    player player(playerTexture, hexs);

    hudClass HUD(hudView, mainFont);

    hexWindow window(&(hexs.at(0)), camera, mainFont);
    townWindow townWindow(mainFont);
    /// Start game clock
    start = std::clock();
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;


    // Game loop
    while (app.isOpen())
    {
        // Process events
        sf::Event event;
        while (app.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                app.close();

            if (event.type == sf::Event::KeyReleased)
            {
                if(event.key.code == sf::Keyboard::Escape)
                {
                    if(window.display)
                        window.display = false;
                }

                if(event.key.code == sf::Keyboard::Q)
                {
                    camera.rotate(-45);
                }

                if(event.key.code == sf::Keyboard::E)
                {
                    camera.rotate(45);
                }

            }

            if (event.type == sf::Event::MouseButtonPressed) // Gets tile info
            {
                //LMB
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    for (auto &tile : hexs)
                    {
                        if(tile.hex.getGlobalBounds().contains(app.mapPixelToCoords(sf::Mouse::getPosition())))
                        {

                            if(tile.terrain == town) //&& tile.owner == playerOwned)
                            {
                                window.display = false;
                                townWindow.update(&tile, towns);
                                townWindow.display = true;
                                break;
                            }

                            if(townWindow.display)
                                townWindow.display = false;

                            window.hex = &tile;
                            window.infoText.setString(window.genString());
                            window.display = true;
                            break; // stops the loop over all tiles
                        }
                    }
                }

                //RMB
                if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
                {

                        for (auto &tile : hexs)
                        {
                            if(tile.hex.getGlobalBounds().contains(app.mapPixelToCoords(sf::Mouse::getPosition())))
                            {

                                parameters p; // may only pass one object as paramater to async :'(
                                hexagon* town2 = &hexs.at(tile.index);

                                pathParameters pp(player.currentHex, town2, hexs, gridSize);
                                std::future< std::vector<hexagon*> > future = std::async(std::launch::async, findPath, std::ref(pp));
                                p.hexPath = future.get();

                                p.character = &player;
                                p.daySpeed = daySpeed;

                                std::async(std::launch::async, playerMovement, p);
                                break;

                            }
                        }
                }
            }
        }


    HUD.update(player, date);
    update_view(app, camera, hudView, hexs, window, HUD, player, townWindow, AIBoats);

    bool monthTick = false;
    bool yearTick = false;

    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    if(duration >= daySpeed) /// every daytick (a second)
    {
        duration = 0;
        start = std::clock();
        HUD.dateStr = date.update(monthTick, yearTick);


        for(auto &texture : textures)
        {
            if(texture.name == "boatTexture")
            {
                for(int i = 0; i<10; i++)
                {
                    AIBoat newBoat(texture, hexs, townPaths);
                    AIBoats.push_back(newBoat);
                }
                break;
            }
        }

        for(auto &boat : AIBoats)
        {
            if(!boat.moveNext())
            {
                while(true)
                {
                    int randnum = rand() % ((townPaths.size()-1) + 1);
                    if(townPaths.at(randnum).at(0)->index == boat.currentHex->index)
                    {
                        boat.currentPath = townPaths.at(randnum);
                        break;
                    }
                }
            }
        }
    }


    if(monthTick)
    {
        for(auto &town : towns)
        {
            town.population += (town.food-(town.population/100))*5;
            if(town.manPower < town.population/7)
                town.manPower += town.population/12;
                if(town.manPower > town.population/7)
                    town.manPower = town.population/7;

            if(floor(town.population/100) > town.townSize)
            {
                int newSize = floor(town.population/100);
                for(auto &tile : hexs)
                {
                    if(tile.distanceTo(town.tile) <= newSize && tile.owner == noOne && newSize < 11)
                    {
                        tile.owner = town.tile->owner;
                        sf::Color colour = town.tile->ownerHex.getFillColor();
                        tile.ownerHex.setFillColor(colour);
                        town.food += tile.resource.food;
                        town.production += tile.resource.production;

                    }
                }
            }


            printf("Pop: %i\nMen: %i\n\n", town.population, town.manPower);
        }

    }

    if(yearTick)
    {

    }


    }

    return EXIT_SUCCESS;
}
