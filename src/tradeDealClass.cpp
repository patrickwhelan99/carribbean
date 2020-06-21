#include "../include/custom.h"

tradeDealClass::tradeDealClass(std::string name, goodClass tradeGood, int tradeGoodVolume, int payment, timeFrequency tradeFrequency)
{
    this->name = name;
    this->tradeGood = tradeGood;
    this->tradeGoodVolume = tradeGoodVolume;
    this->payment = payment;
    this->tradeFrequency = tradeFrequency;
}
