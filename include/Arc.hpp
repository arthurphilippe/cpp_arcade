/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Arc
*/

#ifndef ARC_HPP_
	#define ARC_HPP_

	#include <queue>
	#include "Sprite.hpp"

namespace arc {
	struct Item {
		std::string	name;
		std::string	spritesPath;
		SpriteList	sprites;
		int		currSpriteIdx;
		int		x;
		int		y;
	};
	using ItemList = std::vector<Item>;

	enum Interaction {
		MOVE_UP,
		MOVE_DOWN,
		MOVE_LEFT,
		MOVE_RIGHT,
		ACTION_1,
		LIB_NEXT,
		LIB_PREV,
		GAME_NEXT,
		GAME_PREV,
		QUIT,
	};
	using InteractionList = std::queue<Interaction>;
}

#endif /* !ARC_HPP_ */
