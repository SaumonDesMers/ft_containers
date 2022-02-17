#include <include.hpp>

template<class T, class Container>
void debug(ft::map<T, Container>& s) {
	std::cout << std::endl;
	std::cout << "size: " << s.size() << std::endl;
	std::cout << std::endl;
}

void test_map() {

	ft::map<int, std::string> m;

	debug(m);

	m[5] = "salut";

	std::cout << m[5] << std::endl;
}