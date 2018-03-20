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
	using libArray = std::vector<std::string>;
}

class arc::Startup {
public:
	Startup(const std::string &gamepath = "./games/", const std::string &gfxpath = "./lib/");
	~Startup();
	void startGame();
	libArray getGfxLibs() const;
	libArray getGameLibs() const;
	const std::string &getUserName() const noexcept {return _username;}
private:
	void setLibs(const std::string &path, libArray &list);
	void dumpScores();
	void dumpLibs() const;
	bool checkExtension(char *filename);
	void askUserName();
	libArray _gfxLibs;
	libArray _gameLibs;
	std::string _username;
};

#endif /* STARTUP_H_ */
