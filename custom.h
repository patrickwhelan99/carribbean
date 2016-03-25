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
        int index;
        Terrain terrain;
        resourceClass resource;
        Owner owner;
        sf::CircleShape hex;
        sf::CircleShape resourceIcon;
        sf::CircleShape ownerHex;

        hexagon(int x, int y);
        std::vector<hexagon*> adjacentTiles(std::vector<hexagon> &hexs, int vectorSize);
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

void update_view(sf::RenderWindow &app, sf::View &camera, std::vector<hexagon> hexs);
std::vector<hexagon> genGrid(int gridSize, sf::View &camera, std::vector<resourceClass> &resources, std::vector<textureClass> &textures);
std::vector<resourceClass> loadResources(void);
std::vector<textureClass> loadTextures(void);

#endif // CUSTOM_H_INCLUDED
