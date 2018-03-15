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
	constexpr auto FPS = 56;
}

class arc::Pacman : public arc::IGame {
public:
	Pacman();
	~Pacman() {};
	void dump() const noexcept override;
	ItemList &getItems() noexcept override
	{
		return _items;
	}
	const Specs &getSpecs() const noexcept override
	{
		return _info;
	}
	void proccessIteraction(Interaction &) noexcept;
	void envUpdate() noexcept;
private:
	std::string	_name;
	ItemList	_items;
	Specs		_info;

	static ItemList defaultItems;

	void _dumpItems() const noexcept;
};

#endif /* !DEFAULTGAME_HPP_ */
