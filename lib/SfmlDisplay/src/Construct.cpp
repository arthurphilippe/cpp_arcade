//
// EPITECH PROJECT, 2018
// Aracade
// File description:
// Constructor
//

#include "SfmlDisplay.hpp"

extern "C" arc::IDisplay *Construct()
{
	return new arc::SfmlDisplay();
}
