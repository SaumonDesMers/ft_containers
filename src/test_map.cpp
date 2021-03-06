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

void test_copy_map() {
	typedef ft::map<int, std::string>	map;

	map m;

	for (int i=0; i<10; i++)
		m[i*3] = "";
	
	debug(m);

	map m1;

	for (int i=0; i<5; i++)
		m1[i*2] = "";

	debug(m1);

	m = m1;

	debug(m);

}

void test_swap_map() {
	typedef ft::map<int, std::string>	map;

	map m1;

	m1[5] = "salut";
	m1[3] = "coucou";
	m1[7] = "hey";
	m1[1] = "yo";

	map m2;

	m2[4] = "bonjour";
	m2[6] = "mdr";
	m2[9] = "lol";

	std::cout << "M1" << std::endl;
	debug(m1);
	std::cout << std::endl;

	std::cout << "M2" << std::endl;
	debug(m2);

	std::cout << "Swap" << std::endl;
	std::cout << std::endl;
	m1.swap(m2);

	std::cout << "M1" << std::endl;
	debug(m1);
	std::cout << std::endl;

	std::cout << "M2" << std::endl;
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
	m[6] = "mdr";
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
	m[6] = "mdr";
	m[9] = "lol";

	map::iterator it;
	for (int i=0; i<11; i++) {
		it = m.upper_bound(i);
		std::cout << "upper_bound of " << i << " is " << (it == m.end() ? "end" : itoa(it->first)) << std::endl;
	}
}

void test_insert_map() {
	typedef ft::map<int, std::string>	map;

	{
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
	{
		map m;

		m[5] = "salut";
		m[3] = "coucou";
		m[7] = "hey";
		m[1] = "yo";

		map m2;

		m2[4] = "bonjour";
		m2[6] = "mdr";
		m2[9] = "lol";

		m2.insert(m.begin(), m.end());

		debug(m2);
	}
	{
		map m;

		m[5] = "salut";
		m[3] = "coucou";
		m[7] = "hey";
		m[1] = "yo";
		m[4] = "bonjour";
		m[6] = "mdr";

		map::value_type to_insert(9, "lol");

		ft::pair<map::iterator, bool> p = m.insert(to_insert);

		std::cout << "iterator->first = " << p.first->first << std::endl;
		std::cout << "iterator->second = " << p.first->second << std::endl;
		std::cout << std::boolalpha << "bool = " << p.second << std::endl;

		ft::pair<map::iterator, bool> p2 = m.insert(to_insert);

		std::cout << std::endl;

		std::cout << "iterator->first = " << p2.first->first << std::endl;
		std::cout << "iterator->second = " << p2.first->second << std::endl;
		std::cout << std::boolalpha << "bool = " << p2.second << std::endl;

		debug(m);
	}
	{
		map m;

		m[5] = "salut";
		m[3] = "coucou";
		m[7] = "hey";
		m[1] = "yo";
		m[6] = "mdr";
		m[9] = "lol";

		map::value_type to_insert(4, "bonjour");

		map::iterator hint = m.begin();
		for (; hint->first < to_insert.first; hint++);

		m.insert(hint, to_insert);

		debug(m);
	}
}

void rel_ope_test(ft::map<int, std::string> m1, ft::map<int, std::string> m2, std::string const & m1_name, std::string const & m2_name) {
	std::cout << std::boolalpha << std::endl;
	std::cout << m1_name << " == " << m2_name << " = " << (m1 == m2) << std::endl;
	std::cout << m1_name << " != " << m2_name << " = " << (m1 != m2) << std::endl;
	std::cout << m1_name << " < " << m2_name << " = " << (m1 < m2) << std::endl;
	std::cout << m1_name << " > " << m2_name << " = " << (m1 > m2) << std::endl;
	std::cout << m1_name << " <= " << m2_name << " = " << (m1 <= m2) << std::endl;
	std::cout << m1_name << " >= " << m2_name << " = " << (m1 >= m2) << std::endl;
	std::cout << std::endl;
}

void test_rel_ope_map() {
	typedef ft::map<int, std::string>	map;

	map m1;

	m1[5] = "salut";
	m1[3] = "coucou";
	m1[7] = "hey";
	m1[1] = "yo";

	map m2;

	m2[4] = "bonjour";
	m2[6] = "mdr";
	m2[9] = "lol";

	map m3;

	m1[5] = "salut";
	m1[3] = "coucou";
	m1[7] = "hey";

	map m4;

	rel_ope_test(m1, m1, "m1", "m1");

	rel_ope_test(m1, m2, "m1", "m2");
	rel_ope_test(m2, m1, "m2", "m1");

	rel_ope_test(m1, m3, "m1", "m3");
	rel_ope_test(m3, m1, "m3", "m1");

	rel_ope_test(m1, m4, "m1", "m4");
	rel_ope_test(m4, m1, "m4", "m1");

	rel_ope_test(m3, m2, "m3", "m2");
	rel_ope_test(m2, m3, "m2", "m3");
}

void test_erase_map() {
	typedef ft::map<int, std::string>	map;

	map m;
	
	for (int i=0; i<15; i++)
		m[i] = "";

	m.erase(m.find(5), m.find(9));
	debug(m);
}

void test_const_iterator_map() {
	typedef ft::map<int, char>	map;

	map m;
	
	for (int i=0; i<15; i++)
		m[i] = i + 65;
	
	map::iterator it = m.begin();
	map::const_iterator cit(it);

	it++;
	it->second = '1';
	// cit->second = '2';
	cit++;
	std::cout << cit->second << std::endl;

	// map::iterator it2(cit);
	map::const_iterator cit2(it);

	map::reverse_iterator rit(m.rbegin());
	std::cout << rit->first << std::endl;
	map::reverse_iterator crit(m.rbegin());
	std::cout << crit->first << std::endl;

	const map &mp = m;

	cit = mp.lower_bound(5);
}

void test_map() {
	test_swap_map();
	test_find_map();
	test_lower_bound_map();
	test_upper_bound_map();
	test_insert_map();
	test_rel_ope_map();
	test_copy_map();
	test_erase_map();
	test_const_iterator_map();
}