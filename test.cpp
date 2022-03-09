#include "pair.hpp"
#include "node.hpp"
#include "map.hpp"
#include <iostream>
#include <map>

#define NS ft

typedef int key_type;
typedef int mapped_type;
typedef NS::pair<const key_type, mapped_type> value_type;
typedef NS::pair<const key_type, const mapped_type> const_value_type;
typedef typename NS::map<key_type, mapped_type> map;

template<class Pair>
std::string printPair(Pair p) {
	std::cout << "key: " << p.first << "\t| value: " << p.second << std::endl;
	return "";
}

template<class It>
void print_map(It first, It last) {
	for (It it=first; it!=last; it++)
		print_pair(*it);
	std::cout << std::endl;
}

void	ft_const_bound(const map &mp, const key_type &param)
{
	map::const_iterator ite = mp.end(), it[2];

	std::cout << "with key [" << param << "]:" << std::endl;
	it[0] = mp.lower_bound(param); it[1] = mp.upper_bound(param);
	std::cout << "lower_bound: " << (it[0] == ite ? "end()" : printPair(*(it[0])));
	std::cout << "upper_bound: " << (it[1] == ite ? "end()" : printPair(*(it[1])));
}

void	ft_bound(map &mp, const key_type &param)
{
	map::iterator ite = mp.end(), it[2];

	std::cout << "with key [" << param << "]:" << std::endl;
	it[0] = mp.lower_bound(param); it[1] = mp.upper_bound(param);
	std::cout << "lower_bound: " << (it[0] == ite ? "end()" : printPair(*(it[0])));
	std::cout << "upper_bound: " << (it[1] == ite ? "end()" : printPair(*(it[1])));
}

int main() {

	map m;

	for (int i=0; i<5; i++)
		m[i] = (i+1) * 5;

	const map &mp = m;

	map::const_iterator _it = mp.lower_bound(3);

	printPair(*_it);

	ft_const_bound(mp, 3);
	// ft_bound(m, 3);

	return 0;
}