#include "custom.h"
#include <future>

void handleEvents(sf::RenderWindow &app, std::vector<hexagon> &hexs, townWindow &townWindow, hexWindow &window, player &player, int gridSize, sf::View &camera, std::vector<townClass> &towns, int daySpeed)
{
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
}
