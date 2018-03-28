/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** SolarFox
*/

#ifndef SOLARFOX_HPP_
	#define SOLARFOX_HPP_

	#include <chrono>
	#include <string>
	#include "Arc.hpp"
	#include "IGame.hpp"
	#include "Error.hpp"

namespace arc {
	class SolarFox;
	constexpr auto GRID_H = 42;
	constexpr auto GRID_L = 42;
	constexpr auto GRID_STEP = 12;
	constexpr auto FPS = 56;
	constexpr auto W_HEIGHT = 720;
	constexpr auto W_WIDTH = 1280;
}

class arc::SolarFox : public arc::IGame {
public:
	SolarFox();
	~SolarFox() {
		_startTime = std::chrono::high_resolution_clock::now();
	};
	void dump() const noexcept override;
	ItemList &getItems() noexcept override
	{
		return _items;
	}
	Item &getItemFromName(const std::string &name);
	const Specs &getSpecs() const noexcept override
	{
		return _info;
	}
	void proccessIteraction(Interaction &) noexcept;
	void envUpdate() noexcept;
	void shoot(const std::string &name);
	const std::vector<struct Position> &getBulletPos() {return _bulletpos;}
	void createItems();
	arc::Action canMove(const std::string &name, int x, int y);
	arc::Action moveDirectionPars(arc::Item, const struct Position &pos, const std::string &name);
	arc::Action canMoveDirectionX(const arc::Sprite &, const int &x, const std::string &name);
	arc::Action canMoveDirectionY(const arc::Sprite &, const int &y, const std::string &name);
	class ItemParser {
	public:
		ItemParser() = delete;
		~ItemParser() = delete;
		static arc::SpriteList parser(const std::string &filename);
		static const std::string &getErrorLine();
		static const int &getErrorLineNb();
		using FlagMap = std::unordered_map<std::string, arc::Action>;
		using MapColor = std::unordered_map<std::string, arc::Color>;
		static const std::string getAttribute();
		static std::string _line;
		static void parseLine();
		static arc::Item createItem();
		static std::string setName();
		static Sprite createSprite();
	private:
		static std::string modifyFolder(std::string foldername);
		static void readFile(const std::string &name);
		static int getIndex(const std::string &what);
		static std::string getInfo(const std::string &what);
		static arc::Action setFlag();
		static std::string setPath();
		static char setSubstitute();
		static Color setColor();
		static SpriteList _vector;
		static int _nbrline;
		static Color _color;
	};
private:
	Interaction _keystate;
	std::vector<struct Position> _bulletpos;
	std::string	_name;
	ItemList	_items;
	ItemList	_todraw;
	Specs		_info;
	void setItems(const std::string &path);
	void createSprite();
	void changeItemsPositionFromName(const std::string &name, int a, int b);
	std::chrono::high_resolution_clock::time_point _startTime;
	void changeSpritePosition(SpriteList &spritelist, int x, int y) noexcept;
	static ItemList defaultItems;
	void printBackground() const noexcept;
	void _dumpItems() const noexcept;
	SpriteList &getSpriteListFromName(const std::string &name);
};

#endif /* !SOLARFOX_HPP_ */
