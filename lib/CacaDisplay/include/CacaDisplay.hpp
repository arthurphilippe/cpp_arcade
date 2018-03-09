/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** CacaDisplay
*/

#ifndef CACA_HPP_
	#define CACA_HPP_

	#include <caca.h>
	#include "IDisplay.hpp"

namespace arc {
	class CacaDisplay;
}

class arc::CacaDisplay : public IDisplay {
public:
	CacaDisplay();
	~CacaDisplay();

	void clear();
	void refresh();
	void putstr(const std::string &, int x = 0, int y = 0);
	void waitEvent();
private:
	caca_display_t	*_dp;
	caca_canvas_t	*_cv;
	caca_event_t	_ev;
};

#endif /* !CACA_HPP_ */
