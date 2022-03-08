#include "pair.hpp"
#include "node.hpp"
#include <iostream>

typedef int key_type;
typedef int mapped_type;
typedef ft::pair<const key_type, mapped_type> value_type;
typedef ft::pair<const key_type, const mapped_type> const_value_type;
typedef typename ft::map<key_type, mapped_type> map;

int main() {

	map m;

	value_type p;
	const_value_type _p(p);

	// ft::node<map, value_type> n;
	// ft::node<map, const_value_type> _n(n);

	// map::iterator it;
	// map::const_iterator _it(it);

	return 0;
}