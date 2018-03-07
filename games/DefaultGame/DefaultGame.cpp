/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** DefaultGame
*/

#include <iostream>
#include "DefaultGame.hpp"

arc::DefaultGame::DefaultGame()
	: _name("DefaultGame")
{

}

void arc::DefaultGame::dump() const noexcept
{
	std::cout << _name;
}
