/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** CacaDisplay
*/

#include "CacaDisplay.hpp"
#include "GfxException.hpp"

static const arc::CacaDisplay::KeyMap KEYMAP = {
	{'z', arc::CacaDisplay::MOVE_UP},
	{'q', arc::CacaDisplay::MOVE_LEFT},
	{'s', arc::CacaDisplay::MOVE_DOWN},
	{'d', arc::CacaDisplay::MOVE_RIGHT},
	{CACA_KEY_PAGEUP, arc::CacaDisplay::GAME_NEXT},
	{CACA_KEY_PAGEDOWN, arc::CacaDisplay::GAME_PREV},
	{'p', arc::CacaDisplay::LIB_NEXT,},
	{'o', arc::CacaDisplay::LIB_PREV},
};

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
	caca_free_display(_dp);
}

void arc::CacaDisplay::clear()
{
	caca_clear_canvas(_cv);
	caca_set_color_ansi(_cv, CACA_BLACK, CACA_WHITE);
}

void arc::CacaDisplay::refresh()
{
	caca_refresh_display(_dp);
}

void arc::CacaDisplay::putstr(const std::string &str, int x, int y)
{
	caca_put_str(_cv, x, y, str.c_str());
}

void arc::CacaDisplay::waitEvent()
{
	caca_get_event(_dp, CACA_EVENT_KEY_PRESS, &_ev, -1);
}

arc::IDisplay::InteractionList arc::CacaDisplay::getInteractions()
{
	InteractionList input;
	while (auto key = caca_get_event(_dp, CACA_EVENT_KEY_PRESS, &_ev, 0)) {
		if (KEYMAP.find(key) != KEYMAP.end())
			input.push(KEYMAP.find(key)->second);
	}
	return input;
}
