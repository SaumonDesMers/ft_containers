#include <include.hpp>

template<class T, class Container>
void debug(ft::map<T, Container>& s) {
	std::cout << std::endl;
	std::cout << "size: " << s.size() << std::endl;
	std::cout << std::endl;
}

void test_map() {
	typedef ft::map<int, std::string>	map;
	typedef ft::map<int, std::string>::iterator	iterator;

	map m;

	m[5] = "salut";
	m[3] = "coucou";
	m[7] = "hey";
	m[1] = "yo";
	m[4] = "bonjour";
	m[6] = "mdr";
	m[9] = "lol";

	// m.print();

	for (iterator it = m.begin(); it != m.end(); it++);
		// std::cout << "Key = " << it->first << "  Value = " << it->second << std::endl;

	map m2(m.begin(), m.end());

	for (iterator it = m2.begin(); it != m2.end(); it++)
		std::cout << "Key = " << it->first << "  Value = " << it->second << std::endl;

}