/*
** EPITECH PROJECT, 2018
** Arcade
** File description:
** BackGround
*/

#ifndef BACKGROUND_HPP_
	#define BACKGROUND_HPP_

#include "Arc.hpp"

namespace arc {
        class BackGround;
}

class arc::BackGround {
public:
        BackGround(const std::string &filename);
        ~BackGround() {}
        const std::vector<struct Position> getBackGround() const noexcept {return _background;}
private:
        int getIndex(const std::string &what);
        void parseLine();

        std::string getInfo(const std::string &what);
        std::string _filename;
        std::string _line;
        std::vector<struct Position> _background;
};

#endif /* !BACKGROUND_HPP_ */
