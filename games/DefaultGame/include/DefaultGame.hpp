/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** DefaultGame
*/

#ifndef DEFAULTGAME_HPP_
	#define DEFAULTGAME_HPP_

	#include <string>
	#include "IGame.hpp"

namespace arc {
	class DefaultGame;
}

class arc::DefaultGame : public arc::IGame {
public:
	DefaultGame();
	~DefaultGame() {};
	void dump() const noexcept override;
protected:
private:
	std::string _name;
};

#endif /* !DEFAULTGAME_HPP_ */
