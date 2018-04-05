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
	#include <memory>
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
	class SpriteStorage;
	SDL_Renderer *_render;
private:
	SDL_Surface *findSurface(const Sprite &currSprite);
	SDL_Window *_window;
	TTF_Font *_font;
	std::vector<std::unique_ptr<SpriteStorage>> _spriteVector;
};

class arc::SdlDisplay::SpriteStorage {
public:
	SpriteStorage(const std::string &path);
	~SpriteStorage() {};
	const std::string &getPath() const noexcept;
	SDL_Surface *getSurface() const noexcept;
private:
	SDL_Surface *_surface;
	const std::string &_path;
};

#endif /* !SDLDISPLAY_HPP_ */