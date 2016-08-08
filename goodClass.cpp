#include "custom.h"

goodClass::goodClass(std::string name, std::string unit, int stdNum, float price, std::string textureName, std::vector<resourceClass> materials)
{
    this->name = name;
    this->unit = unit;
    this->stdNum = stdNum;
    this->price = price;
    this->textureName = textureName;
    this->materials = materials;
}
