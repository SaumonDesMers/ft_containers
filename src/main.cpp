#include <iostream>
#include <string>
#include <iomanip>
#include <deque>
#include <list>
#include <vector>
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

template<class T>
void debug(ft::vector<T>& v) {
	std::cout << "\n_arr: ";
	for (size_t i=0; i<v.size(); i++)
		std::cout << v[i] << (i != v.size() - 1 ? ", " : "");
	std::cout << "\n_size: " << v.size() << std::endl;
	std::cout << "_capacity: " << v.capacity() << std::endl;
	std::cout << std::endl;
}

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
	try {
		ft::vector<int> foo;
		debug(foo);
		for (int i=0; i<5; i++) {
			foo.reserve(i*3);
			std::cout << foo.capacity() << std::endl;
		}
		foo.reserve(foo.max_size() + 1);
	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}

	try {
		ft::vector<int> foo(3);
		debug(foo);
		for (int i=0; i<5; i++) {
			foo.reserve(i*3);
			std::cout << foo.capacity() << std::endl;
		}
	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}

void test_resize() {
	ft::vector<int> v(6, 3);
	debug(v);
	v.reserve(10);
	debug(v);
	v.resize(7);
	debug(v);
	v.resize(12);
	debug(v);
	v.resize(3);
	debug(v);
	try {
		v.resize(v.max_size() + 1);
	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}

void test_pop_back() {
	ft::vector<int> v(5, 3);
	debug(v);
	v.pop_back();
	debug(v);
}

void test_swap() {
	ft::vector<int> v1(5, 3);
	ft::vector<int> v2(3, 5);
	debug(v1);
	debug(v2);
	v1.swap(v2);
	debug(v1);
	debug(v2);
}

void test_assign() {
	ft::vector<int> v1(5, 3);
	debug(v1);
	v1.assign(7, 2);
	debug(v1);
	v1.assign(3, 6);
	debug(v1);
	try {
		v1.assign(v1.max_size() + 1, 7);
	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}

	std::deque<int> v2(10, 9);
	v1.assign(v2.begin(), v2.end());
	debug(v1);
}

void test_insert() {
	ft::vector<int> v(10, 3);
	// std::deque<int> d(10, 9);

	// ft::vector<int>::iterator it = v.begin();

	// v.insert(it + 2, 4);
	debug(v);
}

void test_iterator() {
	ft::vector<int> v(10);

	ft::vector<int>::iterator it = v.begin();

	std::cout << "*it = " << *it << std::endl;
}

int main() {

	// test_compare();
	// test_pair();
	// test_push_back();
	// test_reserve();
	// test_resize();
	// test_pop_back();
	// test_swap();
	// test_assign();
	test_insert();

	return 0;
}
