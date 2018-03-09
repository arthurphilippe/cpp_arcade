/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** IGame
*/

#ifndef IGAME_HPP_
	#define IGAME_HPP_

	#include <vector>
	#include "Sprite.hpp"
	#include "SpriteParser.hpp"


namespace arc {
	class IGame;
}

class arc::IGame {
public:
	struct GridSize {
		int x;
		int y;
		int pixelStep;
	};

	struct Item {
		std::string	name;
		std::string	spritesPath;
		SpriteList	sprites;
		int		x;
		int		y;
	};
	using ItemList = std::vector<IGame::Item>;

	virtual ~IGame() = default;
	virtual void dump() const noexcept = 0;
	virtual ItemList &getItems() noexcept = 0;
	virtual const GridSize &getGridSize() const noexcept = 0;
};


#endif /* !IGAME_HPP_ */
