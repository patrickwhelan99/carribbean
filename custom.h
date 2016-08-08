#ifndef CUSTOM_H_INCLUDED
#define CUSTOM_H_INCLUDED
#include <SFML/Graphics.hpp>

enum Terrain {none, sea, land, mountain, sand, jungle, town, lake};
enum Day {monday, tuesday, wednesday, thursday, friday, saturday, sunday};
enum Month {january, february, march, april, may, june, july, august, september, october, november, december};

class textureClass : public sf::Texture
{
    public:
        std::string name;
        textureClass();
};

class resourceClass
{
    public:
            int spawnChance;
            std::string name;
            sf::CircleShape icon;
            std::vector<Terrain> requiredTerrain;
            std::string textureName;
            int food;
            int production;


            resourceClass(std::string name = "none", std::string texture = "", int spawnChance = 0, std::vector<Terrain> requiredTerrain = std::vector<Terrain>(), int food = 0, int production = 0);
};

class goodClass
{
    public:
        sf::CircleShape icon;
        int stdNum;
        std::string name;
        float price;
        std::string unit; //kg or litre etc
        std::string textureName;
        std::vector<resourceClass> materials;

        goodClass(std::string name="none", std::string unit="unit", int stdNum=1000, float price=10, std::string textureName="none", std::vector<resourceClass> materials = std::vector<resourceClass>());
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
        std::vector<resourceClass> requiredMaterials;

        buildingClass(std::string name="none", std::string desc="none", std::string textureStr="none", int foodOutput=0, int productionOutput=0, int manpowerOutput=0, std::vector<resourceClass> requiredMaterials = std::vector<resourceClass>());
};

class hexagon;

class townClass
{
    public:
        hexagon* tile;
        std::string name;
        int income;
        int expenditure;
        int manPower;
        int garrison;
        int population;
        int food;
        int production;
        int townSize;
        std::vector<hexagon*> ownedTiles;
        std::vector<buildingClass> buildings;

        townClass(hexagon* tile, std::vector<hexagon*> &adjTiles, std::vector<hexagon> &hexs, int gridSize);
        int resourceCount(resourceClass resource);
        void setTownName(std::vector<townClass> &towns);
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
        adjTileCounter countAdjacentTiles(std::vector<hexagon> &hexs, int gridSize);
        int distanceTo(hexagon* to);
    private:
    protected:

};

class nationClass
{
    public:
        sf::Color colour;
        std::string name;
        std::string possessive;

        nationClass(std::string name="none", std::string possesive="none", sf::Color colour=sf::Color::White);
};

class counter
{
    public:
        int total;
        float percentage;
        std::string name;
        Terrain terrain;
        std::string owner;
        std::vector<Terrain> spawnTerrains;
        counter();
};

class hexWindow
{
    public:
        sf::RectangleShape rect;
        std::string infoStr;
        sf::Text infoText;
        hexagon* hex;
        int distance;
        bool display;


        hexWindow(hexagon* hexagon, sf::View &hud, sf::Font &font);
        ~hexWindow();
        std::string genString();
};


class Date
{
    public:
        Day day;
        std::string dayStr;
        Month month;
        std::string monthStr;
        int monthDay;
        int year;

        Date();
        std::string update(bool &monthTick, bool &yearTick);
};

class playerClass : public sf::Sprite
{
    public:
        int money;
        std::string name;
        std::vector<hexagon*> currentPath;
        hexagon* currentHex;
        int x;
        int y;
        int z;
        int speed;

        playerClass(sf::Texture &texture, std::vector<hexagon> &hexs, std::string &name, std::vector<townClass> &towns);
        void moveNext(void);
};

class AIBoat : public sf::Sprite
{
    public:
        std::string name;
        hexagon* currentHex;
        int x;
        int y;
        int z;
        int speed;
        std::vector<hexagon*> currentPath;

