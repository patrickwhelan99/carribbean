#include "custom.h"
#include <iostream>

townWindow::townWindow(sf::Font &font)
{
    this->hex = 0;
    this->currentTown = nullptr;
    this->windowBox.setSize(sf::Vector2f(400, 400));
    this->windowBox.setPosition(-490, 100);
    this->windowBox.setFillColor(sf::Color(10, 10, 10, 128));

    this->nameStr = std::string("NAME");
    this->nameText = sf::Text(nameStr, font);
    this->nameText.setPosition(-310, 130);
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
    this->pic1.setFillColor(sf::Color(255, 10, 10));

    this->pic2.setSize(sf::Vector2f(50, 50));
    this->pic2.setPosition(-480, 260);
    this->pic2.setFillColor(sf::Color(255, 10, 10));

    this->pic3.setSize(sf::Vector2f(50, 50));
    this->pic3.setPosition(-480, 320);
    this->pic3.setFillColor(sf::Color(255, 10, 10));

    this->pic4.setSize(sf::Vector2f(50, 50));
    this->pic4.setPosition(-480, 380);
    this->pic4.setFillColor(sf::Color(255, 10, 10));

    this->pic5.setSize(sf::Vector2f(50, 50));
    this->pic5.setPosition(-480, 440);
    this->pic5.setFillColor(sf::Color(255, 10, 10));


    this->display = false;
}

void townWindow::update(hexagon* hexagon, std::vector<townClass> &towns)
{
    this->hex = hexagon;

    for(auto &town : towns)
    {
        if(town.tile->index == hexagon->index)
        {
            this->infoStr = std::to_string(town.population) + std::string("\n\n") + std::to_string(town.manPower) + std::string("\n\n") + std::to_string(town.income) + std::string("\n\n") + std::to_string(town.food) + std::string("\n\n") + std::to_string(town.production);
        }
    }


    this->infoText.setString(this->infoStr);
}
