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
	Startup(const std::string &gamepath = "./games/", const std::string &gfxpath = "./lib/");
	~Startup();
	void dumpLibs() const;
	void startGame();
	std::vector<std::string> getGfxLibs() const;
	std::vector<std::string> getGameLibs() const;
	const std::string &getUserName() const noexcept {return _username;}
private:
	void setGfxLibs(const std::string &path = "./lib/");
	void setGameLibs(const std::string &path = "./games/");
	bool checkExtension(char *path);
	void askUserName();
	std::vector<std::string> _gfxLibs;
	std::vector<std::string> _gameLibs;
	std::string _username;
};

#endif /* STARTUP_H_ */
