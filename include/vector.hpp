#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <iterator.hpp>
#include <iterator>

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
			// typedef typename std::iterator<iterator>				iterator;
			// typedef typename std::iterator<const_iterator>			const_iterator;
			// typedef typename std::reverse_iterator<iterator>		reverse_iterator;
			// typedef typename std::reverse_iterator<const_iterator>	const_reverse_iterator;

		private:

			value_type			*_arr;
			size_type			_arrSize;

			allocator_type		_alloc;
			size_type			_allocatedSize;
			const static int	allocSize = 10;

		public:

			explicit vector(const allocator_type& alloc = allocator_type()) {
				_alloc = alloc;
				_arrSize = 0;
				_allocatedSize = 0;
				_arr = _alloc.allocate(0);
				_alloc.construct(_arr, value_type());
				std::cout << "Construct default vector" << std::endl;
			}

			explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) {
				_alloc = alloc;
				_arrSize = n;
				_allocatedSize = ((_arrSize / allocSize) + 1) * allocSize;
				_arr = _alloc.allocate(_allocatedSize);
				for (size_type i=0; i<n; i++)
					_alloc.construct(&_arr[i], val);
				std::cout << "Construct size vector" << std::endl;
			}

			template <class InputIterator>
        	vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) {
				_alloc = alloc;
				_arrSize = std::distance(first, last);
				_allocatedSize = ((_arrSize / allocSize) + 1) * allocSize;
				_arr = _alloc.allocate(_allocatedSize);
				for (size_type i=0; i<_arrSize; i++)
					_alloc.construct(&_arr[i], *(first++));
				std::cout << "Construct iterator vector" << std::endl;
			}

			vector(const vector& x) {
				(void)x;
				std::cout << "Construct copy vector" << std::endl;
			}

			~vector(void) {
				_alloc.destroy(_arr);
				_alloc.deallocate(_arr, sizeof(value_type));
				std::cout << "Destroy vector" << std::endl;
			}

			//########################################################################

			value_type& operator[]( size_type pos ) {
				return _arr[pos];
			}

			const value_type& operator[]( size_type pos ) const {
				return _arr[pos];
			}

			//########################################################################

			void debug() {
				std::cout << "\n_arr: ";
				for (size_type i=0; i<_arrSize; i++)
					std::cout << _arr[i] << ", ";
				std::cout << "\n_arrSize: " << _arrSize << std::endl;
				std::cout << "_allocatedSize: " << _allocatedSize << std::endl;
				std::cout << std::endl;
			}
	};

	template <class T, class Alloc>
	bool operator==(const ft::vector<T, Alloc>& left, const ft::vector<T, Alloc>& right) {
		lexicographical_compare(left.first(), left.end(), right.first(), right.last())
	}

	template <class T, class Alloc>
	bool operator!=(const ft::vector<T, Alloc>& left, const ft::vector<T, Alloc>& right) {
		lexicographical_compare(left.first(), left.end(), right.first(), right.last())
	}

	template <class T, class Alloc>
	bool operator<( const ft::vector<T, Alloc>& left, const ft::vector<T, Alloc>& right) {
		lexicographical_compare(left.first(), left.end(), right.first(), right.last())
	}

	template <class T, class Alloc>
	bool operator>(const ft::vector<T, Alloc>& left, const ft::vector<T, Alloc>& right) {
		lexicographical_compare(left.first(), left.end(), right.first(), right.last())
	}

	template <class T, class Alloc>
	bool operator<=(const ft::vector<T, Alloc>& left, const ft::vector<T, Alloc>& right) {
		lexicographical_compare(left.first(), left.end(), right.first(), right.last())
	}

	template <class T, class Alloc>
	bool operator>=(const ft::vector<T, Alloc>& left, const ft::vector<T, Alloc>& right) {
		lexicographical_compare(left.first(), left.end(), right.first(), right.last())
	}

	template <class T, class Alloc>
	void swap(ft::vector<T, Alloc>& left, ft::vector<T, Alloc>& right) {
		ft::vector<T, Alloc> tmp(left);
		left = right;
		right = tmp;
	}
	
} // namespace ft

#endif