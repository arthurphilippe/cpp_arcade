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
	#include "Sprite.hpp"
	#include "IDisplay.hpp"

namespace arc {
	class CacaDisplay;
}

class arc::CacaDisplay : public IDisplay {
public:
	CacaDisplay();
	~CacaDisplay() noexcept override;

	void clear();
	void refresh();
	void putstr(const std::string &, int x = 0, int y = 0);
	void putItem(const Item &);
	void waitEvent();
	void putItem(const Item &item, int x ,int y);
	void putSpritePosition(
		const Item &item, const std::vector<struct Position> &poslist);

	caca_color getItemColor(const Sprite &sprite);
	InteractionList getInteractions();

	using KeyMap = std::unordered_map<int, Interaction>;
	using ColorMap = std::unordered_map<Color, caca_color>;
private:
	caca_display_t	*_dp;
	caca_canvas_t	*_cv;
	caca_event_t	_ev;
};

#endif /* !CACA_HPP_ */
