/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by xelax,
*/

#ifndef NCURSESDISPLAY_HPP_
	#define NCURSESDISPLAY_HPP_

	#include <ncurses.h>
	#include "IDisplay.hpp"

#define COLOR_ERROR -1
#define NO_EVENT -1

namespace arc {
	class NCursesDisplay;
}

class arc::NCursesDisplay : public IDisplay {
public:
	NCursesDisplay();
	~NCursesDisplay();
	void clear();
	void putstr(const std::string &, int x = 0, int y = 0);
	void putItem(const Item &item);
	void waitEvent();
	void refresh();
	void setStep(uint step);
	InteractionList getInteractions();

	using KeyMap = std::unordered_map<int, Interaction>;
	using ColorMap = std::unordered_map<Color, NCURSES_COLOR_T>;
private:
	short getPairColor(arc::Color color);
	WINDOW *_window;
	uint _step;
	int _pendingEvent;
};

#endif /* !NCURSESDISPLAY_HPP_ */
