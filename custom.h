#ifndef CUSTOM_H_INCLUDED
#define CUSTOM_H_INCLUDED
#include <SFML/Graphics.hpp>
//#include "terrain.cpp"

enum Terrain {sea, land, mountain, sand, jungle, town, lake};
enum Resource {none, fish, coca, wheat, cattle, tobacco, cotton, horses, metals};
enum Owner {noOne, england, portugal, spain, france};

class terrain
{
    public:
			std::string name;
			std::string desc;
			int movementPoints;
			sf::Color colour;


			terrain(std::string name, std::string desc, int movementPoints, sf::Color colour);
};

class hexagon : public sf::CircleShape
{
    public:
        int x;
        int y;
        int index;
        Terrain terrain;
        Resource resource;
        Owner owner;
        sf::CircleShape hex;
        sf::CircleShape resourceIcon;
        sf::CircleShape ownerHex;

        hexagon(int x, int y);
        std::vector<hexagon*> adjacentTiles(std::vector<hexagon> &hexs, int vectorSize);
    private:
    protected:

};

void update_view(sf::RenderWindow &app, sf::View &camera, std::vector<hexagon> hexs);
std::vector<hexagon> genGrid(int gridSize, sf::View &camera, sf::Texture &cocaTexture, sf::Texture &wheatTexture, sf::Texture &fishTexture, sf::Texture &cattleTexture, sf::Texture &tobaccoTexture, sf::Texture &cottonTexture, sf::Texture &horsesTexture, sf::Texture &metalsTexture);


#endif // CUSTOM_H_INCLUDED
