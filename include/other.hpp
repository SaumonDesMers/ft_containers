#ifndef OTHER_HPP
#define OTHER_HPP

#include <sstream>
#include <iostream>

template<class T>
std::string itoa(T n) {
	std::stringstream out;
	out << n;
	return out.str();
}

#endif