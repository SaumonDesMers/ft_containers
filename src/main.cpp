#include <iostream>
#include <string>
#include <deque>
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

void test_pair() {

	ft::pair<std::string, double> product1;
	ft::pair<std::string, double> product2 ("tomatoes", 2.30);
	ft::pair<std::string, double> product3 (product2);

	product1 = ft::make_pair(std::string("lightbulbs"), 0.99);

	product2.first = "shoes";
	product2.second = 39.90;

	std::cout << "The price of " << product1.first << " is $" << product1.second << std::endl;
	std::cout << "The price of " << product2.first << " is $" << product2.second << std::endl;
	std::cout << "The price of " << product3.first << " is $" << product3.second << std::endl;

	ft::pair<std::string, int> planet, homeplanet;

	planet = ft::make_pair("Earth", 6371);

	homeplanet = planet;

	std::cout << "Home planet: " << homeplanet.first << std::endl;
	std::cout << "Planet size: " << homeplanet.second << std::endl;

	ft::pair<int, char> foo (10, 'z');
	ft::pair<int, char> bar (90, 'a');

	if (foo==bar) std::cout << "foo and bar are equal\n";
	if (foo!=bar) std::cout << "foo and bar are not equal\n";
	if (foo< bar) std::cout << "foo is less than bar\n";
	if (foo> bar) std::cout << "foo is greater than bar\n";
	if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
	if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";
}

bool mycomp (char c1, char c2) { return std::tolower(c1)<std::tolower(c2); }
bool mypredicate (int i, int j) { return (i==j); }

void test_compare() {

	char foo[]="Apple";
	char bar[]="apartment";

	std::cout << std::boolalpha;

	std::cout << "Comparing foo and bar lexicographically (foo<bar):\n";

	std::cout << "Using default comparison (operator<): ";
	std::cout << std::lexicographical_compare(foo, foo+5, bar, bar+9);
	std::cout << std::endl;

	std::cout << "Using mycomp as comparison object: ";
	std::cout << std::lexicographical_compare(foo, foo+5, bar, bar+9, mycomp);
	std::cout << std::endl;

	int myints[] = {20, 40, 60, 80, 100};
	int myints2[] = {20, 40, 60, 80, 100};

	// using default comparison:
	if ( std::equal (myints2, myints2 + 5, myints))
		std::cout << "The contents of both sequences are equal.\n";
	else
		std::cout << "The contents of both sequences differ.\n";

	myints2[3]=81;

	// using predicate comparison:
	if ( std::equal (myints2, myints2 + 5, myints, mypredicate))
		std::cout << "The contents of both sequences are equal.\n";
	else
		std::cout << "The contents of both sequences differ.\n";
		
}

int main() {

	test_compare();
	return 0;
}
