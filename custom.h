#ifndef CUSTOM_H_INCLUDED
#define CUSTOM_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <iostream>

/* The following are for rand*/
#include <stdlib.h>
#include <random>
#include <time.h>
/*---------------------------*/
#include <fstream>
#include <ctime> // for clock
#include <algorithm> // for clock
/* The following are for multi-threading*/
#include <thread>
#include <cmath>
#include <future>
#include <math.h>
/*---------------------------*/

enum Terrain {none, sea, land, mountain, sand, jungle, town, lake};
enum Day {monday, tuesday, wednesday, thursday, friday, saturday, sunday};
enum Month {january, february, march, april, may, june, july, august, september, october, november, december};
enum timeFrequency {daily, weekly, biweekly, monthly, quarterly, annualy};

class terrainClass
{
    public:
        Terrain terrain;
        std::string name;
        int movementPoints;

        terrainClass(Terrain terrain, std::string name, int movementPoints);
};

class textureClass : public sf::Texture
{
    public:
        std::string name;
        textureClass();
};

class resourceClass
{
    public:
            std::string name;
            sf::CircleShape icon;
            int spawnChance;
            std::vector<Terrain> requiredTerrain;
            std::string textureName;
            int food;
            int production;
            int num;

            resourceClass(std::string name = "none", std::string texture = "", int spawnChance = 0, std::vector<Terrain> requiredTerrain = std::vector<Terrain>(), int food = 0, int production = 0);
};

class goodClass
{
    public:
        sf::CircleShape icon;
        int stdNum;
        std::string name;
        double price;
        double originalPrice;
        std::string unit; //kg or litre etc
        std::string textureName;
        int num;
        std::vector<resourceClass> materials;

        goodClass(std::string name="none", std::string unit="unit", int stdNum=0, double price=0, std::string textureName="none", std::vector<resourceClass> materials = std::vector<resourceClass>());

        bool operator==(const goodClass &rhs)
           const{
                    return rhs.name == name;
                }
};

class buildingClass
{
    public:
        std::string name;
        std::string desc;
        std::string textureStr;
        int foodOutput;
        int productionOutput;
        int manpowerOutput;
        goodClass outputGood;
        int outputGoodVolume;
        std::vector<resourceClass> requiredMaterials;

        buildingClass(std::string name="none", std::string desc="none", std::string textureStr="none", int foodOutput=0, int productionOutput=0, int manpowerOutput=0, std::vector<resourceClass> requiredMaterials = std::vector<resourceClass>());
};

class tradeDealClass
{
    public:
        std::string name;
        goodClass tradeGood;
        float tradeGoodVolume;
        double payment;
        timeFrequency tradeFrequency;

        tradeDealClass(std::string name, goodClass tradeGood, int tradeGoodVolume, int payment, timeFrequency tradeFrequency);
};

class hexagon;
class townWindow;
class buildingMenuClass;

class townClass
{
    friend townWindow;
    friend buildingMenuClass;

    public:
        hexagon* tile;
        std::vector<hexagon*> ownedTiles;
        std::vector<goodClass> goods;
        std::vector<buildingClass> buildings;

        townClass(hexagon* tile, std::vector<hexagon*> &adjTiles, std::vector<hexagon> &hexs, int gridSize, std::vector<goodClass> &goods);
        int resourceCount(resourceClass resource);
        void setTownName(std::vector<townClass> &towns);
        void monthTick(std::vector<hexagon> &hexs);
        void generateTradeDeals(std::vector<goodClass> &goods, std::vector<std::vector<hexagon*> > &townPaths);

    private:
        std::string name;
        int income;
        int expenditure;
        int townSize;
        int garrison;
        int population;
        int food;
        int production;
        int manPower;
        std::vector<tradeDealClass> openDeals;
        std::vector<tradeDealClass> activeDeals;
};

class adjTileCounter
{
    public:
        int adjSea;
        int adjLand;
        int adjSand;
        int adjJungle;
        int adjLake;
        int adjTown;
        int adjMountain;

        adjTileCounter(int adjSea, int adjLand, int adjSand, int adjJungle, int adjLake, int adjTown, int adjMountain);
};

class hexagon : public sf::CircleShape
{
    public:
    //Coordinates
        int x;
        int y;
        int z;
    //UID
        int index;
    //PathFinding
        int movementPoints;
        int g;
        int h;
        int f;
        hexagon* parent;
    //Data
        Terrain terrain;
        resourceClass resource;
        std::string owner;
        townClass* townOnTile;
    //Graphics
        sf::CircleShape hex;
        sf::CircleShape resourceIcon;
        sf::CircleShape ownerHex;

