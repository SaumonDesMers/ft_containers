#ifndef INCLUDE_HPP
#define INCLUDE_HPP

#include <iostream>
#include <string>
#include <iomanip>
#include <deque>
#include <list>
#include <other.hpp>
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
	#include <pair.hpp>
#endif

void test_vector();
void test_stack();
void test_map();

#endif