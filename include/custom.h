#ifndef CUSTOM_H_INCLUDED
#define CUSTOM_H_INCLUDED

#include <iostream>


#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "networking.h"

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
#include <memory>


//enum Terrain {none, sea, land, mountain, sand, jungle, town, lake};
enum Terrain {none, sea, lake, sand, land, jungle, town, mountain};
enum Day {monday, tuesday, wednesday, thursday, friday, saturday, sunday};
enum Month {january, february, march, april, may, june, july, august, september, october, november, december};
enum timeFrequency {daily, weekly, biweekly, monthly, quarterly, annualy};
enum direction {up, right, down, left};

class loadingScreenParams
{
    public:
        sf::View camera;
        sf::RenderWindow* app;
        bool* finished;
        double* percentageCharted;

        loadingScreenParams(sf::View &camera, sf::RenderWindow* app, bool* finished, double* percentageCharted)
        {
            this->camera = camera;
            this->app = app;
            this->finished = finished;
            this->percentageCharted = percentageCharted;
        }
};

class worldMenuEntry
{
    public:
        sf::RectangleShape tile;
        sf::RectangleShape image;
        std::string nameStr;
        sf::Text nameText;

        worldMenuEntry(sf::Vector2f &pos, sf::Font &mainFont)
        {
            this->tile.setPosition(pos);
            this->tile.setFillColor(sf::Color(20, 20, 20, 128));
            this->tile.setSize(sf::Vector2f(300, 300));

            this->image.setPosition(this->tile.getPosition() + sf::Vector2f(25, 25));
            this->image.setSize(sf::Vector2f(200, 250));

            this->nameStr = "";
            this->nameText.setPosition(this->image.getPosition() + sf::Vector2f(50, 250));
            this->nameText.setCharacterSize(20);
            this->nameText.setColor(sf::Color::White);
            this->nameText.setFont(mainFont);
        }
};

class terrainClass
{
    public:
        Terrain terrain;
        std::string name;
        int movementPoints;

        terrainClass(Terrain terrain, std::string name, int movementPoints);
        terrainClass(){this->terrain = sea; this->name = "sea"; this->movementPoints = 1;};


        inline bool operator==(const Terrain &lhs){ bool x; return x = (lhs == this->terrain) ? true : false; }
        terrainClass &operator=(const Terrain &rhs);
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

class hexagon;
class townWindow;
class buildingMenuClass;
class tradeDealsWindowClass;
class AIBoat;
class nationClass;

class tradeDealClass
{
    public:
        std::string name;
        goodClass tradeGood;
        float tradeGoodVolume;
        double payment;
        timeFrequency tradeFrequency;
        std::vector<hexagon*> path;

        tradeDealClass(std::string name, goodClass tradeGood, int tradeGoodVolume, int payment, timeFrequency tradeFrequency);
};

class townClass
{
    public:
        nationClass* nation;
        hexagon* tile;
        int income;
        int expenditure;
        int townSize;
        int garrison;
        int population;
        int food;
        int production;
        int manPower;
        std::string name;
        std::vector<tradeDealClass> openDeals;
        std::vector<hexagon*> ownedTiles;
        std::vector<goodClass> goods;
        std::vector<buildingClass> buildings;

        townClass(hexagon* tile, std::vector<hexagon*> &adjTiles, std::vector<hexagon> &hexs, int gridSize, std::vector<goodClass> &goods, nationClass* nation);
        int resourceCount(resourceClass resource);
        void setTownName(std::vector<townClass> &towns);
        std::string getTownName(void);
        void monthTick(std::vector<hexagon> &hexs);
        void generateTradeDeals(std::vector<goodClass> &goods, std::vector<std::vector<hexagon*> > &townPaths, std::vector<AIBoat> &AIBoats, std::vector<textureClass> &textures, std::vector<hexagon> &hexs, std::vector<townClass> &towns);
        bool isBesieged(std::vector<hexagon> &hexs, int &gridSize);
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

class triangle : public sf::CircleShape
{
    public:
        triangle(std::vector<sf::Texture> &alphaTextures, int radius, int points, hexagon* parent, int rotation);
        sf::Texture const * diffuseTexture;
        sf::Texture* alphaTexture;
};

class unit;

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
        terrainClass terrain;
        resourceClass resource;
        std::string owner;
        townClass* townOnTile;
        std::vector<unit*> unitsOnTile;
    //Graphics
        sf::CircleShape hex;
        sf::CircleShape resourceIcon;
        sf::CircleShape ownerHex;
        std::vector<triangle> triangles;

