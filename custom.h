#ifndef CUSTOM_H_INCLUDED
#define CUSTOM_H_INCLUDED
#include <SFML/Graphics.hpp>

enum Terrain {none, sea, land, mountain, sand, jungle, town, lake};
enum Owner {noOne, england, portugal, spain, france};
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

            resourceClass(std::string name = "none", std::string texture = "default.png", int spawnChance = 0, std::vector<Terrain> requiredTerrain = std::vector<Terrain>());
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
        std::string update();
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
        std::vector<hexagon*> findPath(hexagon* tileTo, std::vector<hexagon> &hexs, int vectorSize);
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
};


void update_view(sf::RenderWindow &app, sf::View &camera, sf::View &hudView, std::vector<hexagon> &hexs, hexWindow &window, hudClass &HUD, player &player);
std::vector<hexagon> genGrid(int gridSize, sf::View &camera, std::vector<resourceClass> &resources, std::vector<textureClass> &textures);
std::vector<resourceClass> loadResources(void);
std::vector<textureClass> loadTextures(void);
void playerMovement(parameters p);

#endif // CUSTOM_H_INCLUDED
