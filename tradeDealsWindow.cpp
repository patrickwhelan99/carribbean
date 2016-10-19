#include "custom.h"

tradeDealsWindowClass::tradeDealsWindowClass(sf::Vector2f &spawnButtonPos)
{
    this->window.setPosition(spawnButtonPos.x - 250, spawnButtonPos.y + 100);
    this->window.setSize(sf::Vector2f(300, 100));
    this->window.setFillColor(sf::Color(10, 10, 10, 128));
    this->prevButton.setPosition(spawnButtonPos.x - 250, spawnButtonPos.y + 50);
    this->prevButton.setSize(sf::Vector2f(20, 20));
    this->prevButton.setFillColor(sf::Color::Red);
    this->nextButton.setPosition(spawnButtonPos.x + 230, spawnButtonPos.y + 50);
    this->nextButton.setSize(sf::Vector2f(20, 20));
    this->nextButton.setFillColor(sf::Color::Red);
    this->windowTabs = 0;
    this->index = 0;
}

void tradeDealsWindowClass::updateDeals(std::vector<townClass> &towns, std::vector<textureClass> &textures, sf::Font &font)
{
    int totalOpenDeals = 0;
    for(auto &town : towns)
    {
        totalOpenDeals += static_cast<int>(town.openDeals.size());
    }

    this->window.setSize(sf::Vector2f(500, 50*16));

    int counter = 0;
    for(auto &town : towns)
    {
        for(auto &deal : town.openDeals)
        {
            tradeDealDisplayableClass newDeal;
            std::string dealStr = deal.name + std::string("\t") + town.name;
            newDeal.dealText = sf::Text(dealStr, font);
            newDeal.dealText.setCharacterSize(20);
            newDeal.dealText.setPosition(this->window.getPosition() + sf::Vector2f(10, 50*counter));
            newDeal.goodPic.setPosition(this->window.getPosition() + sf::Vector2f(250, 50*counter));
            newDeal.goodPic.setSize(sf::Vector2f(20, 20));

            for(auto &t : textures)
                if(t.name == deal.tradeGood.name)
                    newDeal.goodPic.setTexture(&t);

            this->deals.push_back(newDeal);

            if(counter > 14)
            {
                counter = 0;
                windowTabs += 1;
            }
            counter++;
        }
    }
}
