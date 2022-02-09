#include <include.hpp>

template<class T, class Container>
void debug(ft::stack<T, Container>& s) {
	std::cout << std::endl;
	std::cout << "top: " << s.top() << std::endl;
	std::cout << "size: " << s.size() << std::endl;
	std::cout << std::endl;
}

void test_stack() {

	ft::stack<int> s1;

	ft::vector<int> v(10, 3);
	ft::stack<int, ft::vector<int> > s2(v);

	std::deque<int> d(10, 3);
	ft::stack<int, std::deque<int> > s3(d);

	for (int i=0; i<15; i++) {
		s1.push(i);
		std::cout << s1.top() << ", ";
	}
	std::cout << std::endl;

#ifdef STD
	std::cout << (s1 == s3) << ", ";
	std::cout << (s1 != s3) << ", ";
	std::cout << (s1 < s3) << ", ";
	std::cout << (s1 > s3) << ", ";
	std::cout << (s1 <= s3) << ", ";
	std::cout << (s1 >= s3) << std::endl;
#else
	std::cout << (s1 == s2) << ", ";
	std::cout << (s1 != s2) << ", ";
	std::cout << (s1 < s2) << ", ";
	std::cout << (s1 > s2) << ", ";
	std::cout << (s1 <= s2) << ", ";
	std::cout << (s1 >= s2) << std::endl;
#endif

	std::cout << (s1 == s1) << ", ";
	std::cout << (s1 != s1) << ", ";
	std::cout << (s1 < s1) << ", ";
	std::cout << (s1 > s1) << ", ";
	std::cout << (s1 <= s1) << ", ";
	std::cout << (s1 >= s1) << std::endl;

	debug(s1);
	debug(s2);

	for (int i=0; i<7; i++)
		s1.pop();
	std::cout << std::endl;
	for (int i=0; i<3; i++)
		s2.pop();
	
	debug(s1);
	debug(s2);
}