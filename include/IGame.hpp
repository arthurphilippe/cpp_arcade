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

	virtual ~IGame() = default;
	virtual void dump() const noexcept = 0;
};

namespace arc {
	using ItemList = std::vector<IGame::Item>;
}

#endif /* !IGAME_HPP_ */
