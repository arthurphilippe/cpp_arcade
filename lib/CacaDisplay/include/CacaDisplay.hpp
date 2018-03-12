/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** CacaDisplay
*/

#ifndef CACA_HPP_
	#define CACA_HPP_

	#include <caca.h>
	#include <unordered_map>
	#include "IDisplay.hpp"

namespace arc {
	class CacaDisplay;
}

class arc::CacaDisplay : public IDisplay {
public:
	CacaDisplay();
	~CacaDisplay() override;

	void clear();
	void refresh();
	void putstr(const std::string &, int x = 0, int y = 0);
	void waitEvent();
	InteractionList getInteractions();

	using KeyMap = std::unordered_map<int, Interaction>;
private:
	caca_display_t	*_dp;
	caca_canvas_t	*_cv;
	caca_event_t	_ev;
};

#endif /* !CACA_HPP_ */
