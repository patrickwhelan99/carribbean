#include "custom.h"

goodClass::goodClass(std::string name, std::string unit, int stdNum, double price, std::string textureName, std::vector<resourceClass> materials)
{
    this->name = name;
    this->unit = unit;
    this->stdNum = stdNum;
    this->price = price;
    this->originalPrice = price;
    this->textureName = textureName;
    this->materials = materials;
    this->num = 0;
}
