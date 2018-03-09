/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Pacman
*/

#ifndef DEFAULTGAME_HPP_
	#define DEFAULTGAME_HPP_

	#include <string>
	#include "IGame.hpp"

namespace arc {
	class Pacman;
	constexpr auto GRID_H = 42;
	constexpr auto GRID_L = 42;
	constexpr auto GRID_STEP = 12;
}

class arc::Pacman : public arc::IGame {
public:
	Pacman();
	~Pacman() {};
	void dump() const noexcept override;
	const GridSize &getGridSize() const noexcept;
private:
	std::string	_name;
	ItemList	_items;
	GridSize	_gridSize;

	void _dumpItems() const noexcept;
	void _setDefault() noexcept;
	static ItemList defaultItems;
};

#endif /* !DEFAULTGAME_HPP_ */
