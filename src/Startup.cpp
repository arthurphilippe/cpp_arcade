/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by xelax,
*/

#include <dirent.h>
#include <iostream>
#include "Scores.hpp"
#include "Error.hpp"
#include "Startup.hpp"

arc::Startup::Startup(int ac, char **av,
			const std::string &gamepath, const std::string &gfxpath)
	: _ac(ac),
	_av(av),
	_valid(true)
{
	_parseArguments();
	if (_valid) {
		setLibs(gfxpath, _gfxLibs);
		setLibs(gamepath, _gameLibs);
		startGame();
	}
}

arc::Startup::~Startup()
{}

void arc::Startup::_parseArguments()
{
	if (_ac != 2) {
		_valid = false;
	} else {
		_gfxLibs.insert(_gfxLibs.begin(), _av[1]);
		_startupLib = _av[1];
		_startupLib = _startupLib.substr(
			_startupLib.find_last_of('_') + 1 , _startupLib.length());
		std::cout << _startupLib << std::endl;
	}
}

void arc::Startup::askUserName()
{
	char username[255];

	std::cout << "What's your name ?" << std::endl << "name: ";
	std::cin.getline(username, 255);
	_username = username;
}

void arc::Startup::_displayScores() const noexcept
{
	for (auto it = _gameLibs.begin(); it != _gameLibs.end(); it++) {
		Scores currScores(*it);

		std::cout << "In " << *it << " the best player is ";
		std::cout << currScores.getBestPlayer() << " with a score of ";
		std::cout << currScores.getHighscore() << std::endl;
	}
}

void arc::Startup::startGame()
{
	std::cout << "Welcome to arcade!" << std::endl << std::endl;
	dumpLibs();
	_displayScores();
	askUserName();
}

arc::libArray arc::Startup::getGfxLibs() const
{
	return _gfxLibs;
}

arc::libArray arc::Startup::getGameLibs() const
{
	return _gameLibs;
}

bool arc::Startup::_checkGfxLib(std::string infolder)
{
	infolder = infolder.substr(3, infolder.length());
	if (infolder == _startupLib) {
		_gfxLibs.erase(_gfxLibs.begin());
	}
	return true;
}

void arc::Startup::setLibs(const std::string &path, libArray &list)
{
	DIR *gameDir = opendir(path.c_str());
	struct dirent *entry = NULL;
	std::string filePath = path;

	if (gameDir == NULL)
		throw arc::StartupError(ERR_GAME_PATH + path);
	while ((entry = readdir(gameDir)) != NULL) {
		if (entry->d_type == DT_DIR && entry->d_name[0] != '.')
			setLibs(path + entry->d_name + "/", list);
		else if (entry->d_type != DT_DIR
				&& checkExtension(entry->d_name)
				&& _checkGfxLib(entry->d_name))
			list.push_back(path + entry->d_name);
	}
	free(entry);
	closedir(gameDir);
}

void arc::Startup::dumpLibs() const
{
	std::cout << "Display Libraries found:" << std::endl;
	for (auto i = _gfxLibs.begin(); i != _gfxLibs.end(); i++) {
		std::cout << '\t' << *i << std::endl;
	}
	std::cout << "Game Libraries found:" << std::endl;
		for (auto i = _gameLibs.begin(); i != _gameLibs.end(); i++) {
		std::cout << '\t' << *i << std::endl;
	}
}

bool arc::Startup::checkExtension(char *filename)
{
	std::string extension(filename);

	if (extension.length() > 4)
		extension = extension.substr(extension.length() - 3, 3);
	if (extension == ".so")
		return (true);
	return (false);
}