        hexagon();
        std::vector<hexagon*> adjacentTiles(std::vector<hexagon> &hexs, int vectorSize);
        std::vector<hexagon*> adjacentTilesByCoords(std::vector<hexagon> &hexs, int &gridSize);
        adjTileCounter countAdjacentTiles(std::vector<hexagon> &hexs, int gridSize);
        int distanceTo(hexagon* to);
        void setupTris(std::vector<sf::Texture> &alphaTextures);
};

class nationClass
{
    public:
        sf::Color colour;
        sf::Texture flag;
        std::string name;
        std::string possessive;
        std::string atWarWithName;
        float money;

        nationClass(std::string name="none", std::string possesive="none", sf::Color colour=sf::Color::White);
        virtual ~nationClass(){};
};

class colonialNation : public nationClass
{
    public:
        void declareWar(nationClass &target);
        colonialNation(void) : nationClass(){};
        colonialNation(nationClass &nation) : nationClass(nation.name, nation.possessive, nation.colour){};
};

class tribalNation : public nationClass
{
    public:
        tribalNation(void) : nationClass(){};
        tribalNation(nationClass &nation) : nationClass(nation.name, nation.possessive, nation.colour){};
    private:
        void resettle();
};




class unit : public sf::Sprite
{
    public:
        nationClass* owner;
        int movementPoints;
        hexagon* tileOccupying;
        unit(nationClass* owner, int movementPoints, hexagon* tileOccupying, const sf::Texture &texture) : sf::Sprite(texture) {this->owner = owner; this->movementPoints = movementPoints; this->tileOccupying = tileOccupying; this->tileOccupying->unitsOnTile.push_back(this);};
};

class militaryUnit : public unit
{
    public:
        float baseDamage;
        float health;
        militaryUnit(nationClass* owner, int movementPoints, hexagon* tileOccupying, const sf::Texture &texture) : unit(owner, movementPoints, tileOccupying, texture){};
};

class militaryLandUnit : public militaryUnit
{
    public:
        float adjAlliedUnitsModifier();
        militaryLandUnit(nationClass* owner, int movementPoints, hexagon* tileOccupying, const sf::Texture &texture) : militaryUnit(owner, movementPoints, tileOccupying, texture){};
};

class militaryNavalUnit : public militaryUnit
{
    public:
        int cannons;
        int sailors;

        float adjAlliedUnitsModifier();
};

class settler : public unit
{
    public:
        bool settleTown();
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

        float health;
        direction shipDirection;
        int firingRange;
        float reloadTime;
        float currentReloadTime;

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
        void fireCannons(const bool &isIntersecting, AIBoat &enemyShip);
};

class AIBoat : public shipClass
{
    public:
        bool destroy;
        bool inactive;
        nationClass* nation;
        tradeDealClass* td;
        sf::Vector2f battleMovement;

        AIBoat(sf::Texture &texture, std::vector<hexagon> &hexs, std::vector< std::vector<hexagon*> > &townPaths, std::vector<townClass> &towns, std::vector<goodClass> &goods) : shipClass(hexs, towns, goods)
        {   this->setScale(10, 10);
            this->setTexture(texture);
            this->name = "Boaty McBoatFace";
            this->speed = rand() % 5 + 2;
            this->destroy = false;
            this->inactive = false;
            this->battleMovement = sf::Vector2f(-0.005f, -0.005f);

            if(this->speed <= 0)
                printf("%i\n", this->speed);

            for(auto &t : townPaths)
                if(t.at(0)->index == this->currentHex->index)
                    this->currentPath = t;
        };
};

inline bool shouldDestroy(const AIBoat &o)
{
    return o.destroy;
};

class tradeDealsWindowClass;

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

        sf::CircleShape tradeDealsButton;
        bool showTradeDeals;
        tradeDealsWindowClass* tradeDealWindow;

        hudClass(sf::View &hudView, sf::Font &mainFont, std::vector<textureClass> &textures);
        void update(playerClass &player, Date &date);
};

class tradeDealDisplayableClass
{
    public:
        sf::Text dealText;
        sf::RectangleShape goodPic;
};

class tradeDealsWindowClass
{
    public:
        sf::RectangleShape window;
        sf::RectangleShape prevButton;
        sf::RectangleShape nextButton;
        sf::Text dealText;
        std::vector<tradeDealDisplayableClass> deals;
        int windowTabs;
        int index;

