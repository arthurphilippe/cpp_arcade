/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by xelax,
*/

#include "IDisplay.hpp"
#include "NCursesDisplay.hpp"

extern "C" arc::IDisplay *Construct()
{
	return new arc::NCursesDisplay();
}
