#include "custom.h"

buildingClass::buildingClass(std::string name, std::string desc, std::string textureStr, int foodOutput, int productionOutput, int manpowerOutput, std::vector<resourceClass> requiredMaterials)
{
    this->name = name;
    this->desc = desc;
    this->textureStr = textureStr;
    this->foodOutput = foodOutput;
    this->productionOutput = productionOutput;
    this->manpowerOutput = manpowerOutput;
    this->requiredMaterials = requiredMaterials;
}
