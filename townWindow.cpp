#include "custom.h"
#include <iostream>

townWindow::townWindow(sf::Font &font, std::vector<textureClass> &textures)
{

    for(auto &t : textures)
    {
        if(t.name == "populationTexture")
            this->populationTexture = &t;
        if(t.name == "manpowerTexture")
            this->manpowerTexture = &t;
        if(t.name == "incomeTexture")
            this->incomeTexture = &t;
        if(t.name == "foodTexture")
            this->foodTexture = &t;
        if(t.name == "productionTexture")
            this->productionTexture = &t;
        if(t.name == "productionTexture")
            this->productionTexture = &t;
        if(t.name == "buildingMenuButtonTexture")
            this->buildingMenuButtonTexture = &t;
        if(t.name == "unitMenuButtonTexture")
            this->unitMenuButtonTexture = &t;
    }


    this->hex = 0;
    this->currentTown = nullptr;
    this->windowBox.setSize(sf::Vector2f(300, 500));
    this->windowBox.setPosition(-490, 100);
    this->windowBox.setFillColor(sf::Color(10, 10, 10, 128));

    this->nameStr = std::string("Not Set");
    this->nameText = sf::Text(nameStr, font);
    this->nameText.setPosition(-450, 130);
    this->nameText.setCharacterSize(30);
    this->nameText.setStyle(sf::Text::Bold);
    this->nameText.setColor(sf::Color::White);



    this->infoStr = std::string("1\n\n2\n\n3\n\n4\n\n5");
    this->infoText = sf::Text(infoStr, font);
    this->infoText.setPosition(-420, 200);
    this->infoText.setCharacterSize(27);
    this->infoText.setStyle(sf::Text::Bold);
    this->infoText.setColor(sf::Color::White);

    this->pic1.setSize(sf::Vector2f(50, 50));
    this->pic1.setPosition(-480, 200);
    this->pic1.setTexture(populationTexture);

    this->pic2.setSize(sf::Vector2f(50, 50));
    this->pic2.setPosition(-480, 260);
    this->pic2.setTexture(manpowerTexture);

    this->pic3.setSize(sf::Vector2f(50, 50));
    this->pic3.setPosition(-480, 320);
    this->pic3.setTexture(incomeTexture);

    this->pic4.setSize(sf::Vector2f(50, 50));
    this->pic4.setPosition(-480, 380);
    this->pic4.setTexture(foodTexture);

    this->pic5.setSize(sf::Vector2f(50, 50));
    this->pic5.setPosition(-480, 440);
    this->pic5.setTexture(productionTexture);

    this->buildingMenuButton.setRadius(25);
    this->buildingMenuButton.setPosition(-300, 300);
    this->buildingMenuButton.setTexture(buildingMenuButtonTexture);
    this->displayBuildingMenu = false;

    this->unitMenuButton.setRadius(25);
    this->unitMenuButton.setPosition(-300, 340);
    this->unitMenuButton.setTexture(unitMenuButtonTexture);
    this->displayUnitMenu = false;

    this->display = false;
}

void townWindow::update(hexagon* hexagon, std::vector<townClass> &towns)
{
    this->hex = hexagon;

    for(auto &town : towns)
    {
        if(town.tile->index == hexagon->index)
        {
            this->currentTown = &town;
            this->nameStr = std::string(town.name);
            this->infoStr = std::to_string(town.population) + std::string("\n\n") + std::to_string(town.manPower) + std::string("\n\n") + std::to_string(town.income) + std::string("\n\n") + std::to_string(town.food) + std::string("\n\n") + std::to_string(town.production);
        }
    }

    this->nameText.setString(this->nameStr);
    this->infoText.setString(this->infoStr);
}

void townWindow::spawnBuildingMenu(std::vector<buildingClass> &buildings, std::vector<textureClass> &textures, buildingMenuClass &buildingMenu)
{
    buildingMenu.update(buildings, textures);
    this->displayBuildingMenu = true;
}
void townWindow::destroyBuildingMenu()
{
    this->displayBuildingMenu = false;
}





void townWindow::spawnUnitMenu()
{printf("Haalloo Welt!\n");}
void townWindow::destroyUnitMenu()
{printf("Haalloo Welt!\n");}
