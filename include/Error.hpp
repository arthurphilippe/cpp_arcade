//
// EPITECH PROJECT, 2018
// nanotekspice
// File description:
// errors class headers
//

#ifndef ERROR_HPP_
	#define ERROR_HPP_

#include <iostream>
#include <exception>

namespace arc {
	class ParserError;
	class StartupError;
	constexpr auto ERR_CONF("error: In configuration file\n  ");
	constexpr auto ERR_SUB("\n  sub char cannot be multiple char long");
	constexpr auto ERR_PATH("\n  can't access to the indicated path");
	constexpr auto ERR_NAME("\n  separator not found");
	constexpr auto ERR_COLOR("\n  can't find a color");
	constexpr auto ERR_GFX_PATH("Error: can't find the following path Gfx path: ");
	constexpr auto ERR_GAME_PATH("Error: can't find the following path Game path: ");
};
class arc::ParserError : public std::exception {
public:
	const char *what() const noexcept
		{
			std::cerr << _what << std::endl;
			return _what.c_str();
		}
	ParserError(const std::string &what);
	ParserError(
		const std::string &ch1, const std::string &ch2,
		const std::string &ch3)
		{
			_what = ch1 + ch2 + ch3;
		}
	const std::string &getError() const {return _what;}
private:
	std::string _what;
};

class arc::StartupError : public std::exception {
public:
	const char *what() const noexcept
	{
		std::cerr << _what << std::endl;
		return _what.c_str();
	}
	StartupError(const std::string &what) : _what(what) {}
	const std::string &getError() const {return _what;}
private:
	std::string _what;
};

#endif /* !ERROR_HPP_ */
