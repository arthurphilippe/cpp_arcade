/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by xelax,
*/
#ifndef SDLDISPLAY_HPP_
	#define SDLDISPLAY_HPP_

	#include <SDL2/SDL.h>
	#include <SDL2/SDL_ttf.h>
	#include "GfxException.hpp"
	#include "IDisplay.hpp"

namespace arc {
	class SdlDisplay;
	constexpr auto FONT_PATH("./sdl/FreeSans.ttf");
	constexpr auto TEXT_SIZE(24);
}

class arc::SdlDisplay : public arc::IDisplay {
public:
	SdlDisplay(int width = 1280, int height = 720);
	~SdlDisplay();
	void clear();
	void putstr(const std::string &, int x = 0, int y = 0);
	void putItem(const Item &);
	void putItem(const Item &item, int x, int y);
	void waitEvent();
	void refresh();
	void setStep(uint);
	InteractionList getInteractions();
	void putSpritePosition(const Item &item, const std::vector<struct Position> &poslist);
	void putSpriteList(const SpriteList &list);
private:
	SDL_Window *_window;
	SDL_Renderer *_render;
	TTF_Font *_font;
};

#endif /* !SDLDISPLAY_HPP_ */