        AIBoat(sf::Texture &texture, std::vector<hexagon> &hexs, std::vector< std::vector<hexagon*> > &townPaths);
        bool moveNext(void);
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

class parameters
{
    public:
        std::vector<hexagon*> hexPath;
        playerClass* character;
        double daySpeed;
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
        sf::Font font;

        ///MAIN WINDOW
        sf::RectangleShape windowBox;

        ///BASIC INFO
        std::string buildingName;
        sf::Text buildingNameText;

        std::string buildingDesc;
        sf::Text buildingDescText;

        std::string requiredMaterials;
        sf::Text requiredMaterialsText;

        /// STATS
        std::string foodOutput;
        sf::Text foodOutputText;

        std::string productionOutput;
        sf::Text productionOutputText;

        std::string manpowerOutput;
        sf::Text manpowerOutputText;

        /// IMAGES
        sf::RectangleShape buildingPic;
        sf::RectangleShape foodPic;
        sf::RectangleShape productionPic;
        sf::RectangleShape manpowerPic;

        /// BUTTONS
        sf::RectangleShape buildButton;
        sf::RectangleShape next;
        sf::RectangleShape previous;

        buildingMenuClass(townWindow &parent, sf::Font &font);
        void update(std::vector<buildingClass> &buildings, std::vector<textureClass> &textures);
        void buildBuilding(std::vector<buildingClass> &buildings, std::vector<resourceClass> &resources, std::vector<townClass> &towns);
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
    std::vector<resourceClass> loadResources(void);
    std::vector<textureClass> loadTextures(void);
    std::vector<goodClass> loadGoods(std::vector<resourceClass> &resources);
    std::vector<buildingClass> loadBuildings(std::vector<resourceClass> &resources);
    ///Grid Generation & Pathfinding
    void genGrid(std::vector<hexagon> &hexs, int gridSize, int seed, sf::View &camera, std::vector<nationClass> &nations, std::vector<resourceClass> &resources, std::vector<textureClass> &textures, std::vector<townClass> &towns, std::vector<AIBoat> &AIBoats, std::vector<int> &edgeTiles);
    std::vector<hexagon*> popTownTiles(std::vector<townClass> &towns, std::vector<hexagon> &hexs, std::vector<int> &edgeTiles);
    std::vector<std::vector<hexagon*> > initPathGen(std::vector<hexagon*> towns, std::vector<hexagon> hexs, int gridSize, std::vector<int> &edgeTiles, unsigned threads);
    ///AIBoats
    void spawnBoats(std::vector<textureClass> &textures, std::vector<AIBoat> &AIBoats, std::vector<hexagon> &hexs, std::vector<std::vector<hexagon*> > &townPaths);

///EventHandler
void handleEvents(sf::RenderWindow &app, std::vector<hexagon> &hexs, townWindow &townWindow, hexWindow &window, playerClass &player, int gridSize, sf::View &camera, sf::View &hudView, std::vector<townClass> &towns, int daySpeed, std::vector<buildingClass> &buildings, std::vector<textureClass> &textures, buildingMenuClass &buildingMenu, std::vector<resourceClass> &resources);
///Camera & Views
void update_view(sf::RenderWindow &app, sf::View &camera, sf::View &hudView, std::vector<hexagon> &hexs, hexWindow &window, hudClass &HUD, playerClass &player, townWindow &townWindow, std::vector<AIBoat> &AIBoats, buildingMenuClass buildingMenu);
///Time Handling
void daytick(hudClass &HUD, std::vector<AIBoat> &AIBoats, std::vector<std::vector<hexagon*> > &townPaths, Date &date, bool &monthTick, bool &yearTick, playerClass &player);
void monthtick(std::vector<townClass> &towns, std::vector<hexagon> &hexs, std::vector<resourceClass> resources);
void yeartick(void);
///Path finding
std::vector<hexagon*> findPath(pathParameters params);
void playerMovement(parameters p);
bool compHexs(const hexagon* a, const hexagon* b);
bool inVector(std::vector<hexagon*> vec, hexagon* adj);

#endif // CUSTOM_H_INCLUDED
