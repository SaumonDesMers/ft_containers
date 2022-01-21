#include <iostream>

template < class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T& >
class iterator {

	private:

		typedef Category	iterator_category;
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
	
	public:


};