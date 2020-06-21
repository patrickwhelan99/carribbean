#include "../include/custom.h"

resourceClass::resourceClass(std::string name, std::string texture, int spawnChance, std::vector<Terrain> requiredTerrain, int food, int production)
{
    this->name = name;
    this->textureName = "none";
    this->icon = sf::CircleShape(15*200, 6);
    this->spawnChance = spawnChance;
    this->requiredTerrain = requiredTerrain;
    this->food = food;
    this->production = production;
}
