#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <iterator.hpp>

namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
	class vector {

		public:

			typedef T												value_type;
			typedef Alloc											allocator_type;
			typedef typename std::size_t							size_type;
			typedef typename std::ptrdiff_t							difference_type;
			typedef value_type&										reference;
			typedef const value_type&								const_reference;
			typedef typename Alloc::pointer							pointer;
			typedef typename Alloc::const_pointer					const_pointer;
			// typedef typename std::reverse_iterator<iterator>		reverse_iterator;
			// typedef typename std::reverse_iterator<const_iterator>	const_reverse_iterator;

			//########################################################################

			vector();

	};

	template <class T, class Alloc>
	bool operator== ( const ft::vector<T, Alloc>& left, const ft::vector<T, Alloc>& right);

	template <class T, class Alloc>
	bool operator!= ( const ft::vector<T, Alloc>& left, const ft::vector<T, Alloc>& right);

	template <class T, class Alloc>
	bool operator<( const ft::vector<T, Alloc>& left, const ft::vector<T, Alloc>& right);

	template <class T, class Alloc>
	bool operator> ( const ft::vector<T, Alloc>& left, const ft::vector<T, Alloc>& right);

	template <class T, class Alloc>
	bool operator<= ( const ft::vector<T, Alloc>& left, const ft::vector<T, Alloc>& right);

	template <class T, class Alloc>
	bool operator>= ( const ft::vector<T, Alloc>& left, const ft::vector<T, Alloc>& right);

	template <class T, class Alloc>
	void swap ( ft::vector<T, Alloc>& left, ft::vector<T, Alloc>& right);
	
} // namespace ft

#endif