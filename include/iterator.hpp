#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <iostream>

namespace ft
{

	template <class Iter>
	struct iterator_traits {

		typedef typename Iter::iterator_category	iterator_category;
		typedef typename Iter::value_type			value_type;
		typedef typename Iter::difference_type		difference_type;
		typedef typename Iter::pointer				pointer;
		typedef typename Iter::reference			reference;
	};

	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};

	template <class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct iterator {

			typedef Category	iterator_category;
			typedef T			value_type;
			typedef Distance	difference_type;
			typedef Pointer		pointer;
			typedef Reference	reference;

		private:

			pointer _ptr;

	};

	// template <class Category, class T, class Distance, class Pointer, class Reference>
	// struct iterator<bidirectional_iterator_tag, T, std::ptrdiff_t, T*, T&> {

	// 		typedef Category	iterator_category;
	// 		typedef T			value_type;
	// 		typedef Distance	difference_type;
	// 		typedef Pointer		pointer;
	// 		typedef Reference	reference;

	// 	private:

	// 		pointer _ptr;

	// 		iterator(pointer ptr) { _ptr = ptr; }
	// 		iterator(iterator const &it) { _ptr = it._ptr; }
	// 		~iterator() {}
	// 		iterator operator=(iterator const &it) { _ptr = it._ptr; return *this; }

	// 		iterator operator++() { _ptr++; return *this; }
	// 		iterator operator++(int) { iterator old(*this); _ptr++; return old; }

	// 		bool operator==(iterator const &it) { return _ptr == it._ptr; }
	// 		bool operator!=(iterator const &it) { return _ptr != it._ptr; }

	// 		reference operator*() { return *_ptr; }
	// 		reference operator->() { return *_ptr; }

	// 		iterator operator--() { _ptr--; return *this; }
	// 		iterator operator--(int) { iterator old(*this); _ptr--; return old; }


	// };

	// template <class T>
	// struct iterator<random_access_iterator_tag, T> {

	// 		iterator(pointer const &ptr) { _ptr = ptr; }
	// 		iterator(iterator const &it) { _ptr = it._ptr; }
	// 		~iterator() {}
	// 		iterator operator=(iterator const &it) { _ptr = it._ptr; return *this; }

	// 		iterator operator++() { _ptr++; return *this; }
	// 		iterator operator++(int) { iterator old(*this); _ptr++; return old; }

	// 		bool operator==(iterator const &it) { return _ptr == it._ptr; }
	// 		bool operator!=(iterator const &it) { return _ptr != it._ptr; }

	// 		reference operator*() { return *_ptr; }
	// 		reference operator->() { return *_ptr; }
	// 		reference operator[](difference_type const &x) { return *(_ptr + x); }

	// 		iterator operator--() { _ptr--; return *this; }
	// 		iterator operator--(int) { iterator old(*this); _ptr--; return old; }

	// 		iterator operator+(difference_type const &x) { iterator ret(*this); ret._ptr += x; return ret; }
	// 		iterator operator-(difference_type const &x) { iterator ret(*this); ret._ptr -= x; return ret; }
	// 		iterator operator-(iterator const &it) { iterator ret(*this); ret._ptr -= it._ptr; return ret; }

	// 		bool operator<(iterator const &it) { return _ptr < it._ptr; }
	// 		bool operator>(iterator const &it) { return _ptr > it._ptr; }
	// 		bool operator<=(iterator const &it) { return _ptr <= it._ptr; }
	// 		bool operator>=(iterator const &it) { return _ptr >= it._ptr; }

	// 		iterator operator+=(difference_type const &x) { _ptr += x; return *this; }
	// 		iterator operator-=(difference_type const &x) { _ptr -= x; return *this; }

	// };

} // namespace ft

#endif