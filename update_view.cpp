#include "custom.h"
#include <iostream>

void update_view(sf::RenderWindow &app, sf::View &camera, sf::View &hudView, std::vector<hexagon> &hexs, hexWindow &window, hudClass &HUD, player &player)
{
                            // Camera Movement
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                    {
                        camera.setCenter(camera.getCenter().x, camera.getCenter().y - 7*300);
                    }

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                    {
                        camera.setCenter(camera.getCenter().x, camera.getCenter().y + 7*300);
                    }

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                    {
                        camera.setCenter(camera.getCenter().x - 7*300, camera.getCenter().y);
                    }

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                    {
                        camera.setCenter(camera.getCenter().x + 7*300, camera.getCenter().y);
                    }

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
                    {
                        camera.rotate(-45);
                    }

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
                    {
                        camera.rotate(45);
                    }

                        // Zooming
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageDown))
                    {
                        camera.setSize(camera.getSize().x*1.01, camera.getSize().y*1.01);
                    }

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageUp) && camera.getSize().x > 1000)
                    {
                        camera.setSize(camera.getSize().x*0.99, camera.getSize().y*0.99);
                    }

                    // Needed to update view
                    app.setView(camera);


        app.clear();
        for (auto const &hex: hexs)
        {
            app.draw(hex.hex);
            if(hex.resource.name != "none")
            {
                app.draw(hex.resource.icon);
            }

            if(hex.owner != noOne)
            {
                app.draw(hex.ownerHex);
            }
        }

    app.draw(player);

    app.setView(hudView);

        if(window.display)
        {
            app.draw(window.rect);
            app.draw(window.infoText);
        }

        app.draw(HUD.top);
        app.draw(HUD.dateText);
        app.draw(HUD.nameText);
        app.draw(HUD.moneyText);


        app.display();

    app.setView(camera);
}
