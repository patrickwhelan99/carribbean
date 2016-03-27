
#include "custom.h"

#include <SFML/Graphics.hpp>
#include <iostream>

/* The following are for rand*/
#include <stdlib.h>
#include <random>
#include <time.h>
/*---------------------------*/
#include <fstream>
#include <ctime>
#include <algorithm>
#include <math.h>



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

    sf::View hud;
    hud.setSize(1000, 1000);
    hud.setCenter(0, 0);

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

    hexagon* oldHex = nullptr;
    hexWindow* window = nullptr;

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
                    delete window;
                    app.close();
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
                            if(window != nullptr)
                            {
                                std::cout << "Distance from last tile:  " << window->hex->distanceTo(&tile) << std::endl;
                                delete window;
                            }

                            window = new hexWindow(&tile, hud, mainFont);
                            std::cout << window->infoStr << std::endl;
                            break; // stops the loop over all tiles
                        }
                    }
                }


                if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
                {
                    if(window != nullptr)
                    {
                        for (auto &tile : hexs)
                        {
                            if(tile.hex.getGlobalBounds().contains(app.mapPixelToCoords(sf::Mouse::getPosition())))
                            {
                                window->distance = window->hex->distanceTo(&tile);
                                window->infoText.setString(window->genString());
                            }
                        }
                    }
                }

            }

        }

    update_view(app, camera, hud, hexs, window);


    }

    return EXIT_SUCCESS;
}
