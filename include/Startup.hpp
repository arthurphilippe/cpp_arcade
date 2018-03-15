/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by xelax,
*/
#ifndef STARTUP_H_
	#define STARTUP_H_

	#include <vector>
	#include <string>

namespace arc {
	class Startup;
}

class Startup {
public:
	Startup();
	~Startup();
	std::vector<std::string> getGfxLibs() const;
	std::vector<std::string> getGameLibs() const;
	void dumpLibs() const;
private:
	void setGfxLibs(std::string path = "./lib/");
	void setGameLibs(std::string path = "./games/");
	std::vector<std::string> gfxLibs;
	std::vector<std::string> gameLibs;
};

#endif /* STARTUP_H_ */
