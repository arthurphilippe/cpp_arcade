/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** CacaDisplay
*/

#include "CacaDisplay.hpp"
#include "GfxException.hpp"

arc::CacaDisplay::CacaDisplay()
{
	_dp = caca_create_display(NULL);
	if (!_dp)
		throw GfxException(GFX_ERR_INIT);
	_cv = caca_get_canvas(_dp);
	caca_set_display_title(_dp, "Arcade");
	caca_set_color_ansi(_cv, CACA_BLACK, CACA_WHITE);
	caca_put_str(_cv, 0, 0, "Welcome to arcade!");
	caca_refresh_display(_dp);
}

arc::CacaDisplay::~CacaDisplay()
{
	caca_get_event(_dp, CACA_EVENT_KEY_PRESS, &_ev, -1);
	caca_free_display(_dp);
}

void arc::CacaDisplay::clear()
{
	caca_clear_canvas(_cv);
}

void arc::CacaDisplay::display()
{
	caca_refresh_display(_dp);
}

void arc::CacaDisplay::waitEvent()
{
	caca_get_event(_dp, CACA_EVENT_KEY_PRESS, &_ev, -1);
}

void arc::CacaDisplay::putstr(const std::string &str, int x, int y)
{
	caca_put_str(_cv, x, y, str.c_str());
}
