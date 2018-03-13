/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** GameWarper
*/

#include <algorithm>
#include "GameWarper.hpp"
#include "SpriteParser.hpp"

arc::GameWarper::GameWarper()
	: _gameEntry("./games/Pacman/libPacman.so"),
	_displayEntry("./lib/SfmlDisplay/libsfml.so"),
	_currGame(_gameEntry.get()()),
	_currDisplay(_displayEntry.get()())
{
	for_each(_currGame->getItems().begin(), _currGame->getItems().end(),
			 _setItemSprites);
	_currGame->dump();
	_currDisplay->clear();
	// _currDisplay->putstr("kapa", 0, 0);
	// _currDisplay->refresh();
}

arc::GameWarper::~GameWarper()
{
	bool hasExited = false;
	while (!hasExited) {
		auto inter = _currDisplay->getInteractions();
		while (inter.size() != 0) {
			if (inter.front() == Interaction::QUIT) {
				std::cout << "recived quit" << std::endl;
				hasExited = true;
			} else {
				_currGame->proccessIteraction(inter.front());
				// _currGame->dump();
				_currDisplay->putItem(_currGame->getItems()[0]);
				_currDisplay->refresh();
			}
			inter.pop();
		}
	}
}

void arc::GameWarper::_setItemSprites(Item &item)
{
	if (item.spritesPath.length())
		item.sprites = SpriteParser::parser(item.spritesPath);
}
