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

template<class T>
void log(T *obj, std::string msg) {
	std::cout << "{" << obj << "} " << msg << std::endl;
}

template<class T>
void log(T *obj, std::string msg, T *param) {
	std::cout << "{" << obj << "} " << msg << " {" << param << "}" << std::endl;
}

template<class T, class U>
void log(T *obj, std::string msg, U *param) {
	std::cout << "{" << obj << "} " << msg << " {" << param << "}" << std::endl;
}

#endif