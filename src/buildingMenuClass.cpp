#include "../include/custom.h"

buildingMenuClass::buildingMenuClass(townWindow &parent, sf::Font &font)
{
    this->parent = &parent;
    this->index = 0;
    this->font = font;

    this->windowBox.setSize(sf::Vector2f(200, 500));
    sf::Vector2f pos = parent.windowBox.getPosition();
    pos.x += parent.windowBox.getLocalBounds().width + 3;
    this->windowBox.setPosition(pos);
    this->windowBox.setFillColor(sf::Color(10, 10, 10, 128));

    this->buildingPic.setPosition(sf::Vector2f(this->windowBox.getPosition().x+this->windowBox.getLocalBounds().width/4, this->windowBox.getPosition().y+this->windowBox.getLocalBounds().height/8));
    this->buildingPic.setSize(sf::Vector2f(100, 200));

    this->buildingNameText = sf::Text(this->buildingName, font);
    this->buildingNameText.setPosition(this->buildingPic.getPosition().x, this->buildingPic.getPosition().y + (this->windowBox.getGlobalBounds().top - this->buildingPic.getGlobalBounds().top) / 2);
    this->buildingNameText.setCharacterSize(30);
    this->buildingNameText.setStyle(sf::Text::Bold);
    this->buildingNameText.setColor(sf::Color::White);

    this->buildingDescText = sf::Text(this->buildingName, font);
    this->buildingDescText.setPosition(this->windowBox.getPosition().x, this->windowBox.getPosition().y + this->windowBox.getLocalBounds().height/2 + this->windowBox.getLocalBounds().height/16);
    this->buildingDescText.setCharacterSize(15);
    this->buildingDescText.setStyle(sf::Text::Italic);
    this->buildingDescText.setColor(sf::Color::White);

    this->foodPic.setPosition(this->buildingDescText.getPosition().x, this->buildingDescText.getPosition().y + 20);
    this->foodPic.setSize(sf::Vector2f(20, 20));
    this->foodPic.setTexture(this->parent->foodTexture);

    this->productionPic.setPosition(this->buildingDescText.getPosition().x, this->foodPic.getPosition().y + 25);
    this->productionPic.setSize(sf::Vector2f(20, 20));
    this->productionPic.setTexture(this->parent->productionTexture);

    this->manpowerPic.setPosition(this->buildingDescText.getPosition().x, this->productionPic.getPosition().y + 25);
    this->manpowerPic.setSize(sf::Vector2f(20, 20));
    this->manpowerPic.setTexture(this->parent->manpowerTexture);

    this->foodOutputText = sf::Text(foodOutput, font);
    this->foodOutputText.setPosition(this->foodPic.getPosition().x + 30, this->foodPic.getPosition().y + this->foodPic.getLocalBounds().height/2);
    this->foodOutputText.setCharacterSize(10);
    this->foodOutputText.setColor(sf::Color::White);

    this->productionOutputText = sf::Text(foodOutput, font);
    this->productionOutputText.setPosition(this->productionPic.getPosition().x + 30, this->productionPic.getPosition().y + this->productionPic.getLocalBounds().height/2);
    this->productionOutputText.setCharacterSize(10);
    this->productionOutputText.setColor(sf::Color::White);

    this->manpowerOutputText = sf::Text(foodOutput, font);
    this->manpowerOutputText.setPosition(this->manpowerPic.getPosition().x + 30, this->manpowerPic.getPosition().y + this->manpowerPic.getLocalBounds().height/2);
    this->manpowerOutputText.setCharacterSize(10);
    this->manpowerOutputText.setColor(sf::Color::White);

    this->requiredMaterialsText = sf::Text(this->requiredMaterials, font);
    this->requiredMaterialsText.setPosition(this->foodPic.getPosition().x + (this->windowBox.getLocalBounds().width/3)*2, this->foodPic.getPosition().y);
    this->requiredMaterialsText.setCharacterSize(15);
    this->requiredMaterialsText.setStyle(sf::Text::Italic);
    this->requiredMaterialsText.setColor(sf::Color::White);

    this->previous.setSize(sf::Vector2f(20, 20));
    this->previous.setPosition(this->manpowerPic.getPosition().x, this->manpowerPic.getPosition().y + 25);
    this->previous.setFillColor(sf::Color::Red);

    this->next.setSize(sf::Vector2f(20, 20));
    this->next.setPosition(this->windowBox.getPosition().x + this->windowBox.getLocalBounds().width - 25, this->manpowerPic.getPosition().y + 25);
    this->next.setFillColor(sf::Color::Red);

    this->buildButton.setSize(sf::Vector2f(20, 20));
    this->buildButton.setPosition(this->windowBox.getPosition().x + this->windowBox.getLocalBounds().width/2 - 25, this->manpowerPic.getPosition().y + 25);
    this->buildButton.setFillColor(sf::Color::Red);
}

