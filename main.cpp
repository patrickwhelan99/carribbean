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
    std::vector<resourceClass> resources = loadResources();


    // Generate the grid
        // Setup timer
        std::clock_t start;
        double duration;
        start = std::clock();

    printf("Creating Grid!...\n");
    std::vector<hexagon> hexs = genGrid(gridSize, camera, resources, textures);

        duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    std::cout << "Generation Time: "<< duration << "s" << std::endl;


    sf::Font mainFont;
    mainFont.loadFromFile("DroidSans.ttf");

    Date date;
    double daySpeed = 1; // days last for x sec(s)

    sf::Texture playerTexture;
    playerTexture.loadFromFile("tobacco.png");
    player player(playerTexture, hexs);

    hudClass HUD(hudView, mainFont);

    hexWindow window(&(hexs.at(0)), camera, mainFont);

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
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    for (auto &tile : hexs)
                    {
                        if(tile.hex.getGlobalBounds().contains(app.mapPixelToCoords(sf::Mouse::getPosition())))
                        {
                            window.hex = &tile;
                            window.infoText.setString(window.genString());
                            window.display = true;
                            break; // stops the loop over all tiles
                        }
                    }
                }


                if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
                {

                        for (auto &tile : hexs)
                        {
                            if(tile.hex.getGlobalBounds().contains(app.mapPixelToCoords(sf::Mouse::getPosition())))
                            {

                                parameters p; // may only pass one object as param
                                p.hexPath = player.findPath(&tile, hexs, gridSize);
                                p.character = &player;
                                std::thread t1(playerMovement, p);
                                t1.detach();
                                break;
                            }
                        }
                }
            }
        }


    HUD.update(player, date);
    update_view(app, camera, hudView, hexs, window, HUD, player);

    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    if(duration >= daySpeed) // every second
    {
        //update_view(app, camera, hudView, hexs, window, HUD, player);
        duration = 0;
        start = std::clock();
        HUD.dateStr = date.update();
    }



    }

    return EXIT_SUCCESS;
}