        tradeDealsWindowClass(sf::Vector2f &spawnButtonPos);
        void updateDeals(std::vector<townClass> &towns, std::vector<textureClass> &textures, sf::Font &font);
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

/// Menus
int mainMenu(sf::RenderWindow &app, unsigned &threads);
int gameSetup(sf::RenderWindow &app, sf::View &menuView, unsigned &threads);
int worldBrowser(sf::RenderWindow &app, sf::View &menuView);

int loadingScreen(loadingScreenParams &loadingParams);

///Initial Game Setup
int gameMain(sf::RenderWindow &app, int &gridSize, uint32_t &seed, std::string &playerName, unsigned &threads);


///Initial Setup
    ///Camera & Views
    void cameraInit(sf::View &camera, sf::View &hudView, sf::RenderWindow &app, sf::Font &mainFont, int gridSize);
    void genTownWindow(hexWindow &window);
    ///Loading Extern Files
    std::vector<std::shared_ptr<nationClass> > loadNations(void);
    void constructNation(std::shared_ptr<nationClass> &newNation, std::vector<std::shared_ptr<nationClass> > &nations);
    std::vector<resourceClass> loadResources(std::vector<terrainClass> &terrains);
    std::vector<textureClass> loadTextures(void);
    std::vector<goodClass> loadGoods(std::vector<resourceClass> &resources);
    std::vector<buildingClass> loadBuildings(std::vector<resourceClass> &resources, std::vector<goodClass> &goods);
    ///Grid Generation & Pathfinding
    std::vector<terrainClass> loadTerrains(void);
    void genGrid(std::vector<hexagon> &hexs, int gridSize, uint32_t seed, sf::View &camera, std::vector<std::shared_ptr<nationClass> > &nations, std::vector<resourceClass> &resources, std::vector<textureClass> &textures, std::vector<townClass> &towns, std::vector<AIBoat> &AIBoats, std::vector<int> &edgeTiles, std::vector<goodClass> &goods, sf::RenderWindow &app);
    std::vector<hexagon*> popTownTiles(std::vector<townClass> &towns, std::vector<hexagon> &hexs, std::vector<int> &edgeTiles);
    std::vector<std::vector<hexagon*> > initPathGen(std::vector<hexagon*> towns, std::vector<hexagon> hexs, int gridSize, std::vector<int> &edgeTiles, unsigned threads, double* percentageCharted);
    ///AIBoats
    void spawnBoats(std::vector<textureClass> &textures, std::vector<AIBoat> &AIBoats, std::vector<hexagon> &hexs, std::vector<std::vector<hexagon*> > &townPaths, std::vector<townClass> &towns, std::vector<goodClass> &goods);
    void endBattle(playerClass &player, std::vector<AIBoat> &AIBoats, const bool &playerVictory);
    void AIBattleLoop(std::vector<AIBoat> &AIBoats, playerClass &player, std::vector<sf::RectangleShape> &nodes, sf::FloatRect &intersectionRect, std::clock_t &start);
    ///AI Towns
    void buildBuilding(buildingClass &building, std::vector<resourceClass> &resources, std::vector<goodClass> &goods, townClass* currentTown);
///EventHandler
void handleEvents(sf::RenderWindow &app, std::vector<hexagon> &hexs, hudClass &HUD, townWindow &townWindow, hexWindow &window, playerClass &player, int gridSize, sf::View &camera, sf::View &hudView, std::vector<townClass> &towns, int daySpeed, std::vector<buildingClass> &buildings, std::vector<textureClass> &textures, buildingMenuClass &buildingMenu, std::vector<resourceClass> &resources, std::vector<goodClass> &goods, sf::Font &font, bool &paused, std::vector<AIBoat> &AIBoats, std::vector<unit> &units, std::vector<std::shared_ptr<nationClass> > &nations);

///Camera & Views
void update_view(sf::RenderWindow &app, sf::View &camera, sf::View &hudView, std::vector<hexagon> &hexs, hexWindow &window, hudClass &HUD, playerClass &player, townWindow &townWindow, std::vector<AIBoat> &AIBoats, buildingMenuClass buildingMenu, tradeDealsWindowClass &tradeDealWindow, std::vector<terrainClass> &terrains, sf::Shader &landBlendShader, std::vector<unit> &units);
///Time Handling
void daytick(hudClass &HUD, std::vector<AIBoat> &AIBoats, std::vector<std::vector<hexagon*> > &townPaths, Date &date, bool &monthTick, bool &yearTick, playerClass &player, std::vector<townClass> &towns, std::vector<goodClass> &goods, std::vector<hexagon> &hexs, int &gridSize, std::vector<std::shared_ptr<nationClass> > &nations);
void monthtick(std::vector<townClass> &towns, std::vector<goodClass> &goods, std::vector<std::vector<hexagon*> > &townPaths, std::vector<AIBoat> &AIBoats, std::vector<textureClass> &textures, std::vector<hexagon> &hexs, std::vector<std::shared_ptr<nationClass> > &nations, std::vector<buildingClass> &buildings, std::vector<resourceClass> &resources);
void yeartick(void);
///Path finding
std::vector<hexagon*> findPath(pathParameters params);
bool compHexs(const hexagon* a, const hexagon* b);
bool inVector(std::vector<hexagon*> vec, hexagon* adj);


bool initiateCombat(sf::RenderWindow &app, sf::View camera, playerClass &player, std::vector<AIBoat> &AIBoats);

#endif // CUSTOM_H_INCLUDED
