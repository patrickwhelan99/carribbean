#include "../include/custom.h"
#include <future>
#include <iostream>
#include <cmath>

#ifdef __linux__
std::vector<std::vector<hexagon*> > initPathGen(std::vector<hexagon*> towns, std::vector<hexagon> hexs, int gridSize, std::vector<int> &edgeTiles, unsigned threads, double* percentageCharted)
{
    int pathsInt = static_cast<int>(towns.size());
    printf("Generating %i Paths!\n.... could take a while\n...... go and get a drink? Go outside? Go and visit your grandma? Go on holiday?\n", pathsInt*pathsInt - pathsInt);
    std::vector< std::vector<hexagon*> > townPaths;
    std::vector<std::future< std::vector<hexagon*> > > path;
    pathParameters ppArray[static_cast<int>(towns.size()*towns.size()-towns.size())];
    int n = 0;
    int t = 0;

    //printf("Stage 1/3:\n"); /// Generate Half of the paths
    for(auto &town1 : towns)
    {
        n=0;
        for(auto &town2 : towns)
        {
            if(town1 && town2)
            {
                if(n<t)
                {
                    ///Do nothing will replace with reversed path of one that has already been calculated after future has been resolved
                }

                else if(town1->index!=town2->index)
                {
                        hexagon* a = town1;
                        hexagon* b = town2;
                        pathParameters p(a, b, hexs, gridSize);
                        ppArray[n] = std::move(p);
                        path.push_back(std::async(std::launch::async, findPath, std::ref(ppArray[n])));
                }
                n++;
            }
        }

        *(percentageCharted) += ((float)1/pathsInt)*100;
        //std::cout << ceil(*(percentageCharted)) << "%\n";
        t++;
    }

    *(percentageCharted) = 0;

    //printf("Stage 2/3:\n"); /// Gather all the futures!
    for(auto &i : path)
    {
        townPaths.push_back(i.get());
        *(percentageCharted) += (float)100*((float)1/(float)path.size());
        //std::cout << ceil(*(percentageCharted)) << "%\n";
    }


    //printf("Stage 3/3:\n"); /// Copy and reverse 1st half of paths to get 2nd half
    t = 0;
    *(percentageCharted) = 0;
    for(auto &town1 : towns)
    {
        int p = 0;

        for(auto &town2 : towns)
        {
            if(p<=t)
            {
                for(auto &path : townPaths)
                {
                    if(static_cast<int>(path.size()) > 0)
                    {
                        if(path.front() != path.back() && path.back()->index == town1->index && path.front()->index == town2->index)
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
        *(percentageCharted) += (float)100/(float)(pathsInt);
        //printf("%f\%\n", ceil(*(percentageCharted)));
        t++;
    }

    return townPaths;
}
#endif

#ifdef __MINGW32__
std::vector<std::vector<hexagon*> > initPathGen(std::vector<hexagon*> towns, std::vector<hexagon> hexs, int gridSize, std::vector<int> &edgeTiles, unsigned threads, double* percentageCharted)
{
    int pathsInt = static_cast<int>(towns.size());
    printf("Generating %i Paths!\n.... could take a while\n...... go and get a drink? Go outside? Go and visit your grandma? Go on holiday?\n", pathsInt*pathsInt - pathsInt);
    std::vector< std::vector<hexagon*> > townPaths;
    std::vector<std::future< std::vector<hexagon*> > > path;
    pathParameters ppArray[static_cast<int>(towns.size()*towns.size()-towns.size())];

    //printf("Stage 1/3:\n"); /// Generate Half of the paths
    for(auto &town1 : towns)
    {
        for(auto &town2 : towns)
        {
            if(town1 && town2)
            {
                if(town1->index!=town2->index)
                {
                        hexagon* a = town1;
                        hexagon* b = town2;
                        pathParameters p(a, b, hexs, gridSize);
                        findPath(p);
                }
            }
        }

        *(percentageCharted) += ((float)1/pathsInt)*100;
        std::cout << ceil(*(percentageCharted)) << "%\n";
    }

    return townPaths;
}
#endif
