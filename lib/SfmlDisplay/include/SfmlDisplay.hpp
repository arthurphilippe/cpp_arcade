//
// EPITECH PROJECT, 2018
// Arcade
// File description:
// Sfml Header
//

#ifndef SFMLDISPLAY_HPP_
	#define SFMLDISPLAY_HPP_

#include <SFML/Graphics.hpp>
#include "IDisplay.hpp"

namespace arc {
	class SfmlDisplay;
	constexpr auto FONT_PATH("lib/SfmlDisplay/sfml/MickeyFont.ttf");
	constexpr auto TEXT_SIZE(24);
};

class arc::SfmlDisplay : public arc::IDisplay {
public:
	SfmlDisplay(int x = 1280, int y = 720, const std::string &name = "Arcade");
	~SfmlDisplay();

	void clear();
	void putstr(const std::string &str, int x = 0, int y = 0);
	void waitEvent();
private:
	sf::RenderWindow _window;
	sf::Font _font;
};

#endif /* !SMFLDISPLAY_HPP_ */
