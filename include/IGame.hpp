/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** IGame
*/

#ifndef IGAME_HPP_
	#define IGAME_HPP_

namespace arc {
	class IGame;
}

class arc::IGame {
public:
	virtual ~IGame() = default;

	virtual void dump() const noexcept = 0;
protected:
private:
};

#endif /* !IGAME_HPP_ */
