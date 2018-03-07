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

class ParserError : public std::exception {
public:
	const char *what() const noexcept
		{
			std::cerr << _what << std::endl;
			return _what.c_str();
		}
	ParserError(const std::string &what) : _what(what) {}
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

#endif /* !ERROR_HPP_ */
