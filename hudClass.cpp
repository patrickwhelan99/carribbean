#include "custom.h"

hudClass::hudClass(sf::View &hudView, sf::Font &mainFont, std::vector<textureClass> &textures)
{
    this->tradeDealWindow = nullptr;

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
    this->dateText.setPosition(-500, -450);
    this->nameText.setPosition(0, -450);
    this->moneyText.setPosition(450, -450);

    this->tradeDealsButton.setRadius(25);
    for(auto &t : textures)
        if(t.name == "tradeDealButtonTexture")
            this->tradeDealsButton.setTexture(&t);
    this->tradeDealsButton.setPosition(0,-450);

    this->showTradeDeals = false;
}

void hudClass::update(playerClass &player, Date &date)
{

    this->dateText.setString(this->dateStr);

    this->nameStr = player.name;
    this->nameText.setString(this->nameStr);

    this->moneyStr = std::to_string(player.money);
    this->moneyText.setString(this->moneyStr);
}
