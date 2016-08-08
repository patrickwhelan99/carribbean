#include "custom.h"
#include <future>

void handleEvents(sf::RenderWindow &app, std::vector<hexagon> &hexs, townWindow &townWindow, hexWindow &window, playerClass &player, int gridSize, sf::View &camera, sf::View &hudView, std::vector<townClass> &towns, int daySpeed, std::vector<buildingClass> &buildings, std::vector<textureClass> &textures, buildingMenuClass &buildingMenu, std::vector<resourceClass> &resources)
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
                    app.setView(hudView); /// Change apps view so mouse position can be mapped to hud coordinates and not the map's

                    if(townWindow.display && townWindow.buildingMenuButton.getGlobalBounds().contains(app.mapPixelToCoords(sf::Mouse::getPosition())))
                    {
                        if(!townWindow.displayBuildingMenu)
                            townWindow.spawnBuildingMenu(buildings, textures, buildingMenu);
                        else
                            townWindow.destroyBuildingMenu();

                        break;
                    }

                    if(townWindow.display && townWindow.unitMenuButton.getGlobalBounds().contains(app.mapPixelToCoords(sf::Mouse::getPosition())))
                    {
                        if(!townWindow.displayUnitMenu)
                            townWindow.spawnUnitMenu();
                        else
                            townWindow.destroyUnitMenu();

                        break;
                    }

                    if(townWindow.displayBuildingMenu && buildingMenu.previous.getGlobalBounds().contains(app.mapPixelToCoords(sf::Mouse::getPosition())))
                    {
                        if(buildingMenu.index == 0)
                            buildingMenu.index = buildings.size()-1;
                        else
                            buildingMenu.index -=1;

                        buildingMenu.update(buildings, textures);
                        break;
                    }

                    if(townWindow.displayBuildingMenu && buildingMenu.next.getGlobalBounds().contains(app.mapPixelToCoords(sf::Mouse::getPosition())))
                    {
                        if(buildingMenu.index == buildings.size()-1)
                            buildingMenu.index = 0;
                        else
                            buildingMenu.index +=1;

                        buildingMenu.update(buildings, textures);
                        break;
                    }

                    if(townWindow.displayBuildingMenu && buildingMenu.buildButton.getGlobalBounds().contains(app.mapPixelToCoords(sf::Mouse::getPosition())))
                    {
                        buildingMenu.buildBuilding(buildings, resources, towns);
                    }

                    if(townWindow.displayBuildingMenu && buildingMenu.windowBox.getGlobalBounds().contains(app.mapPixelToCoords(sf::Mouse::getPosition())))
                        break;

                    app.setView(camera);

                    for (auto &tile : hexs)
                    {
                        if(tile.hex.getGlobalBounds().contains(app.mapPixelToCoords(sf::Mouse::getPosition())))
                        {

                            if(tile.terrain == town)
                            {
                                window.display = false;
                                townWindow.update(&tile, towns);
                                townWindow.display = true;
                                break;
                            }

                            if(townWindow.display)
                                townWindow.display = false;
                            if(townWindow.displayBuildingMenu)
                                townWindow.displayBuildingMenu = false;

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
                                player.currentPath = std::vector<hexagon*>(); // clear current path
                                pathParameters p(player.currentHex, &tile, hexs, gridSize);
                                player.currentPath = findPath(p);
                            }
                        }
                }
            }
        }
}
