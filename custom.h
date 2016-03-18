#ifndef CUSTOM_H_INCLUDED
#define CUSTOM_H_INCLUDED
#include <SFML/Graphics.hpp>

enum Terrain {sea, land, mountain, sand, jungle, town, lake};
enum Resource {none, fish, coca, wheat, cattle, tobacco, cotton};

class hexagon : public sf::CircleShape
{
    public:
        int x;
        int y;
        int index;
        Terrain terrain;
        Resource resource;
        sf::CircleShape hex;
        sf::CircleShape resourceIcon;

        hexagon(int x, int y);
        std::vector<hexagon*> adjacentTiles(std::vector<hexagon> &hexs, int vectorSize);
        int adjacentLand(std::vector<hexagon> &hexs);
        int adjacentSand(std::vector<hexagon> &hexs);
        int adjacentSea(std::vector<hexagon> &hexs);
        int adjacentTown(std::vector<hexagon> &hexs);
    private:
    protected:

};

void update_view(sf::RenderWindow &app, sf::View &camera, std::vector<hexagon> hexs);
std::vector<hexagon> genGrid(int gridSize, sf::View &camera);


#endif // CUSTOM_H_INCLUDED
