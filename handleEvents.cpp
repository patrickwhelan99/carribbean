#include "custom.h"
#include <future>


void handleEvents(sf::RenderWindow &app, std::vector<hexagon> &hexs, hudClass &HUD, townWindow &townWindow, hexWindow &window, playerClass &player, int gridSize, sf::View &camera, sf::View &hudView, std::vector<townClass> &towns, int daySpeed, std::vector<buildingClass> &buildings, std::vector<textureClass> &textures, buildingMenuClass &buildingMenu, std::vector<resourceClass> &resources, std::vector<goodClass> &goods, sf::Font &font, bool &paused, std::vector<AIBoat> &AIBoats, std::vector<unit> &units, std::vector<std::shared_ptr<nationClass> > &nations)
{
    sf::Event event;
        while (app.pollEvent(event))
        {
            // Close window : exit
            if(event.type == sf::Event::Closed)
                app.close();

            if(event.type == sf::Event::KeyReleased)
            {
                if(event.key.code == sf::Keyboard::Escape)
                {
                    paused = !paused;
                }

                if(event.key.code == sf::Keyboard::Q)
                {
                    camera.rotate(-45);
                }

                if(event.key.code == sf::Keyboard::E)
                {
                    camera.rotate(45);
                }

                if(event.key.code == sf::Keyboard::F1)
                {
                    sf::Image Screen = app.capture();
                    Screen.saveToFile("screenshot.jpg");
                }

                if(event.key.code == sf::Keyboard::Return)
                {
                    std::vector<AIBoat> sameTileBoats;

                    for(auto &b : AIBoats)
                        if(b.currentHex->index == player.currentHex->index)
                            sameTileBoats.push_back(b);

                    if(sameTileBoats.size() > 0)
                        initiateCombat(app, camera, player, sameTileBoats);
                }

                if(event.key.code == sf::Keyboard::Tab)
                {
                    for(std::shared_ptr<nationClass> &nation : nations)
                    {
                        //if(!nation.atWarWithName.size() != 0)
                        //{
                            for(townClass &town : towns)
                            {
                                printf("nation:\t%s\tnationAtWarWith:\t%s\ttown's nation:\t%s\n", nation->name.c_str(), nation->atWarWithName.c_str(), town.nation->name.c_str());
                                if(town.nation->name == nation->atWarWithName)
                                {
                                    for(hexagon* &hex : town.tile->adjacentTiles(hexs, gridSize))
                                    {
                                        auto a = nation.get();
                                        militaryLandUnit newUnit(a, 1, hex, textures.at(5));
                                        units.push_back(newUnit);
                                    }
                                }
                            }
                        //}
                    }
                }

            }

            if(paused)
                break;

            if (event.type == sf::Event::MouseButtonPressed)
            {
                //LMB
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    app.setView(hudView); /// Change apps view so mouse position can be mapped to hud coordinates and not the map's

                    if(HUD.tradeDealsButton.getGlobalBounds().contains(app.mapPixelToCoords(sf::Mouse::getPosition())))
                    {
                        HUD.showTradeDeals = !HUD.showTradeDeals;
                        if(HUD.showTradeDeals)
                        {
                            HUD.showTradeDeals = true;
                            HUD.tradeDealWindow->updateDeals(towns, textures, font);
                        }
                    }

                    if(HUD.showTradeDeals && HUD.tradeDealWindow->prevButton.getGlobalBounds().contains(app.mapPixelToCoords(sf::Mouse::getPosition())))
                    {
                        if(HUD.tradeDealWindow->index == 0)
                            HUD.tradeDealWindow->index = HUD.tradeDealWindow->windowTabs;
                        else
                            HUD.tradeDealWindow->index -=1;
                    }

                    if(HUD.showTradeDeals && HUD.tradeDealWindow->nextButton.getGlobalBounds().contains(app.mapPixelToCoords(sf::Mouse::getPosition())))
                    {
                        if(HUD.tradeDealWindow->index == HUD.tradeDealWindow->windowTabs)
                            HUD.tradeDealWindow->index = 0;
                        else
                            HUD.tradeDealWindow->index +=1;
                    }

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
                        if(buildingMenu.index == static_cast<int>(buildings.size()-1))
                            buildingMenu.index = 0;
                        else
                            buildingMenu.index +=1;

                        buildingMenu.update(buildings, textures);
                        break;
                    }

                    if(townWindow.displayBuildingMenu && buildingMenu.buildButton.getGlobalBounds().contains(app.mapPixelToCoords(sf::Mouse::getPosition())) && townWindow.currentTown->nation->name = "player")
                    {
                        buildingMenu.buildBuilding(buildings, resources, towns, goods);
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
                                townWindow.displayBuildingMenu = false;
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
                                player.setPath(tile, hexs, gridSize);
                            }
                        }
                }
            }
        }
}
