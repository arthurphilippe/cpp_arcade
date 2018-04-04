/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by xelax,
*/

#include "SdlDisplay.hpp"

extern "C" arc::IDisplay *Construct()
{
	return new arc::SdlDisplay();
}