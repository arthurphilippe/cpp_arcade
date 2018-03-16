/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Entry
*/

#include <iostream>
#include <memory>
#include "SolarFox.hpp"

extern "C" {
	arc::IGame *Construct()
	{
		return new arc::SolarFox();
	}
}
