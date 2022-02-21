#include <include.hpp>

template<class T, class Container>
void debug(ft::map<T, Container>& s) {
	std::cout << std::endl;
	std::cout << "size: " << s.size() << std::endl;
	std::cout << std::endl;
}

void test_map() {

	ft::map<int, std::string> m;

	m[5] = "salut";
	m[3] = "coucou";
	m[7] = "hey";
	m[1] = "yo";
	m[4] = "bonjour";

	try
	{
		std::cout << "map.at(7) = " << m.at(7) << std::endl;
		std::cout << "map.at(10) = " << m.at(10) << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	m.print();

}