#include "custom.h"
#include <future>
#include <iostream>

std::vector<std::vector<hexagon*> > initPathGen(std::vector<townClass> towns, std::vector<hexagon> hexs, int gridSize, std::vector<int> &edgeTiles)
{
    int pathsInt = static_cast<int>(towns.size());
    printf("Generating %i Paths!\n.... could take a while\n...... go and get a drink? Go outside? Go and visit your grandma? Go on holiday?\n", pathsInt*pathsInt - pathsInt);
    double percentageCharted = 0;
    std::vector< std::vector<hexagon*> > townPaths;
    std::vector<std::future< std::vector<hexagon*> > > path;
    pathParameters ppArray[static_cast<int>(towns.size()*towns.size()-towns.size())];

    int n = 0;
    int t = 0;
    printf("Stage 1:\n"); /// Generate Half of the paths
    for(auto &town1 : towns)
    {
        n=0;
        for(auto &town2 : towns)
        {
            if(town1.tile && town2.tile)
            {
                if(n<t)
                {
                    ///Do nothing will replace with reversed path of one that has already been calculated after future has been resolved
                }

                else if(town1.tile->index!=town2.tile->index)
                {
                        hexagon* a = town1.tile;
                        hexagon* b = town2.tile;
                        pathParameters p(a, b, hexs, gridSize);
                        ppArray[n] = std::move(p);
                        path.push_back(std::async(std::launch::async, findPath, std::ref(ppArray[n])));
                }
                n++;
            }
        }

        percentageCharted += (1/pathsInt)*100;
        std::cout << percentageCharted << "%\n";
        t++;
    }

    percentageCharted = 0;

    printf("Stage 2:\n"); /// Gather all the futures!
    for(auto &i : path)
    {
        townPaths.push_back(i.get());
        percentageCharted += 100/(towns.size()*towns.size()-towns.size());
        std::cout << percentageCharted << "%\n";
    }


    printf("Stage 3:\n"); /// Copy and reverse 1st half of paths to get 2nd half
    t = 0;
    percentageCharted = 0;
    for(auto &town1 : towns)
    {
        int p = 0;

        for(auto &town2 : towns)
        {
            if(p<=t)
            {
                for(auto &path : townPaths)
                {
                    if(path.size() > 0)
                    {
                        if(path.back()->index == town1.tile->index && path.front()->index == town2.tile->index)
                        {
                            std::vector<hexagon*> l = path;
                            std::reverse(l.begin(), l.end());
                            townPaths.push_back(l);
                            break;
                        }
                    }
                }
            }
            p++;
        }
        percentageCharted += 200/(towns.size()*towns.size()-towns.size());
        printf("%f\%\n", percentageCharted);
        t++;
    }

    return townPaths;
}
