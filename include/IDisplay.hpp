/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** IDisplay
*/

#ifndef IDISPLAY_HPP_
	#define IDISPLAY_HPP_

	#include <string>
	#include <queue>
	#include "Arc.hpp"
	#include "IGame.hpp"

namespace arc {
	class IDisplay;
}

class arc::IDisplay {
public:
	virtual ~IDisplay() = default;
	virtual void clear() = 0;
	virtual void putstr(const std::string &, int x = 0, int y = 0) = 0;
	virtual void putItem(const Item &);
	virtual void waitEvent() = 0;
	virtual void refresh() = 0;
	virtual InteractionList getInteractions() = 0;
};

#endif /* !IDISPLAY_HPP_ */
