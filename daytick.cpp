#include "custom.h"
#include <random>

void daytick(hudClass &HUD, std::vector<AIBoat> &AIBoats, std::vector<std::vector<hexagon*> > &townPaths, Date &date, bool &monthTick, bool &yearTick)
{
    ///Update Hud info
    HUD.dateStr = date.update(monthTick, yearTick);


    ///Move AI Boats
    for(auto &boat : AIBoats)
    {
        if(!boat.moveNext())
        {
            while(true)
            {
                int randnum = rand() % ((townPaths.size()-1) + 1);
                if(townPaths.at(randnum).at(0)->index == boat.currentHex->index)
                {
                    boat.currentPath = townPaths.at(randnum);
                    break;
                }
            }
        }
    }


}
