/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** IDisplay
*/

#ifndef IDisplay_HPP_
	#define IDisplay_HPP_

	#include <string>
	#include <queue>

namespace arc {
	class IDisplay;
}

class arc::IDisplay {
public:
	enum Interaction {
		MOVE_UP,
		MOVE_DOWN,
		MOVE_LEFT,
		MOVE_RIGHT,
		LIB_NEXT,
		LIB_PREV,
		GAME_NEXT,
		GAME_PREV,
		QUIT,
	};
	using InteractionList = std::queue<Interaction>;

	virtual ~IDisplay() = default;
	virtual void clear() = 0;
	virtual void putstr(const std::string &, int x = 0, int y = 0) = 0;
	virtual void waitEvent() = 0;
	virtual void refresh() = 0;
	virtual InteractionList getInteractions() = 0;
};

#endif /* !IDisplay_HPP_ */
