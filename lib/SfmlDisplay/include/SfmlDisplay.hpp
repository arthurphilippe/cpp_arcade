//
// EPITECH PROJECT, 2018
// Arcade
// File description:
// Sfml Header
//

#ifndef SFMLDISPLAY_HPP_
	#define SFMLDISPLAY_HPP_

#include <iostream>
#include <memory>
#include <vector>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "IDisplay.hpp"
#include "GfxException.hpp"

namespace arc {
	class SfmlDisplay;
	constexpr auto FONT_PATH("lib/SfmlDisplay/sfml/MickeyFont.ttf");
	constexpr auto TEXT_SIZE(24);
};

class arc::SfmlDisplay : public arc::IDisplay {
public:
	SfmlDisplay(int x = 1500, int y = 1000, const std::string &name = "Arcade");
	~SfmlDisplay();

	void clear();
	void refresh();
	void setStep(uint step)
	{
		(void) step;
	}
	void putstr(const std::string &str, int x = 0, int y = 0);
	void putItem(const Item &);
	sf::Sprite &findSprite(const Item &item);
	void waitEvent();
	InteractionList getInteractions();
	using KeyMap = std::unordered_map<sf::Keyboard::Key, Interaction>;

	class SpriteStorage {
	public:
		SpriteStorage(const Item &item)
			: _path(item.sprites[item.currSpriteIdx].path)
			{
				if (!_texture.loadFromFile(item.sprites[item.currSpriteIdx].path))
					throw GfxException(GFX_ERR_INIT);
				_texture.setSmooth(true);
				_sprite.setTexture(_texture);
				auto bound = _sprite.getGlobalBounds();
				_sprite.setOrigin(bound.width / 2 ,bound.height / 2);
			}
		~SpriteStorage() {};
		const std::string &path() const noexcept {return _path;}
		sf::Sprite &getSprite() noexcept {return _sprite;}
	private:
		std::string _path;
		sf::Texture _texture;
		sf::Sprite _sprite;
	};
private:
	sf::RenderWindow _window;
	sf::Font _font;
	std::vector<sf::Texture> _text;
	std::vector<std::unique_ptr<SpriteStorage>> _spriteVector;
};

#endif /* !SMFLDISPLAY_HPP_ */
