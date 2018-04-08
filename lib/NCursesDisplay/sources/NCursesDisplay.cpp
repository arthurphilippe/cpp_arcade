/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by xelax,
*/

#include <ncurses.h>
#include <linux/input-event-codes.h>
#include "NCursesDisplay.hpp"
#include "GfxException.hpp"

static const arc::NCursesDisplay::KeyMap KEYMAP = {
	{'z', arc::MOVE_UP},
	{'q', arc::MOVE_LEFT},
	{'s', arc::MOVE_DOWN},
	{'d', arc::MOVE_RIGHT},
	{KEY_PPAGE, arc::GAME_NEXT},
	{KEY_NPAGE, arc::GAME_PREV},
	{'p', arc::LIB_NEXT},
	{'o', arc::LIB_PREV},
	{27, arc::QUIT},
	{' ', arc::ACTION_1}
};

static const arc::NCursesDisplay::ColorMap _colors = {
	{arc::BLUE, COLOR_BLUE},
	{arc::RED, COLOR_RED},
	{arc::GREEN, COLOR_GREEN},
	{arc::YELLOW, COLOR_YELLOW},
	{arc::CYAN, COLOR_CYAN},
	{arc::MAGENTA, COLOR_MAGENTA},
	{arc::WHITE, COLOR_WHITE},
	{arc::BLACK, COLOR_BLACK},
	{arc::UNDEFINED, COLOR_ERROR}
};

arc::NCursesDisplay::NCursesDisplay()
{
	_window = initscr();
	if (_window == NULL)
		throw GfxException(GFX_ERR_INIT);
	raw();
	noecho();
	curs_set(0);
	keypad(_window, true);
	start_color();
	_step = 1;
	_pendingEvent = NO_EVENT;
}

arc::NCursesDisplay::~NCursesDisplay()
{
	endwin();
}

void arc::NCursesDisplay::clear()
{
	wclear(_window);
}

void arc::NCursesDisplay::putstr(const std::string &str, int x, int y)
{
	mvwprintw(_window, x, y, "%s", str);
}

short arc::NCursesDisplay::getPairColor(arc::Color color)
{
	for (auto i = _colors.begin(); i != _colors.end(); i++) {
		if (i->first == color)
			return (i->second);
	}
	return (COLOR_ERROR);
}

void arc::NCursesDisplay::putItem(const arc::Item &item)
{
	auto &currSprite = item.sprites[item.currSpriteIdx];
	short pairColor = COLOR_ERROR;

	if (currSprite.substitute) {
		pairColor = getPairColor(currSprite.color);
		init_pair(pairColor, pairColor, COLOR_BLACK);
		attron(COLOR_PAIR(pairColor));
		mvwprintw(_window, item.y / _step, item.x / _step, "%c", currSprite.substitute);
		attroff(COLOR_PAIR(pairColor));
	} else {
		mvwprintw(_window, item.y / _step, item.x / _step, "?");
	}
}

void arc::NCursesDisplay::waitEvent()
{
	wtimeout(_window, -1);
	_pendingEvent = wgetch(_window);
}

void arc::NCursesDisplay::refresh()
{
	wrefresh(_window);
}

void arc::NCursesDisplay::setStep(uint step)
{
	_step = step;
}

arc::InteractionList arc::NCursesDisplay::getInteractions()
{
	InteractionList input;

	wtimeout(_window, 0);
	_pendingEvent = wgetch(_window);
	if (KEYMAP.find(_pendingEvent) != KEYMAP.end())
		input.push(KEYMAP.find(_pendingEvent)->second);
	return (input);
}