        hexagon();
        std::vector<hexagon*> adjacentTiles(std::vector<hexagon> &hexs, int vectorSize);
        std::vector<hexagon*> adjacentTilesByCoords(std::vector<hexagon> &hexs, int &gridSize);
        adjTileCounter countAdjacentTiles(std::vector<hexagon> &hexs, int gridSize);
        int distanceTo(hexagon* to);
};

class nationClass
{
    public:
        sf::Color colour;
        std::string name;
        std::string possessive;

        nationClass(std::string name="none", std::string possesive="none", sf::Color colour=sf::Color::White);
};


class hexWindow
{
    public:
        sf::RectangleShape rect;
        std::string infoStr;
        sf::Text infoText;
        hexagon* hex;
        bool display;


        hexWindow(hexagon* hexagon, sf::View &hud, sf::Font &font);
        ~hexWindow();
        std::string genString();
};

class hudClass;

class Date
{
    friend hudClass;
    public:
        std::string update(bool &monthTick, bool &yearTick);
        Date();
    private:
        Day day;
        std::string dayStr;
        Month month;
        std::string monthStr;
        int monthDay;
        int year;
};

class shipClass : public sf::Sprite
{
    friend hudClass;
    public:
        std::string name;
        hexagon* currentHex;
        std::vector<hexagon*> currentPath;
        int x;
        int y;
        int z;
        int speed;
        int movementPoints;
        std::vector<goodClass> inventory;

        shipClass(std::vector<hexagon> &hexs, std::vector<townClass> &towns, std::vector<goodClass> &goods);
        void moveNext(void);
};

class playerClass : public shipClass
{
    friend hudClass;
    public:
        int money;
        playerClass(sf::Texture &texture, std::vector<hexagon> &hexs, std::string &name, std::vector<townClass> &towns, std::vector<goodClass> &goods) : shipClass(hexs, towns, goods)
        {   this->setScale(15, 15);
            this->setTexture(texture);
            this->name = name;
            this->money = 1000;
            this->speed = 3;
        };
        void setPath(hexagon &tile, std::vector<hexagon> &hexs, int &gridSize);
};

class AIBoat : public shipClass
{
    public:

        AIBoat(sf::Texture &texture, std::vector<hexagon> &hexs, std::vector< std::vector<hexagon*> > &townPaths, std::vector<townClass> &towns, std::vector<goodClass> &goods) : shipClass(hexs, towns, goods)
        {   this->setScale(10, 10);
            this->setTexture(texture);
            this->name = "Boaty McBoatFace";
            this->speed = rand() % 5 + 2;
            if(this->speed <= 0)
                printf("%i\n", this->speed);

            for(auto &t : townPaths)
                if(t.at(0)->index == this->currentHex->index)
                    this->currentPath = t;
        };
};

class hudClass
{
    public:
        sf::RectangleShape top;
        std::string dateStr;
        sf::Text dateText;
        std::string moneyStr;
        sf::Text moneyText;
        std::string nameStr;
        sf::Text nameText;

        hudClass(sf::View &hudView, sf::Font &mainFont);
        void update(playerClass &player, Date &date);
};

class pathParameters
{
    public:
        hexagon* tile1;
        hexagon* tile2;
        std::vector<hexagon> hexs;
        int gridSize;

        pathParameters(hexagon* town1, hexagon* town2, std::vector<hexagon> hexs, int gridSize);
        pathParameters(void);
};

class townWindow;

class buildingMenuClass
{
    public:

        int index;
        townWindow* parent;


        ///MAIN WINDOW
        sf::RectangleShape windowBox;

        /// IMAGES
        sf::RectangleShape buildingPic;
        sf::RectangleShape foodPic;
        sf::RectangleShape productionPic;
        sf::RectangleShape manpowerPic;

        /// BUTTONS
        sf::RectangleShape buildButton;
        sf::RectangleShape next;
        sf::RectangleShape previous;

        ///Texts
        sf::Text buildingNameText;
        sf::Text buildingDescText;
        sf::Text requiredMaterialsText;
        sf::Text foodOutputText;
        sf::Text productionOutputText;
        sf::Text manpowerOutputText;

        buildingMenuClass(townWindow &parent, sf::Font &font);
        void update(std::vector<buildingClass> &buildings, std::vector<textureClass> &textures);
        void buildBuilding(std::vector<buildingClass> &buildings, std::vector<resourceClass> &resources, std::vector<townClass> &towns, std::vector<goodClass> goods);

    private:
        ///Font
        sf::Font font;
        ///BASIC INFO
        std::string buildingName;
        std::string buildingDesc;
        std::string requiredMaterials;
        /// STATS
        std::string foodOutput;
        std::string productionOutput;
        std::string manpowerOutput;

};

