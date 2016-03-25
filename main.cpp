
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
                    app.close();
                }
            }

            if (event.type == sf::Event::MouseButtonReleased) // Gets tile info
            {
                    for (auto &tile : hexs)
                    {
                        if(tile.hex.getGlobalBounds().contains(app.mapPixelToCoords(sf::Mouse::getPosition())))
                        {
                            printf("Tile: %i\nX: %i\nY: %i\nTerrain: %i\nOwner: %i\nResource: %s\n\n\n", tile.index, tile.x, tile.y, tile.terrain, tile.owner, tile.resource.name.c_str());
                            break;
                        }
                    }
            }

        }


    update_view(app, camera, hexs);


    }

    return EXIT_SUCCESS;
}
