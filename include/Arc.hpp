/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Arc
*/

#ifndef ARC_HPP_
	#define ARC_HPP_

	#include <queue>
	#include <unordered_map>

namespace arc {
	enum Color {
		BLUE,
		RED,
		GREEN,
		YELLOW,
		CYAN,
		MAGENTA,
		WHITE,
		BLACK,
		UNDEFINED,
		DFT_COLOR_RET_ERROR,
	};
	enum Attribute {
		PLAYER,
		BLOCK,
		FOE,
		MOVE,
		DROP,
		UNK,
	};
	struct Sprite {
		int x;
		int y;
		int rotation;
		char substitute;
		std::string name;
		std::string path;
		arc::Color color;
	};
	using SpriteList = std::vector<Sprite>;

	struct Item {
		std::string	name;
		std::string	spritesPath;
		SpriteList	sprites;
		arc::Attribute	attribute;
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

	struct Vectori {
		int v_x;
		int v_y;
	};

	struct Position
	{
		int x;
		int y;
		Interaction interact;
	};

	const std::unordered_map<Interaction, Vectori> MOVE_BINDS {
		{MOVE_UP, {0, -1}},
		{MOVE_DOWN, {0, 1}},
		{MOVE_LEFT, {-1, 0}},
		{MOVE_RIGHT, {1, 0}}
	};
}

#endif /* !ARC_HPP_ */
