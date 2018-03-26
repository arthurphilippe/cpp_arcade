/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** CacaDisplay
*/

#include <iostream>
#include "Arc.hpp"
#include "CacaDisplay.hpp"
#include "GfxException.hpp"

static const arc::CacaDisplay::KeyMap KEYMAP = {
	{'z', arc::MOVE_UP},
	{'q', arc::MOVE_LEFT},
	{'s', arc::MOVE_DOWN},
	{'d', arc::MOVE_RIGHT},
	{CACA_KEY_PAGEUP, arc::GAME_NEXT},
	{CACA_KEY_PAGEDOWN, arc::GAME_PREV},
	{'p', arc::LIB_NEXT},
	{'o', arc::LIB_PREV},
	{CACA_KEY_ESCAPE, arc::QUIT},
	{' ', arc::ACTION_1}
};

static const arc::CacaDisplay::ColorMap _map = {
	{arc::BLUE, CACA_BLUE},
	{arc::RED, CACA_RED},
	{arc::GREEN, CACA_GREEN},
	{arc::YELLOW, CACA_YELLOW},
	{arc::CYAN, CACA_CYAN},
	{arc::MAGENTA, CACA_MAGENTA},
	{arc::WHITE, CACA_WHITE},
	{arc::BLACK, CACA_BLACK},
	{arc::UNDEFINED, CACA_DEFAULT}
};

arc::CacaDisplay::CacaDisplay()
	: _dp(caca_create_display(NULL)), _step(1)
{
	if (!_dp)
		throw GfxException(GFX_ERR_INIT);
	_cv = caca_get_canvas(_dp);
	caca_set_display_title(_dp, "Arcade");
}

arc::CacaDisplay::~CacaDisplay()
{
	caca_free_display(_dp);
}

void arc::CacaDisplay::clear()
{
	caca_clear_canvas(_cv);
	caca_set_color_ansi(_cv, CACA_WHITE, CACA_BLACK);
}

void arc::CacaDisplay::refresh()
{
	caca_refresh_display(_dp);
}

void arc::CacaDisplay::setStep(uint step)
{
	_step = step;
}

void arc::CacaDisplay::putstr(const std::string &str, int x, int y)
{
	caca_put_str(_cv, x, y, str.c_str());
}

caca_color arc::CacaDisplay::getItemColor(const Sprite &sprite)
{
	for (auto i = _map.begin(); i != _map.end(); i++) {
		if (i->first == sprite.getColor())
			return (i->second);
	}
	return CACA_DEFAULT;
}

void arc::CacaDisplay::putItem(const Item &item)
{
	auto &currSprite = item.sprites[item.currSpriteIdx];

	if (currSprite.getSubstitute()) {
		caca_set_color_ansi(_cv, getItemColor(currSprite), CACA_BLACK);
		caca_put_char(_cv, item.x / _step, item.y / _step,
				currSprite.getSubstitute());
	}
	else
		caca_put_char(_cv, item.x / _step, item.y / _step, '?');
}

void arc::CacaDisplay::putItem(const Item &item, int x ,int y)
{
	auto &currSprite = item.sprites[item.currSpriteIdx];

	if (currSprite.getSubstitute()) {
		caca_set_color_ansi(_cv, getItemColor(currSprite), CACA_BLACK);
		caca_put_char(_cv, x / _step, y / _step,
				currSprite.getSubstitute());
	}
	else
		caca_put_char(_cv, x / _step, y / _step, '?');
}

void arc::CacaDisplay::putSpritePosition(
	const Item &item, const std::vector<struct Position> &poslist)
{
	for (auto i  = poslist.begin(); i != poslist.end(); i++) {
		putItem(item, i->x, i->y);
	}
}


void arc::CacaDisplay::waitEvent()
{
	caca_get_event(_dp, CACA_EVENT_KEY_PRESS, &_ev, -1);
}

arc::InteractionList arc::CacaDisplay::getInteractions()
{
	InteractionList input;

	while (caca_get_event(_dp, CACA_EVENT_KEY_PRESS, &_ev, 50)) {
		if (KEYMAP.find(_ev.data.key.ch) != KEYMAP.end())
			input.push(KEYMAP.find(_ev.data.key.ch)->second);
	}
	return input;
}
