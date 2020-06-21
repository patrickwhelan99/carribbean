#ifndef NETWORKING_H_INCLUDED
#define NETWORKING_H_INCLUDED



#ifdef __GNUC__
#ifdef __linux__

#include <glob.h>

inline std::string genImageName()
{
	glob_t globby;
	size_t cnt = 0;
	if(glob("./*.png", GLOB_NOSORT, NULL, &globby) == 0)
		cnt = globby.gl_pathc;
	globfree(&globby);
	std::cout << "Number of files: " << cnt << std::endl;
	return std::string("image_") + std::to_string(static_cast<int>(cnt));
};
#endif
#endif

#ifdef __MINGW32__

inline std::string genImageName()
{
	int a = rand() % 9999999 + 0;
	return std::string("image_") + std::to_string(a);
};
#endif // __MINGW32__

class world
{
	public:
		uint32_t seed;
		std::string name;
		std::string imageName;
		int32_t worldSize;

		world(uint32_t seed=0, int32_t worldSize=0, std::string name="", std::string imageName="")
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
