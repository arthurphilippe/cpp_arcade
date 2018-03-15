/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by xelax,
*/

#include <dirent.h>
#include <iostream>
#include "Startup.hpp"

Startup::Startup()
{
	setGfxLibs();
	setGameLibs();
}

Startup::~Startup()
{
}

std::vector<std::string> Startup::getGfxLibs() const
{
	return (this->gfxLibs);
}

std::vector<std::string> Startup::getGameLibs() const
{
	return (this->gameLibs);
}

void Startup::setGfxLibs(std::string path)
{
	DIR *gfxDir = opendir(path.c_str());
	struct dirent *entry = NULL;

	if (gfxDir == NULL)
		throw std::exception();
	while ((entry = readdir(gfxDir)) != NULL) {
		if (entry->d_type != DT_DIR)
			this->gfxLibs.push_back((std::string)entry->d_name);
	}
	closedir(gfxDir);
}

void Startup::setGameLibs(std::string path)
{
	DIR *gameDir = opendir(path.c_str());
	struct dirent *entry = NULL;

	if (gameDir == NULL)
		throw std::exception();
	while ((entry = readdir(gameDir)) != NULL) {
		if (entry->d_type != DT_DIR)
			this->gameLibs.push_back((std::string)entry->d_name);
	}
	closedir(gameDir);
}

void Startup::dumpLibs() const
{
	unsigned int iterator = 0;

	std::cout << "Gfx Libraries: " << this->gfxLibs.size() << std::endl;
	for (iterator = 0; iterator < this->gfxLibs.size() ; iterator++) {
		std::cout << iterator <<'\t' << this->gfxLibs[iterator] << std::endl;
	}
	std::cout << "Game Libraries: " << this->gameLibs.size() <<std::endl;
	for (iterator = 0; iterator < this->gameLibs.size() ; iterator++) {
		std::cout << iterator << '\t' << this->gameLibs[iterator] << std::endl;
	}
}