class townWindow
{
    public:
        sf::RectangleShape windowBox;

        std::string nameStr;
        sf::Text nameText;

        std::string infoStr;
        sf::Text infoText;

        hexagon* hex;
        townClass* currentTown;

        bool display;

        sf::RectangleShape pic1;
        sf::RectangleShape pic2;
        sf::RectangleShape pic3;
        sf::RectangleShape pic4;
        sf::RectangleShape pic5;

        sf::Texture *populationTexture;
        sf::Texture *manpowerTexture;
        sf::Texture *incomeTexture;
        sf::Texture *foodTexture;
        sf::Texture *productionTexture;
        sf::Texture *buildingMenuButtonTexture;
        sf::Texture *unitMenuButtonTexture;

        sf::CircleShape unitMenuButton;
        sf::CircleShape buildingMenuButton;
        bool displayBuildingMenu;
        bool displayUnitMenu;

        townWindow(sf::Font &font, std::vector<textureClass> &textures);
        void update(hexagon* hexagon, std::vector<townClass> &towns);
        void spawnBuildingMenu(std::vector<buildingClass> &buildings, std::vector<textureClass> &textures, buildingMenuClass &buildingMenu);
        void destroyBuildingMenu();
        void spawnUnitMenu();
        void destroyUnitMenu();
};

///Initial Setup
    ///Camera & Views
    void cameraInit(sf::View &camera, sf::View &hudView, sf::RenderWindow &app, sf::Font &mainFont, int gridSize);
    void genTownWindow(hexWindow &window);
    ///Loading Extern Files
    std::vector<nationClass> loadNations(void);
    std::vector<resourceClass> loadResources(std::vector<terrainClass> &terrains);
    std::vector<textureClass> loadTextures(void);
    std::vector<goodClass> loadGoods(std::vector<resourceClass> &resources);
    std::vector<buildingClass> loadBuildings(std::vector<resourceClass> &resources, std::vector<goodClass> &goods);
    ///Grid Generation & Pathfinding
    std::vector<terrainClass> loadTerrains(void);
    void genGrid(std::vector<hexagon> &hexs, int gridSize, int seed, sf::View &camera, std::vector<nationClass> &nations, std::vector<resourceClass> &resources, std::vector<textureClass> &textures, std::vector<townClass> &towns, std::vector<AIBoat> &AIBoats, std::vector<int> &edgeTiles, std::vector<goodClass> &goods);
    std::vector<hexagon*> popTownTiles(std::vector<townClass> &towns, std::vector<hexagon> &hexs, std::vector<int> &edgeTiles);
    std::vector<std::vector<hexagon*> > initPathGen(std::vector<hexagon*> towns, std::vector<hexagon> hexs, int gridSize, std::vector<int> &edgeTiles, unsigned threads);
    ///AIBoats
    void spawnBoats(std::vector<textureClass> &textures, std::vector<AIBoat> &AIBoats, std::vector<hexagon> &hexs, std::vector<std::vector<hexagon*> > &townPaths, std::vector<townClass> &towns, std::vector<goodClass> &goods);

///EventHandler
void handleEvents(sf::RenderWindow &app, std::vector<hexagon> &hexs, townWindow &townWindow, hexWindow &window, playerClass &player, int gridSize, sf::View &camera, sf::View &hudView, std::vector<townClass> &towns, int daySpeed, std::vector<buildingClass> &buildings, std::vector<textureClass> &textures, buildingMenuClass &buildingMenu, std::vector<resourceClass> &resources, std::vector<goodClass> &goods);
///Camera & Views
void update_view(sf::RenderWindow &app, sf::View &camera, sf::View &hudView, std::vector<hexagon> &hexs, hexWindow &window, hudClass &HUD, playerClass &player, townWindow &townWindow, std::vector<AIBoat> &AIBoats, buildingMenuClass buildingMenu);
///Time Handling
void daytick(hudClass &HUD, std::vector<AIBoat> &AIBoats, std::vector<std::vector<hexagon*> > &townPaths, Date &date, bool &monthTick, bool &yearTick, playerClass &player, std::vector<townClass> &towns, std::vector<goodClass> &goods);
void monthtick(std::vector<townClass> &towns, std::vector<hexagon> &hexs, std::vector<resourceClass> resources, std::vector<goodClass> &goods, std::vector<std::vector<hexagon*> > &townPaths);
void yeartick(void);
///Path finding
std::vector<hexagon*> findPath(pathParameters params);
bool compHexs(const hexagon* a, const hexagon* b);
bool inVector(std::vector<hexagon*> vec, hexagon* adj);

#endif // CUSTOM_H_INCLUDED
