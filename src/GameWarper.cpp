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
	_displayEntry("./lib/CacaDisplay/libcaca.so"),
	_currGame(_gameEntry.get()()),
	_currDisplay(_displayEntry.get()())
{
	for_each(_currGame->getItems().begin(), _currGame->getItems().end(),
			 _setItemSprites);
	_currGame->dump();
	_currDisplay->clear();
	_currDisplay->putstr("kapa", 0, 0);
	_currDisplay->refresh();
	_currDisplay->waitEvent();
}

void arc::GameWarper::_setItemSprites(IGame::Item &item)
{
	if (item.spritesPath.length())
		item.sprites = SpriteParser::parser(item.spritesPath);
}

