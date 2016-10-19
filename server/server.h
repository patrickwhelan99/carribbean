#ifndef SERVER_H_INCLUDED
#define SERVER_H_INCLUDED

#include <string>
#include <iostream>
#include <SFML/Network.hpp>
#include <fstream>

#include <random>

#include "../custom.h"


std::vector<world> loadWorlds();
int pageUpdate(sf::TcpSocket *client, std::vector<world> &worlds);

#endif
