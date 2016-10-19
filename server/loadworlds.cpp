#include "server.h"
//#include "networkingClasses.h"

std::vector<world> loadWorlds()
{
	std::vector<world> worlds;
	std::ifstream worldsFile;
    worldsFile.open("worlds.txt");

    std::string line;

    if (worldsFile.is_open())
    {
            while ( std::getline (worldsFile,line) )
            {
				std::string token = line.substr(0, line.find(", "));
                line.erase(0, line.find(", ") + 2);
                uint32_t seed = std::atoi(token.c_str());

				token = line.substr(0, line.find(", "));
                line.erase(0, line.find(", ") + 2);
                int32_t worldSize = std::atoi(token.c_str());

				token = line.substr(0, line.find(", "));
                line.erase(0, line.find(", ") + 2);
                std::string name = token;

				token = line.substr(0, line.find("\n"));
                line.erase(0, line.find("\n"));
                std::string imageName = token;

				world newWorld(seed, worldSize, name, imageName);
				worlds.push_back(newWorld);
			}
	}
	return worlds;
}