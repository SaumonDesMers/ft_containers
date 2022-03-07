#include <include.hpp>

template<class T>
void debug(ft::vector<T>& v) {
	std::cout << "\n_arr: ";
	for (size_t i=0; i<v.size(); i++)
		std::cout << v[i] << (i != v.size() - 1 ? ", " : "");
	// std::cout << "\n_size: " << v.size() << std::endl;
	// std::cout << "_capacity: " << v.capacity() << std::endl;
	std::cout << "\nsize : " << v.size() << ", capacity : " << v.capacity() << std::endl;
	std::cout << std::endl;
}

void test_push_back() {
	int sz = 20;
	ft::vector<int> v;

	v.reserve(6);

	std::cout << "Initial size: " << v.size() << ", capacity: " << v.capacity() << '\n';
	std::cout << "Size:  Capacity:\n" << std::left;
	while (sz-- > 0) {
		v.push_back(sz);
		std::cout << std::setw( 7) << v.size() << std::setw(11) << v.capacity() << '\n';
	}
	std::cout << "\nFinal size: " << v.size() << ", capacity: " << v.capacity() << '\n';

	std::cout << "Vector: " << std::endl;
	for (std::size_t i=0; i<v.size(); i++)
		std::cout << v[i] << ", ";
	std::cout << std::endl;
}

void test_reserve() {
	try {
		ft::vector<int> foo;
		debug(foo);
		for (int i=0; i<5; i++) {
			foo.reserve(i*3);
			std::cout << foo.capacity() << std::endl;
		}
		foo.reserve(foo.max_size() + 1);
	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}

	try {
		ft::vector<int> foo(3);
		debug(foo);
		for (int i=0; i<5; i++) {
			foo.reserve(i*3);
			std::cout << foo.capacity() << std::endl;
		}
	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}

void test_resize() {
	ft::vector<int> v(6, 3);
	debug(v);
	v.reserve(10);
	debug(v);
	v.resize(7);
	debug(v);
	v.resize(12);
	debug(v);
	v.resize(3);
	debug(v);
	try {
		v.resize(v.max_size() + 1);
	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}

void test_pop_back() {
	ft::vector<int> v(5, 3);
	debug(v);
	v.pop_back();
	debug(v);
}

void test_swap() {
	ft::vector<int> v1(5, 3);
	ft::vector<int> v2(3, 5);
	debug(v1);
	debug(v2);
	v1.swap(v2);
	debug(v1);
	debug(v2);
}

void test_assign() {
	ft::vector<int> v1(5, 3);
	debug(v1);
	v1.assign(7, 2);
	debug(v1);
	v1.assign(3, 6);
	debug(v1);
	try {
		v1.assign(v1.max_size() + 1, 7);
	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}

	std::deque<int> v2(10, 9);
	v1.assign(v2.begin(), v2.end());
	debug(v1);
}

void test_insert() {
	ft::vector<int> v(10, 3);
	std::deque<int> d(10, 9);

	v.insert(v.begin() + 2, 4);
	debug(v);
	v.insert(v.begin() + 5, 4, 5);
	debug(v);
	v.insert(v.begin() + 8, d.begin(), d.end());
	debug(v);
}

void test_iterator() {
	ft::vector<int>    myvec;
    for (size_t i = 0; i < 13; i++)
        myvec.push_back(i + 42);
    ft::vector<int>::const_iterator    it = myvec.begin();
    std::cout << "FIRST: " << *it << std::endl;
    for (; it != myvec.end(); it++)
        std::cout << *it << " ";
    std::cout << std::endl;
    ft::vector<int>::reverse_iterator    rit = myvec.rbegin();
    for (; rit != myvec.rend(); rit++)
        std::cout << *rit << " ";
    std::cout << std::endl;
    ft::vector<int>::const_reverse_iterator test = myvec.rend();
    (void)test;
}

void test_erase() {
	ft::vector<std::string> v;

	for (size_t i=0; i<10; i++)
		v.push_back(itoa(i));
	debug(v);
	v.erase(v.begin() + 3, v.begin() + 7);
	debug(v);
	v.erase(v.begin(), v.begin() + 3);
	debug(v);
}

void test_operator() {
	ft::vector<std::string> v1(10, "salut");
	ft::vector<std::string> v2(10, "salut");

	v2[4] = "coucou";

	std::cout << (v1 == v2) << ", ";
	std::cout << (v1 != v2) << ", ";
	std::cout << (v1 < v2) << ", ";
	std::cout << (v1 > v2) << ", ";
	std::cout << (v1 <= v2) << ", ";
	std::cout << (v1 >= v2) << std::endl;

	std::cout << (v1 == v1) << ", ";
	std::cout << (v1 != v1) << ", ";
	std::cout << (v1 < v1) << ", ";
	std::cout << (v1 > v1) << ", ";
	std::cout << (v1 <= v1) << ", ";
	std::cout << (v1 >= v1) << std::endl;
}

class Awesome {

	public:

		Awesome( void ) : _n( 42 ) { std::cout << "Default constructor" << std::endl; } //should not happen too often or else there is a wrong use of allocator (which calls the copy constructor)
		Awesome( int n ) : _n( n ) { std::cout << "Int constructor" << std::endl; (void)n; }
		Awesome( Awesome const &rhs ) : _n( 42 ) { *this = rhs;}
		virtual ~Awesome(void) {}

		Awesome &operator=( Awesome const & rhs ) { this->_n = rhs._n; return (*this); }
		bool operator==( Awesome const & rhs ) const { return (this->_n == rhs._n); }
		bool operator!=( Awesome const & rhs ) const { return (this->_n != rhs._n); }
		bool operator>( Awesome const & rhs ) const { return (this->_n > rhs._n); }
		bool operator<( Awesome const & rhs ) const { return (this->_n < rhs._n); }
		bool operator>=( Awesome const & rhs ) const { return (this->_n >= rhs._n); }
		bool operator<=( Awesome const & rhs ) const { return (this->_n <= rhs._n); }
		void operator+=(int rhs){ _n += rhs; }
		int get( void ) const { return this->_n; }

	private:

		int _n;
};
std::ostream & operator<<( std::ostream & o, Awesome const & rhs ) { o << rhs.get(); return o; }

void test_vector() {

	// test_push_back();
	// test_reserve();
	// test_resize();
	// test_pop_back();
	// test_swap();
	// test_assign();
	// test_insert();
	// test_iterator();
	// test_erase();
	// test_operator();

	std::cout << std::endl << "INSERT TESTS" << std::endl;
	ft::vector<Awesome> test(1, 1);
	ft::vector<Awesome> test2(5, 5);

	test.insert(test.begin(), 200, 12);
	debug<Awesome>(test);
	test.insert(test.begin() + 12, 200, 30);
	debug<Awesome>(test);
	test.insert(test.end(), 12, 50);
	debug<Awesome>(test);
	test.insert(test.end() - 1, 0, 60);
	debug<Awesome>(test);
	test.insert(test.end() - 1, 1, 70);
	debug<Awesome>(test);
	test.insert(test.begin() + 412, test2.begin(), test2.end());
	debug<Awesome>(test);
	test.insert(test.begin() + 6, test2.begin(), test2.end());
	debug<Awesome>(test);
	test.insert(test.end(), test2.begin(), test2.end());
	debug<Awesome>(test);
}