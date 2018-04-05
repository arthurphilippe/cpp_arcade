/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** GfxException
*/

#ifndef GFXEXCEPTION_HPP_
	#define GFXEXCEPTION_HPP_

	#include <string>

namespace arc {
	class GfxException;
	constexpr auto GFX_ERR_INIT("Failed to init GUI");
	constexpr auto GFX_ERR_TEXT_LOADING("Failed to load text");
	constexpr auto GFX_ERR_SPRITE_LOADING("Failed to load sprite");
}

class arc::GfxException {
public:
	const char *what() const noexcept;
	GfxException(const std::string &err)
		: _what(err)
	{}
	GfxException(const char *err)
		: _what(err)
	{}
	const std::string &getError() const
	{
		return _what;
	}
private:
	std::string _what;
};

#endif /* !GFXEXCEPTION_HPP_ */
