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
//	const char *what() const noexcept;
	ParserError(const std::string &what) : _what(what) {}
	const std::string &printError() const noexcept {std::cerr << _what << std::endl;}
	const std::string &getError() const {return _what;}
	std::string _what;
};

#endif /* !ERROR_HPP_ */
