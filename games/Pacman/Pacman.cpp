/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Pacman
*/

#include <iostream>
#include <algorithm>
#include "Pacman.hpp"

arc::Pacman::Item DEF_PACMAN = {"pacman", "", arc::SpriteList(), 20, 20};
arc::Pacman::Item DEF_GHOSTA = {"ghost a", "", arc::SpriteList(), 30, 30};
arc::Pacman::Item DEF_GHOSTB = {"ghost b", "", arc::SpriteList(), 40, 30};
arc::Pacman::Item DEF_GHOSTC = {"ghost c", "", arc::SpriteList(), 50, 30};
arc::Pacman::Item DEF_GHOSTD = {"ghost d", "", arc::SpriteList(), 60, 30};

arc::Pacman::Pacman()
	: _name("Pacman"), _gridSize({GRID_H, GRID_L, GRID_STEP})
{
	_items.push_back(DEF_PACMAN);
	_items.push_back(DEF_GHOSTA);
	_items.push_back(DEF_GHOSTB);
	_items.push_back(DEF_GHOSTC);
	_items.push_back(DEF_GHOSTD);
}

void arc::Pacman::dump() const noexcept
{
	std::cout << "Dumping game " << _name << "." << std::endl;
	std::cout << "Grid size: " << _gridSize.x << "*" << _gridSize.y;
	std::cout << "*" <<_gridSize.pixelStep << std::endl;
	_dumpItems();
}

void arc::Pacman::_dumpItems() const noexcept
{
	for (auto it = _items.begin(); it != _items.end(); ++it) {
		std::cout << "Item: " << it->name << " -- Sprite count:";
		std::cout << it->sprites.size() << " -- Pos: " << it->x;
		std::cout << ", " << it->y << std::endl;
	}
}

void arc::Pacman::_setDefault() noexcept
{
}
