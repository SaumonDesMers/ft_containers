#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <iostream>

namespace ft
{
	
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

} // namespace ft

#endif