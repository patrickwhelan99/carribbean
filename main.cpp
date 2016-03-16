
#include "custom.h"

#include <SFML/Graphics.hpp>
#include <iostream>

/* The following are for rand*/
#include <stdlib.h>
#include <random>
#include <time.h>
/*---------------------------*/
#include <fstream>



int main()
{
    // Create the main window and camera
    sf::RenderWindow app(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "Gen that Land"/*, sf::Style::Fullscreen*/);

    sf::View camera;
    camera.setSize(8888, 5000);
    camera.setCenter(2250, 1750);
    app.setView(camera);

    // Generate the grid
    std::vector<hexagon> hexs = genGrid();

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

        }


    update_view(app, camera, hexs);


    }

    return EXIT_SUCCESS;
}