void buildingMenuClass::update(std::vector<buildingClass> &buildings, std::vector<textureClass> &textures)
{

    buildingClass building = buildings.at(this->index);

    for(auto &t : textures)
    {
        if(t.name == building.textureStr)
            this->buildingPic.setTexture(&t);
    }

    this->buildingName = building.name;
    this->buildingDesc = building.desc;
    this->foodOutput = std::to_string(building.foodOutput);
    this->productionOutput = std::to_string(building.productionOutput);
    this->manpowerOutput = std::to_string(building.manpowerOutput);

    this->buildingNameText.setString(this->buildingName);
    this->buildingDescText.setString(this->buildingDesc);
    this->foodOutputText.setString(this->foodOutput);
    this->productionOutputText.setString(this->productionOutput);
    this->manpowerOutputText.setString(this->manpowerOutput);

    this->requiredMaterials = std::string("");

    for(auto &r : building.requiredMaterials)
    {
        this->requiredMaterials += r.name + std::string("\n");
    }
    this->requiredMaterialsText.setString(this->requiredMaterials);


}

void buildingMenuClass::buildBuilding(std::vector<buildingClass> &buildings, std::vector<resourceClass> &resources, std::vector<townClass> &towns, std::vector<goodClass> goods)
{
    buildingClass building = buildings.at(this->index);
    bool canBuild = true;

///Check if building already built in town
    for(auto &b : this->parent->currentTown->buildings)
    {
        if(building.name == b.name)
            canBuild = false;
    }

///Check if town has resources neccesary
    for(auto &r : resources)
    {
        int (townClass::*fPtr) (resourceClass resource);
        fPtr = &townClass::resourceCount;
        int a = (this->parent->currentTown->*fPtr)(r);
        int b = 0;
        for(auto &res : building.requiredMaterials)
        {
            if(res.name == r.name)
                b += 1;
        }

        if(a < b)
            canBuild = false;
    }

///Check if town is producting enough goods for building


            for(auto &good : this->parent->currentTown->goods)
            {
                if(building.outputGood.name == good.name)
                {
                    if(building.outputGoodVolume < good.num)
                        canBuild = false;
                    break;
                }

            }

///If so remove resources and add building to towns vector
    if(canBuild)
    {
        for(auto &resource : resources)
        {
            int b = 0;
            for(auto &res : building.requiredMaterials)
            {
                if(res.name == resource.name)
                    b += 1;
            }

            int n = 0;

        while(n<b)
            {
                for(auto &t : this->parent->currentTown->ownedTiles)
                {
                    if(t->resource.name == resource.name)
                    {
                        t->resource = resources.at(0);
                        t->resourceIcon.setFillColor(sf::Color(0, 0, 0, 255));
                        n++;
                    }

                    if(n>=b)
                        break;
                }

            }
        }
        ///Update towns stats and townwindow
        this->parent->currentTown->buildings.push_back(building);
        this->parent->currentTown->food += building.foodOutput;
        this->parent->currentTown->production += building.productionOutput;
        this->parent->currentTown->manPower += building.manpowerOutput;
        this->parent->update(this->parent->hex, towns);
    }

    else
        printf("Cannot Build!\n");

}


















