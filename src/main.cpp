#include <iostream>
#include <string>
#include <iomanip>
#include <deque>
#ifdef STD
	#include <map>
	#include <stack>
	#include <vector>
	#include <utility>
	#include <algorithm>
	namespace ft = std;
#else
	#include <map.hpp>
	#include <stack.hpp>
	#include <vector.hpp>
	#include <utils.hpp>
	#include <pair.hpp>
#endif

void test_push_back() {
	int sz = 20;
	ft::vector<int> v;

	v.reserve(6);

	std::cout << "Initial size: " << v.size() << ", capacity: " << v.capacity() << '\n';
	std::cout << "Size:  Capacity:\n" << std::left;
	while (sz-- > 0) {
		v.push_back(sz);
		std::cout << std::setw( 7) << v.size() << std::setw(11) << v.capacity() << '\n';
	}
	std::cout << "\nFinal size: " << v.size() << ", capacity: " << v.capacity() << '\n';

	std::cout << "Vector: " << std::endl;
	for (std::size_t i=0; i<v.size(); i++)
		std::cout << v[i] << ", ";
	std::cout << std::endl;
}

void test_reserve() {
	try
	{
		ft::vector<int> foo;
		std::cout << foo.capacity() << std::endl;
		for (int i=0; i<5; i++) {
			foo.reserve(i*3);
			std::cout << foo.capacity() << std::endl;
		}
		foo.reserve(foo.max_size() + 1);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	try
	{
		ft::vector<int> foo(3);
		std::cout << foo.capacity() << std::endl;
		for (int i=0; i<5; i++) {
			foo.reserve(i*3);
			std::cout << foo.capacity() << std::endl;
		}
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

int main() {

	// test_compare();
	// test_pair();
	test_push_back();
	// test_reserve();
	return 0;
}
