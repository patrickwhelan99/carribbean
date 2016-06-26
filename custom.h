#ifndef CUSTOM_H_INCLUDED
#define CUSTOM_H_INCLUDED
#include <SFML/Graphics.hpp>

enum Terrain {none, sea, land, mountain, sand, jungle, town, lake};
enum Owner {noOne, england, portugal, spain, france, playerOwned};
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


            resourceClass(std::string name = "none", std::string texture = "default.png", int spawnChance = 0, std::vector<Terrain> requiredTerrain = std::vector<Terrain>(), int food = 0, int production = 0);
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

        townClass(hexagon* tile, std::vector<hexagon*> &adjTiles, Owner owner);
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
        Owner owner;
        townClass* town;
    //Graphics
        sf::CircleShape hex;
        sf::CircleShape resourceIcon;
        sf::CircleShape ownerHex;

        hexagon();
        std::vector<hexagon*> adjacentTiles(std::vector<hexagon> &hexs, int vectorSize);
        int distanceTo(hexagon* to);
    private:
    protected:

};

class counter
{
    public:
        int total;
        float percentage;
        std::string name;
        Terrain terrain;
        Owner owner;
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

class player : public sf::Sprite
{
    public:
        int money;
        std::string name;
        player(sf::Texture &texture, std::vector<hexagon> &hexs);
        hexagon* currentHex;
        int x;
        int y;
        int z;
};

class AIBoat : public sf::Sprite
{
    public:
        std::string name;
        hexagon* currentHex;
        int x;
        int y;
        int z;
        std::vector<hexagon*> currentPath;

        AIBoat(sf::Texture &texture, std::vector<hexagon> &hexs, std::vector< std::vector<hexagon*> > &townPaths);
        bool moveNext(std::vector<hexagon> &hexs, int &gridSize);
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
        void update(player &player, Date &date);
};

class parameters
{
    public:
        std::vector<hexagon*> hexPath;
        player* character;
        double daySpeed;
};

class pathParameters
{
    public:
        hexagon* tile1;
        hexagon* tile2;
        std::vector<hexagon> hexs;
        int gridSize;

        pathParameters(hexagon* town1, hexagon* town2, std::vector<hexagon> &hexs, int gridSize);
        pathParameters(void);
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

        townWindow(sf::Font &font);
        void update(hexagon* hexagon, std::vector<townClass> &towns);
};


void update_view(sf::RenderWindow &app, sf::View &camera, sf::View &hudView, std::vector<hexagon> &hexs, hexWindow &window, hudClass &HUD, player &player, townWindow &townWindow, std::vector<AIBoat> &AIBoats);

std::vector<hexagon> genGrid(int gridSize, sf::View &camera, std::vector<resourceClass> &resources, std::vector<textureClass> &textures, std::vector<townClass> &towns, std::vector<AIBoat> &AIBoats);

std::vector<resourceClass> loadResources(void);
std::vector<textureClass> loadTextures(void);

//std::vector<hexagon*> findPath(hexagon* currentTile, hexagon* tileTo, std::vector<hexagon> &hexs, int gridSize);
std::vector<hexagon*> findPath(pathParameters &params);
void playerMovement(parameters p);

void genTownWindow(hexWindow &window);

bool compHexs(const hexagon* a, const hexagon* b);
bool inVector(std::vector<hexagon*> vec, hexagon* adj);

#endif // CUSTOM_H_INCLUDED
