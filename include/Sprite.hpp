//
// EPITECH PROJECT, 2018
// Aracade
// File description:
// Sprite Header
//

#ifndef SPRITE_HPP_
	#define SPRITE_HPP_

	#include <iostream>
	#include <vector>

namespace arc {
	class Sprite;
	using SpriteList = std::vector<Sprite>;
	enum Color {
		BLUE,
		RED,
		GREEN,
		YELLOW,
		CYAN,
		MAGENTA,
		WHITE,
		BLACK,
		UNDEFINED,
	        DFT_COLOR_RET_ERROR,
	};
}

class arc::Sprite {
public:
	Sprite(const std::string &name, const std::string &path,
		const char &substitute)
		: _substitute(substitute), _name(name), _path(path) {};
	~Sprite(){};
	void setName(const std::string &name) noexcept {_name = name;}
	void setPath(const std::string &path) noexcept {_path = path;}
	void setColor(const arc::Color &color) noexcept {_color = color;}
	void setSubstitute(const char &substitute) noexcept
	{
		_substitute = substitute;
	}
	void setX(const int &x) noexcept {_x = x;}
	void setY(const int &y) noexcept {_y = y;}
	void setRotation(const int &rotation) noexcept {_rotation = rotation;}
	const std::string &getName() const noexcept {return _name;}
	const std::string &getPath() const noexcept {return _path;}
	const char &getSubstitute() const noexcept {return _substitute;}
	const arc::Color &getColor() const noexcept {return _color;}
	const int &getX() const noexcept {return _x;}
	const int &getY() const noexcept {return _y;}
	const int &getRotation() const noexcept {return _rotation;}
private:
	int _x;
	int _y;
	int _rotation;
	char _substitute;
	std::string _name;
	std::string _path;
	arc::Color _color;
};

#endif /* !SPRITE_HPP_ */
