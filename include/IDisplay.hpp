/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** IDisplay
*/

#ifndef IDisplay_HPP_
	#define IDisplay_HPP_

	#include <string>

namespace arc {
	class IDisplay;
}

class arc::IDisplay {
public:
	virtual ~IDisplay() = default;
	virtual void clear() = 0;
	virtual void putstr(const std::string &, int x = 0, int y = 0) = 0;
	virtual void waitEvent() = 0;
	virtual void display() = 0;
protected:
private:
};

#endif /* !IDisplay_HPP_ */
