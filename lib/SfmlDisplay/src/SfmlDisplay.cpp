//
// EPITECH PROJECT, 2018
// Arcade
// File description:
// SfmlDisplay
//

#include <iostream>
#include "Arc.hpp"
#include "GfxException.hpp"
#include "SfmlDisplay.hpp"

static const arc::SfmlDisplay::KeyMap KEYMAP = {
	{sf::Keyboard::Z, arc::MOVE_UP},
	{sf::Keyboard::Q, arc::MOVE_LEFT},
	{sf::Keyboard::S, arc::MOVE_DOWN},
	{sf::Keyboard::D, arc::MOVE_RIGHT},
	{sf::Keyboard::PageUp, arc::GAME_NEXT},
	{sf::Keyboard::PageDown, arc::GAME_PREV},
	{sf::Keyboard::P, arc::LIB_NEXT,},
	{sf::Keyboard::O, arc::LIB_PREV},
	{sf::Keyboard::Escape, arc::QUIT},
	{sf::Keyboard::Space, arc::ACTION_1}
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

void arc::SfmlDisplay::clear()
{
	_window.clear();
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

sf::Sprite &arc::SfmlDisplay::findSprite(const Sprite &currSprite)
{
	for (auto i = _spriteVector.begin(); i != _spriteVector.end(); i++) {
		if (currSprite.getPath() == i->get()->getPath())
			return i->get()->getSprite();
	}
	_spriteVector.push_back(
		std::unique_ptr<SpriteStorage>(
			new SpriteStorage(
				currSprite.getPath(), currSprite.getRotation())));
	return _spriteVector[
		_spriteVector.size() - 1].
		get()->getSprite();
}

void arc::SfmlDisplay::putItem(const Item &item)
{
	auto &currSprite = item.sprites[item.currSpriteIdx];
	sf::Sprite &sprite = findSprite(currSprite);
	sprite.setPosition(currSprite.getX(), currSprite.getY());
	_window.draw(sprite);
}

void arc::SfmlDisplay::putItem(const Item &item, int x, int y)
{
	auto &currSprite = item.sprites[item.currSpriteIdx];
	sf::Sprite &sprite = findSprite(currSprite);
	sprite.setPosition(x, y);
	_window.draw(sprite);
}

void arc::SfmlDisplay::putSpriteList(const SpriteList &splist)
{
	for (auto i = splist.begin(); i != splist.end(); i++)
	{
		auto currSprite = i;
		auto sprite = findSprite(*currSprite);
		sprite.setPosition(currSprite->getX(), currSprite->getY());
		sprite.setRotation(currSprite->getRotation());
		_window.draw(sprite);
	}
}

void arc::SfmlDisplay::putSpritePosition(const Item &item, const std::vector<struct Position> &poslist)
{
	for (auto i  = poslist.begin(); i != poslist.end(); i++) {
		putItem(item, i->x, i->y);
	}
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

arc::InteractionList arc::SfmlDisplay::getInteractions()
{
	InteractionList input;

	for (auto i = KEYMAP.begin(); i != KEYMAP.end(); i++) {
		if (sf::Keyboard::isKeyPressed(i->first))
			input.push(i->second);
	}
	return input;
}
