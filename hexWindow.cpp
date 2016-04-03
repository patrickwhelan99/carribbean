#include "custom.h"
#include <string.h>
#include <iostream>

hexWindow::hexWindow(hexagon* hexagon, sf::View &hud, sf::Font &font)
{
    this->hex = hexagon;
    this->rect.setSize(sf::Vector2f(200, 250));
    this->rect.setPosition(-490, 200);
    this->rect.setFillColor(sf::Color(10, 10, 10, 128));

    this->distance = 0;
    this->infoStr = std::string("X: ") + std::to_string(hexagon->x) + std::string("\nY: ") + std::to_string(hexagon->y) + std::string("\nZ: ") + std::to_string(hexagon->z) + std::string("\nResource: ") + hexagon->resource.name + std::string("\nDistance: ") + std::to_string(this->distance);

    this->infoText = sf::Text(infoStr, font);
    this->infoText.setPosition(-490, 200);
    this->infoText.setCharacterSize(25);
    this->infoText.setStyle(sf::Text::Bold);
    this->infoText.setColor(sf::Color::White);

    this->display = true;
}

hexWindow::~hexWindow()
{

}

std::string hexWindow::genString()
{
    return std::string("X: ") + std::to_string(this->hex->x) + std::string("\nY: ") + std::to_string(this->hex->y) + std::string("\nZ: ") + std::to_string(this->hex->z) + std::string("\nResource: ") + this->hex->resource.name + std::string("\nDistance: ") + std::to_string(this->distance);
}
