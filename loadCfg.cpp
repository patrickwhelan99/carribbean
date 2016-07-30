#include "custom.h"
#include <iostream>
#include <fstream>

cfgClass loadCfg(void)
{
        printf("Loading Config...\n");

    cfgClass config;

    std::ifstream cfg;
    textureCfg.open("cfg.txt");
    std::string line;

    if (cfg.is_open())
    {
            while ( std::getline (cfg,line) )
            {

	    }
    }
