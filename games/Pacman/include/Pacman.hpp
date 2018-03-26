/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Pacman
*/

#ifndef PACMAN_HPP_
	#define PACMAN_HPP_

	#include <string>
	#include "Arc.hpp"
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
	ItemList &getItemsFromName(const std::string &name);
	void proccessIteraction(Interaction &) noexcept;
	void envUpdate() noexcept;
	arc::Item &getItemFromName(const std::string &name);
	void putSpritePosition(const Item &item, const std::vector<struct Position> &poslist);
	SpriteList &getSpriteListFromName(const std::string &name) {
		(void) name;
		return _items[0].sprites;
	}
	const std::vector<struct Position> &getBulletPos() {return _bulletPos;}
private:
	std::string	_name;
	ItemList	_items;
	ItemList	_todraw;
	Specs		_info;
	std::vector<struct Position> _bulletPos;

	static ItemList defaultItems;

	void _dumpItems() const noexcept;
};

#endif /* !PACMAN_HPP_ */
