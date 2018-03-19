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
	std::string filePath = path;

	if (gfxDir == NULL)
		throw std::exception();
	while ((entry = readdir(gfxDir)) != NULL) {
		if (entry->d_type != DT_DIR &&
			this->checkExtension(entry->d_name)) {
			filePath += (std::string)entry->d_name;
			this->gfxLibs.push_back(filePath);
			filePath = path;
		}
	}
	free(entry);
	closedir(gfxDir);
}

void Startup::setGameLibs(std::string path)
{
	DIR *gameDir = opendir(path.c_str());
	struct dirent *entry = NULL;
	std::string filePath = path;

	if (gameDir == NULL)
		throw std::exception();
	while ((entry = readdir(gameDir)) != NULL) {
		if (entry->d_type != DT_DIR &&
			this->checkExtension(entry->d_name)) {
			filePath += (std::string)entry->d_name;
			this->gameLibs.push_back(filePath);
			filePath = path;
		}
	}
	free(entry);
	closedir(gameDir);
}

void Startup::dumpLibs() const
{
	unsigned int iterator = 0;

	std::cout << "Gfx Libraries Path:" << std::endl;
	for (iterator = 0; iterator < this->gfxLibs.size() ; iterator++) {
		std::cout <<'\t' << this->gfxLibs[iterator] << std::endl;
	}
	std::cout << "Game Libraries Path:" << std::endl;
	for (iterator = 0; iterator < this->gameLibs.size() ; iterator++) {
		std::cout << '\t' << this->gameLibs[iterator] << std::endl;
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
