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
    std::vector<townClass> towns;
    std::vector<AIBoat> AIBoats;
    std::vector<hexagon> hexs = genGrid(gridSize, camera, resources, textures, towns, AIBoats);

        duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    std::cout << "Generation Time: "<< duration << "s\n" << std::endl;


    std::cout << "Charting the Seas!" << std::endl;
    printf("Generating %i Paths!\n", static_cast<int>((static_cast<int>(towns.size())^2) - static_cast<int>(towns.size())));
    double percentageCharted = 0;
    std::vector< std::vector<hexagon*> > townPaths;
    std::vector<std::future< std::vector<hexagon*> > > path;
    pathParameters ppArray[static_cast<int>(towns.size()*towns.size()-towns.size())];
    //printf("Path size: %i\n", static_cast<int>(towns.size()*towns.size()-towns.size()));
    start = std::clock();
    int n = 0;
    for(auto &town1 : towns)
    {
        for(auto &town2 : towns)
        {
            if(town1.tile && town2.tile && town1.tile->index!=town2.tile->index)
            {
                    printf("Calculating %i -> %i\n", town1.tile->index, town2.tile->index);
                    hexagon* a = town1.tile;
                    hexagon* b = town2.tile;
                    pathParameters p(a, b, hexs, gridSize);
                    ppArray[n] = std::move(p);
                    path.push_back(std::async(std::launch::async, findPath, std::ref(ppArray[n])));
                    n++;
            }
        }

    }

    for(auto &i : path)
    {
        townPaths.push_back(i.get());
        percentageCharted += 100/(towns.size()*towns.size()-towns.size());
        std::cout << static_cast<int>(percentageCharted) << "%\n";
    }

    duration = (( std::clock() - start ) / (double) CLOCKS_PER_SEC)/4;
    std::cout << "Charting Time: "<< duration << "s\n" << std::endl;


    for(auto &texture : textures)
    {
        if(texture.name == "boatTexture")
        {
            for(int i = 0; i<5; i++)
            {
                AIBoat newBoat(texture, hexs, townPaths);
                AIBoats.push_back(newBoat);
            }
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


        for(auto &boat : AIBoats)
        {
            if(!boat.moveNext(hexs, gridSize))
            {
                while(true)
                {
                    int randnum = rand() % ((townPaths.size()-1) + 1);
                    if(townPaths.at(randnum).at(0) == boat.currentHex)
                    {
                        boat.currentPath = townPaths.at(randnum);
                        printf("Fixed?\n");
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
