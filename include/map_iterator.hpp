#ifndef MAP_ITERATOR_HPP
#define MAP_ITERATOR_HPP

#include <iostream>
#include <utils.hpp>

namespace ft
{

	template <class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct map_iterator {

			typedef Category	iterator_category;
			typedef T			value_type;
			typedef Distance	difference_type;
			typedef Pointer		pointer;
			typedef Reference	reference;

		private:

			pointer _ptr;

		public:

			map_iterator(pointer const &ptr = pointer()) : _ptr(ptr) {}
			map_iterator (map_iterator const &mit) :_ptr(mit._ptr) {}
			~map_iterator() {}
			map_iterator operator=(map_iterator const &mit) { _ptr = mit._ptr; return *this; }

			map_iterator operator++() { _ptr++; return *this; }
			map_iterator operator++(int) { return map_iterator(_ptr++); }

			bool operator==(map_iterator const &mit) { return _ptr == mit._ptr; }
			bool operator!=(map_iterator const &mit) { return _ptr != mit._ptr; }

			reference operator*() { return *_ptr; }
			pointer operator->() { return &(operator*()); }

			map_iterator operator--() { _ptr--; return *this; }
			map_iterator operator--(int) { return map_iterator(_ptr--); }

	};

} // namespace ft

#endif