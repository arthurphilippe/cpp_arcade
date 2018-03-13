//
// EPITECH PROJECT, 2018
// Arcade
// File description:
// Sfml Header
//

#ifndef SFMLDISPLAY_HPP_
	#define SFMLDISPLAY_HPP_

#include <vector>
#include <unordered_map>
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
	void refresh();
	void putstr(const std::string &str, int x = 0, int y = 0);
	void putItem(const Item &);
	void putSprite(sf::Sprite &sprite, sf::Vector2f position);
        sf::Sprite &findSprite(const Sprite &currSprite);
	void waitEvent();
	InteractionList getInteractions();
	using KeyMap = std::unordered_map<sf::Keyboard::Key, Interaction>;
	struct spriteStruct {
		std::string path;
		sf::Sprite sprite;
		sf::Texture texture;
	};
private:
	sf::RenderWindow _window;
	sf::Font _font;
	std::vector<sf::Texture> _text;
	std::vector<struct spriteStruct> _spriteVector;
};

#endif /* !SMFLDISPLAY_HPP_ */
