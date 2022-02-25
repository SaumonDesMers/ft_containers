#include <include.hpp>

template<class Key, class Value>
void debug(ft::map<Key, Value>& m) {
	std::cout << std::endl;
	for (typename ft::map<Key, Value>::iterator it = m.begin(); it != m.end(); it++)
		std::cout << "Key = " << it->first << "  Value = " << it->second << std::endl;
	std::cout << std::endl;
}

template<class ImputIt>
void debug(ImputIt first, ImputIt last) {
	std::cout << std::endl;
	for (ImputIt it = first; it != last; it++)
		std::cout << "Key = " << it->first << "  Value = " << it->second << std::endl;
	std::cout << std::endl;
}

void test_swap_map() {
	typedef ft::map<int, std::string>	map;

	map m1;

	m1[5] = "salut";
	m1[3] = "coucou";
	m1[7] = "hey";
	m1[1] = "yo";

	map::iterator m_it = m1.begin();
	map::iterator m_ite = m1.end();

	map m2;

	m2[4] = "bonjour";
	m2[6] = "mdr";
	m2[9] = "lol";

	map::iterator m2_it = m2.begin();
	map::iterator m2_ite = m2.end();

	std::cout << "M1" << std::endl;
	debug(m_it, m_ite);
	std::cout << std::endl;

	std::cout << "M2" << std::endl;
	debug(m2_it, m2_ite);

	std::cout << "Swap" << std::endl;
	std::cout << std::endl;
	m1.swap(m2);

	std::cout << "M1" << std::endl;
	std::cout << "with old iterator" << std::endl;
	debug(m_it, m_ite);
	std::cout << "with swaped map" << std::endl;
	debug(m1);
	std::cout << std::endl;

	std::cout << "M2" << std::endl;
	std::cout << "with old iterator" << std::endl;
	debug(m2_it, m2_ite);
	std::cout << "with swaped map" << std::endl;
	debug(m2);
	std::cout << std::endl;
}

void test_find_map() {
	typedef ft::map<int, std::string>	map;

	map m;

	m[5] = "salut";
	m[3] = "coucou";
	m[7] = "hey";
	m[1] = "yo";
	m[4] = "bonjour";
	m[6] = "mdr";
	m[9] = "lol";

	map::iterator it;
	it = m.find(6);
	if (it != m.end())
		std::cout << "key 6 is found" << std::endl;
	else
		std::cout << "key 6 isn't found" << std::endl;

	it = m.find(11);
	if (it != m.end())
		std::cout << "key 11 is found" << std::endl;
	else
		std::cout << "key 11 isn't found" << std::endl;
}

void test_lower_bound_map() {
	typedef ft::map<int, std::string>	map;

	map m;

	m[5] = "salut";
	m[3] = "coucou";
	m[7] = "hey";
	m[1] = "yo";
	m[4] = "bonjour";
	// m[6] = "mdr";
	m[9] = "lol";

	map::iterator it;
	for (int i=0; i<11; i++) {
		it = m.lower_bound(i);
		std::cout << "lower_bound of " << i << " is " << (it == m.end() ? "end" : itoa(it->first)) << std::endl;
	}
}

void test_upper_bound_map() {
	typedef ft::map<int, std::string>	map;

	map m;

	m[5] = "salut";
	m[3] = "coucou";
	m[7] = "hey";
	m[1] = "yo";
	m[4] = "bonjour";
	// m[6] = "mdr";
	m[9] = "lol";

	map::iterator it;
	for (int i=0; i<11; i++) {
		it = m.upper_bound(i);
		std::cout << "upper_bound of " << i << " is " << (it == m.end() ? "end" : itoa(it->first)) << std::endl;
	}
}

void test_insert_map() {
	typedef ft::map<int, std::string>	map;

	map m;

	m[5] = "salut";
	m[3] = "coucou";
	m[7] = "hey";
	m[1] = "yo";
	m[4] = "bonjour";
	m[6] = "mdr";
	m[9] = "lol";

	map m2;

	m2.insert(m.begin(), m.end());

	debug(m2);
}

void test_map() {
	// test_swap_map();
	// test_find_map();
	// test_lower_bound_map();
	// test_upper_bound_map();
	test_insert_map();
}