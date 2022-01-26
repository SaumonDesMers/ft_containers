#include <iostream>
#include <string>
#include <deque>
#ifdef STD
	#include <map>
	#include <stack>
	#include <vector>
	namespace ft = std;
#else
	#include <map.hpp>
	#include <stack.hpp>
	#include <vector.hpp>
	#include <utils.hpp>
#endif

int main() {
	
	test
	return 0;
}

void test_is_integral() {

	class A {};

	std::cout << std::boolalpha;
	std::cout << "is_integral:" << std::endl;
	std::cout << "char: " << ft::is_integral<char>::value << std::endl;
	std::cout << "int: " << ft::is_integral<int>::value << std::endl;
	std::cout << "float: " << ft::is_integral<float>::value << std::endl;
	std::cout << "A: " << ft::is_integral<A>::value << std::endl;
	std::cout << "long long: " << ft::is_integral<long long>::value << std::endl;
	std::cout << "unsigned short: " << ft::is_integral<unsigned short>::value << std::endl;
}

void test_enable_if() {

	class A {};

	std::cout << std::boolalpha;
	std::cout << "is_integral:" << std::endl;
	std::cout << "char: " << ft::is_integral<char>::value << std::endl;
	std::cout << "int: " << ft::is_integral<int>::value << std::endl;
	std::cout << "float: " << ft::is_integral<float>::value << std::endl;
	std::cout << "A: " << ft::is_integral<A>::value << std::endl;
	std::cout << "long long: " << ft::is_integral<long long>::value << std::endl;
	std::cout << "unsigned short: " << ft::is_integral<unsigned short>::value << std::endl;
}