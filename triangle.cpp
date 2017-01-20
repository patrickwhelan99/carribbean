#include "custom.h"

triangle::triangle(std::vector<sf::Texture> &alphaTextures, int radius, int points, hexagon* parent, int rotation) : sf::CircleShape(radius, points)
{
    this->setOrigin(radius, 0);
    this->setPosition(parent->hex.getPosition());
    this->setRotation(rotation);

    this->diffuseTexture = parent->hex.getTexture();

    int randNum = rand() % alphaTextures.size() + 0;
    this->alphaTexture = &(alphaTextures.at(randNum));
    this->setTexture(this->diffuseTexture);
    parent->triangles.push_back(*this);
}
