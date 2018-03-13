//
// EPITECH PROJECT, 2018
// Arcade
// File description:
// Sfml Header
//

#ifndef SFMLDISPLAY_HPP_
	#define SFMLDISPLAY_HPP_

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
	SfmlDisplay(int x = 1280, int y = 720, const std::string &name = "Arcade");
	~SfmlDisplay();

	void clear();
	void refresh();
	void putstr(const std::string &str, int x = 0, int y = 0);
	void putItem(const Item &);
        sf::Sprite &findSprite(const Sprite &currSprite);
	void waitEvent();
	InteractionList getInteractions();
	using KeyMap = std::unordered_map<sf::Keyboard::Key, Interaction>;

	class SpriteStockage {
	public:
		SpriteStockage(const std::string &path)
			: _path(path)
			{
				if (!_texture.loadFromFile(path))
					throw GfxException(GFX_ERR_INIT);
				_texture.setSmooth(true);
				_sprite.setTexture(_texture);
			}
		~SpriteStockage() {};
		const std::string &getPath() const noexcept {return _path;}
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
