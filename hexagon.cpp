#include "custom.h"

hexagon::hexagon(int x, int y)
{
    this->hex = sf::CircleShape(25, 6);
    this->hex.setFillColor(sf::Color::Blue);
    this->terrain = sea;
}

std::vector<hexagon> hexagon::adjacentTiles(std::vector<hexagon> &hexs)
{
    std::vector<hexagon> adjHexs;
    for (auto &others : hexs)
    {
        if((others.x == this->x - 1 && others.y == this->y - 1) || (others.x == this->x && others.y == this->y - 1) || (others.x == this->x - 1 && others.y == this->y ) || (others.x == this->x + 1 && others.y == this->y) || (others.x == this->x && others.y == this->y + 1) || (others.x == this->x + 1 && others.y == this->y + 1))
        {
            adjHexs.push_back(others);
        }
    }

    return adjHexs;
}
