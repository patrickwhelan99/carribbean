#include "custom.h"
#include <random>

void daytick(hudClass &HUD, std::vector<AIBoat> &AIBoats, std::vector<std::vector<hexagon*> > &townPaths, Date &date, bool &monthTick, bool &yearTick, playerClass &player, std::vector<townClass> &towns, std::vector<goodClass> &goods)
{
    ///Update Hud info
    HUD.dateStr = date.update(monthTick, yearTick);

    ///Move Player
    player.moveNext();

    ///Move AI Boats
    for(auto &boat : AIBoats)
    {
        boat.moveNext();

        while(boat.currentPath.size() == 0)
        {
            int randnum = rand() % ((townPaths.size()) + 0);
            if(townPaths.at(randnum).at(0)->index == boat.currentHex->index)
            {
                boat.currentPath = townPaths.at(randnum);
                break;
            }
        }
    }


///Add daily production of goods to towns total
    for(auto &t : towns)
    {
        for(auto &g : t.goods)
        {
            for(auto &b : t.buildings)
            {
                if(b.outputGood.name == g.name)
                {
                    g.num += b.outputGoodVolume;
                }
            }
        }
    }

///Calculate Value of goods according to basic supply/demand model, good.price is then set accordingly
    for(auto &g : goods)
        {
            if(g.name != "none")
            {
                double worldNum = 0;
                for(auto &t : towns)
                {
                    for(auto &x : t.goods)
                    {
                        if(x.name == g.name)
                            worldNum += x.num;
                    }
                }

                for(auto &s : AIBoats)
                {
                    for(auto &i : s.inventory)
                    {
                        if(i.name == g.name)
                            worldNum += i.num;
                    }
                }

                for(auto &i : player.inventory)
                    {
                        if(i.name == g.name)
                            worldNum += i.num;
                    }

                if(worldNum != 0)
                {
                    g.price = g.originalPrice * (g.stdNum/worldNum);
                }
            }

        }
}
