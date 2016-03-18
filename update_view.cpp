#include "custom.h"
void update_view(sf::RenderWindow &app, sf::View &camera, std::vector<hexagon> hexs)
{
                            // Camera Movement
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                        camera.setCenter(camera.getCenter().x, camera.getCenter().y - 7);

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                        camera.setCenter(camera.getCenter().x, camera.getCenter().y + 7);

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                        camera.setCenter(camera.getCenter().x - 7, camera.getCenter().y);

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                        camera.setCenter(camera.getCenter().x + 7, camera.getCenter().y);

                        // Zooming
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageDown) && camera.getSize().x < 20000)
                        camera.setSize(camera.getSize().x*1.01, camera.getSize().y*1.01);

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageUp) && camera.getSize().x > 100)
                        camera.setSize(camera.getSize().x*0.99, camera.getSize().y*0.99);

                    // Needed to update view
                    app.setView(camera);


        app.clear();
        for (auto const &hex: hexs)
            app.draw(hex.hex);

        app.display();
}
