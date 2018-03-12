//
// EPITECH PROJECT, 2018
// Arcade
// File description:
// SfmlDisplay
//

#include <iostream>
#include "GfxException.hpp"
#include "SfmlDisplay.hpp"

static const arc::SfmlDisplay::KeyMap KEYMAP = {
	{sf::Keyboard::Z, arc::SfmlDisplay::MOVE_UP},
	{sf::Keyboard::Q, arc::SfmlDisplay::MOVE_LEFT},
	{sf::Keyboard::S, arc::SfmlDisplay::MOVE_DOWN},
	{sf::Keyboard::D, arc::SfmlDisplay::MOVE_RIGHT},
	{sf::Keyboard::PageUp, arc::SfmlDisplay::GAME_NEXT},
	{sf::Keyboard::PageDown, arc::SfmlDisplay::GAME_PREV},
	{sf::Keyboard::P, arc::SfmlDisplay::LIB_NEXT,},
	{sf::Keyboard::O, arc::SfmlDisplay::LIB_PREV},
	{sf::Keyboard::Escape, arc::SfmlDisplay::QUIT},
};


arc::SfmlDisplay::SfmlDisplay(int x, int y, const std::string &name)
{
	_window.create(sf::VideoMode(x,y), name);
	if (!_font.loadFromFile(FONT_PATH))
		throw GfxException(GFX_ERR_INIT);
}

arc::SfmlDisplay::~SfmlDisplay()
{
}

void arc::SfmlDisplay::refresh()
{
	_window.display();
}

void arc::SfmlDisplay::putstr(const std::string &str, int x, int y)
{
	sf::Text text;

	text.setFont(_font);
	text.setString(str);
	text.setCharacterSize(TEXT_SIZE);
	text.setFillColor(sf::Color::White);
	text.setPosition(x, y);
	_window.draw(text);
}

void arc::SfmlDisplay::clear()
{
	_window.clear();
}

void arc::SfmlDisplay::waitEvent()
{
	sf::Event event;
	while (_window.isOpen()) {
		while (_window.pollEvent(event)) {
			if (event.type == sf::Event::Closed
				|| sf::Keyboard::isKeyPressed(
					sf::Keyboard::Escape))
				_window.close();
		}
	}
}

arc::IDisplay::InteractionList arc::SfmlDisplay::getInteractions()
{
	InteractionList input;
 
	for (auto i = KEYMAP.begin(); i != KEYMAP.end(); i++) {
		if (sf::Keyboard::isKeyPressed(i->first)) {
			std::cout << i->second << std::endl;
			input.push(i->second);
		}
	}
	return input;
}
