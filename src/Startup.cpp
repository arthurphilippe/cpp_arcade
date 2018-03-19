/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by xelax,
*/

#include <dirent.h>
#include <iostream>
#include "Startup.hpp"

Startup::Startup(const std::string &gamepath, const std::string &gfxpath)
{
	setGfxLibs(gfxpath);
	setGameLibs(gamepath);
}

Startup::~Startup()
{
}

void Startup::askUserName()
{
	char username[255];

	std::cout << "Please, enter your username: " << std::endl;
	std::cin.getline(username, 255);
	_username = username;
}

void Startup::startGame()
{
	dumpLibs();
	askUserName();
}

std::vector<std::string> Startup::getGfxLibs() const
{
	return (_gfxLibs);
}

std::vector<std::string> Startup::getGameLibs() const
{
	return (_gameLibs);
}

void Startup::setGfxLibs(const std::string &path)
{
	DIR *gfxDir = opendir(path.c_str());
	struct dirent *entry = NULL;
	std::string filePath = path;

	if (gfxDir == NULL)
		throw std::exception();
	while ((entry = readdir(gfxDir)) != NULL) {
		if (entry->d_type != DT_DIR &&
			checkExtension(entry->d_name)) {
			filePath += (std::string)entry->d_name;
			_gfxLibs.push_back(filePath);
			filePath = path;
		}
	}
	free(entry);
	closedir(gfxDir);
}

void Startup::setGameLibs(const std::string &path)
{
	DIR *gameDir = opendir(path.c_str());
	struct dirent *entry = NULL;
	std::string filePath = path;

	if (gameDir == NULL)
		throw std::exception();
	while ((entry = readdir(gameDir)) != NULL) {
		if (entry->d_type != DT_DIR &&
			checkExtension(entry->d_name)) {
			filePath += (std::string)entry->d_name;
			_gameLibs.push_back(filePath);
			filePath = path;
		}
	}
	free(entry);
	closedir(gameDir);
}

void Startup::dumpLibs() const
{
	std::cout << "Gfx Libraries Path:" << std::endl;
	for (auto i = _gfxLibs.begin(); i != _gfxLibs.end(); i++) {
		std::cout << '\t' << *i << std::endl;
	}
	std::cout << "Game Libraries Path:" << std::endl;
		for (auto i = _gameLibs.begin(); i != _gameLibs.end(); i++) {
		std::cout << '\t' << *i << std::endl;
	}
}

bool Startup::checkExtension(char *path)
{
	std::string extension(path);

	extension = extension.substr(extension.length() - 3, 3);
	if (extension == ".so")
		return (true);
	return (false);
}
