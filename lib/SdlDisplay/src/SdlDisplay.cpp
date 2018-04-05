/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by xelax,
*/

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "SdlDisplay.hpp"

arc::SdlDisplay::SdlDisplay(int width, int height)
{
	int ret_value = -1;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == -1)
		throw GfxException(GFX_ERR_INIT);
	ret_value = SDL_CreateWindowAndRenderer(width, height,
		SDL_WINDOW_RESIZABLE, &_window, &_render);
	if (ret_value < 0)
		throw GfxException(GFX_ERR_INIT);
	if (SDL_SetRenderDrawColor(_render, 0, 0, 0, 255) < 0)
		throw GfxException(GFX_ERR_INIT);
	SDL_RenderPresent(_render);
	if (TTF_Init() == -1)
		throw GfxException(GFX_ERR_INIT);
	if (IMG_Init(IMG_INIT_PNG) == -1)
		throw GfxException(GFX_ERR_INIT);
	/*_font = TTF_OpenFont(FONT_PATH, TEXT_SIZE);
	if (_font == NULL)
		throw GfxException(GFX_ERR_INIT);*/
}

arc::SdlDisplay::~SdlDisplay()
{
	//TTF_CloseFont(_font);
	TTF_Quit();
	IMG_Quit();
	SDL_DestroyRenderer(_render);
	SDL_DestroyWindow(_window);
	SDL_Quit();
}

void arc::SdlDisplay::clear()
{
	SDL_RenderClear(_render);
}

void arc::SdlDisplay::putstr(const std::string &str, int x, int y)
{
	SDL_Surface *window = SDL_GetWindowSurface(_window);
	SDL_Surface *text = TTF_RenderText_Solid(_font, str.c_str(), { 255, 255, 255, 0 });
	SDL_Rect position = { 0, 0, x, y };

	if (SDL_FillRect(window, NULL, 0) < 0)
		throw GfxException(GFX_ERR_TEXT_LOADING);
	SDL_BlitSurface(text, NULL, window, &position);
	SDL_RenderPresent(_render);
}

SDL_Surface *arc::SdlDisplay::findSurface(const arc::Sprite &currSprite)
{
	for (auto i = _spriteVector.begin(); i != _spriteVector.end(); i++) {
		if (currSprite.path == (*i)->getPath())
			return i->get()->getSurface();
	}
	_spriteVector.push_back(std::unique_ptr<SpriteStorage>(
				new SpriteStorage(currSprite.path)));
	return _spriteVector[_spriteVector.size() - 1].get()->getSurface();
}

void arc::SdlDisplay::putItem(const arc::Item &item)
{
	auto &currSprite = item.sprites[item.currSpriteIdx];
	SDL_Surface *surface = findSurface(currSprite);
	SDL_Rect position = { item.x, item.y, 0, 0 };
	SDL_Texture *texture;

	if (surface == NULL)
		throw GfxException(GFX_ERR_SPRITE_LOADING);
	position.w = surface->w;
	position.h = surface->h;
	texture = SDL_CreateTextureFromSurface(_render, surface);
	if (texture == NULL)
		throw GfxException(GFX_ERR_SPRITE_LOADING);
	SDL_RenderCopy(_render, texture, NULL, &position);
}

void arc::SdlDisplay::putItem(const arc::Item &item, int x, int y)
{
	Sprite currSprite = item.sprites[item.currSpriteIdx];
	SDL_Surface *surface = findSurface(currSprite);
	SDL_Rect position = { x, y, 0, 0 };
	SDL_Texture *texture;

	if (surface == NULL)
		throw GfxException(GFX_ERR_SPRITE_LOADING);
	position.w = surface->w;
	position.h = surface->h;
	texture = SDL_CreateTextureFromSurface(_render, surface);
	if (texture == NULL)
		throw GfxException(GFX_ERR_SPRITE_LOADING);
	SDL_RenderCopy(_render, texture, NULL, &position);
}

void arc::SdlDisplay::waitEvent()
{
}

void arc::SdlDisplay::refresh()
{
}

void arc::SdlDisplay::setStep(uint step)
{
	(void)step;
}

arc::InteractionList arc::SdlDisplay::getInteractions()
{
	return arc::InteractionList();
}

void arc::SdlDisplay::putSpritePosition(const arc::Item &item,
	const std::vector<struct Position> &poslist)
{
	(void)item;
	(void)poslist;
}

void arc::SdlDisplay::putSpriteList(const arc::SpriteList &list)
{
	(void)list;
}

arc::SdlDisplay::SpriteStorage::SpriteStorage(const std::string &path) :
	_path(path)
{
	_surface = IMG_Load(path.c_str());
	if (_surface == NULL)
		throw GfxException(GFX_ERR_SPRITE_LOADING);
}

const std::string &arc::SdlDisplay::SpriteStorage::getPath() const noexcept
{
	return (_path);
}

SDL_Surface *arc::SdlDisplay::SpriteStorage::getSurface() const noexcept
{
	return (_surface);
}