#ifndef CUSTOM_H_INCLUDED
#define CUSTOM_H_INCLUDED
#include <SFML/Graphics.hpp>

enum Terrain {none, sea, land, mountain, sand, jungle, town, lake};
enum Owner {noOne, england, portugal, spain, france};

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
        int x;
        int y;
        int z;
        int index;
        Terrain terrain;
        resourceClass resource;
        Owner owner;
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
        std::string name;
        Terrain terrain;
        Owner owner;
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

        hexWindow(hexagon* hexagon, sf::View &hud, sf::Font &font);
        ~hexWindow();
        std::string genString();
};

void update_view(sf::RenderWindow &app, sf::View &camera, sf::View &hud, std::vector<hexagon> hexs, hexWindow* window);
std::vector<hexagon> genGrid(int gridSize, sf::View &camera, std::vector<resourceClass> &resources, std::vector<textureClass> &textures);
std::vector<resourceClass> loadResources(void);
std::vector<textureClass> loadTextures(void);

#endif // CUSTOM_H_INCLUDED
