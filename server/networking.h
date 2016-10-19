#ifndef NETWORKING_H_INCLUDED
#define NETWORKING_H_INCLUDED



#include <glob.h>


std::string genImageName()
{
	glob_t globby;
	size_t count = 0;
	if(glob("./*.png", GLOB_NOSORT, NULL, &globby) == 0)
		count = globby.gl_pathc;
	globfree(&globby);
	cout << "Number of files: " << count << endl;
	return std::string("image_") + count.to_string;
}


/*
inline std::string genImageName()
{
	int a = rand() % 9999999 + 0;
	return std::string("image_") + std::to_string(a);
};
*/

class world
{
	public:
		uint32_t seed;
		std::string name;
		std::string imageName;
		int32_t worldSize;

		world(uint32_t seed, int32_t worldSize, std::string name="", std::string imageName="")
		{
			this->seed = seed;

			if(name.empty())
				this->name = "UNNAMED";
			else
				this->name = name;

			if(imageName.empty())
				this->imageName = genImageName();
			else
				this->imageName = imageName;

			this->worldSize = worldSize;
		}
};



/**********************************PACKETS***************************************************/


inline sf::Packet& operator <<(sf::Packet& packet, const world& w)
{
    return packet << w.seed << w.worldSize << w.name << w.imageName;
}

inline sf::Packet& operator >>(sf::Packet& packet, world& w)
{
     return packet >> w.seed >> w.worldSize >> w.name >> w.imageName;
}

#endif
