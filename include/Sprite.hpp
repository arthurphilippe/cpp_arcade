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
}

class arc::Sprite {
public:
	Sprite(const std::string &name, const std::string &path,
		const char &substitute)
		: _substitute(substitute), _name(name), _path(path) {};
	~Sprite(){};
	void setName(const std::string &name) noexcept {_name = name;}
	void setPath(const std::string &path) noexcept {_path = path;}
	void setSubstitute(const char &substitute) noexcept
	{
		_substitute = substitute;
	}
	const std::string &getName() const noexcept {return _name;}
	const std::string &getPath() const noexcept {return _path;}
	const char &getSubstitute() const noexcept {return _substitute;}
private:
	char _substitute;
	std::string _name;
	std::string _path;
};

#endif /* !SPRITE_HPP_ */
