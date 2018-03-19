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

class arc::Startup {
public:
	Startup(const std::string &gamepath = "./games/", const std::string &gfxpath = "./lib/");
	~Startup();
	void startGame();
	std::vector<std::string> getGfxLibs() const;
	std::vector<std::string> getGameLibs() const;
	const std::string &getUserName() const noexcept {return _username;}
private:
	template<typename T>
	void setLibs(const std::string &path, T &list);
	void dumpScores();
	void dumpLibs() const;
	bool checkExtension(char *filename);
	void askUserName();
	std::vector<std::string> _gfxLibs;
	std::vector<std::string> _gameLibs;
	std::string _username;
};

#endif /* STARTUP_H_ */
