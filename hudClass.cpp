#include "custom.h"

hudClass::hudClass(sf::View &hudView, sf::Font &mainFont)
{
    this->top = sf::RectangleShape(sf::Vector2f(hudView.getSize().x, hudView.getSize().y/10));
    this->top.setFillColor(sf::Color(20, 20, 20, 128));
    this->top.setPosition(-500, -500);

    this->dateText = sf::Text(std::string(""), mainFont);
    this->dateText.setCharacterSize(10);
    this->dateText.setStyle(sf::Text::Bold);

    this->nameText = sf::Text(std::string(""), mainFont);
    this->nameText.setCharacterSize(10);
    this->nameText.setStyle(sf::Text::Bold);

    this->moneyText = sf::Text(std::string(""), mainFont);
    this->moneyText.setCharacterSize(10);
    this->moneyText.setStyle(sf::Text::Bold);

    this->dateText.setPosition(-490, -450);
    this->nameText.setPosition(-140, -450);
    this->moneyText.setPosition(290, -450);
}

void hudClass::update(player &player, Date &date)
{

    this->dateText.setString(this->dateStr);

    this->nameStr = player.name;
    this->nameText.setString(this->nameStr);

    this->moneyStr = std::to_string(player.money);
    this->moneyText.setString(this->moneyStr);
}
