/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Constructor
*/

#include "IDisplay.hpp"
#include "CacaDisplay.hpp"

extern "C" arc::IDisplay *Construct()
{
	return new arc::CacaDisplay();
}
