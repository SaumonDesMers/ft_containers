#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <iostream>

namespace ft
{

	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};

	template <class Iter>
	struct iterator_traits {

		typedef typename Iter::iterator_category	iterator_category;
		typedef typename Iter::value_type			value_type;
		typedef typename Iter::difference_type		difference_type;
		typedef typename Iter::pointer				pointer;
		typedef typename Iter::reference			reference;
	};

	template<typename T>
	struct iterator_traits<T*> {

		typedef random_access_iterator_tag	iterator_category;
		typedef T							value_type;
		typedef std::ptrdiff_t				difference_type;
		typedef T*							pointer;
		typedef T&							reference;
	};

	template<typename T>
	struct iterator_traits<const T*> {

		typedef random_access_iterator_tag	iterator_category;
		typedef T							value_type;
		typedef std::ptrdiff_t				difference_type;
		typedef const T*					pointer;
		typedef const T&					reference;
	};

	template <class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct iterator {

			typedef Category	iterator_category;
			typedef T			value_type;
			typedef Distance	difference_type;
			typedef Pointer		pointer;
			typedef Reference	reference;

		// private:

		// 	pointer _ptr;
		
		// public:

		// 	iterator(pointer const &ptr) { _ptr = ptr; }
		// 	iterator(iterator const &it) { _ptr = it._ptr; }
		// 	~iterator() {}
		// 	iterator operator=(iterator const &it) { _ptr = it._ptr; return *this; }

		// 	iterator operator++() { _ptr++; return *this; }
		// 	iterator operator++(int) { iterator old(*this); _ptr++; return old; }

		// 	bool operator==(iterator const &it) { return _ptr == it._ptr; }
		// 	bool operator!=(iterator const &it) { return _ptr != it._ptr; }

		// 	reference operator*() { return *_ptr; }
		// 	reference operator->() { return *_ptr; }
		// 	reference operator[](difference_type const &x) { return *(_ptr + x); }

		// 	iterator operator--() { _ptr--; return *this; }
		// 	iterator operator--(int) { iterator old(*this); _ptr--; return old; }

		// 	iterator operator+(difference_type const &x) { iterator ret(*this); ret._ptr += x; return ret; }
		// 	iterator operator-(difference_type const &x) { iterator ret(*this); ret._ptr -= x; return ret; }
		// 	iterator operator-(iterator const &it) { iterator ret(*this); ret._ptr -= it._ptr; return ret; }

		// 	bool operator<(iterator const &it) { return _ptr < it._ptr; }
		// 	bool operator>(iterator const &it) { return _ptr > it._ptr; }
		// 	bool operator<=(iterator const &it) { return _ptr <= it._ptr; }
		// 	bool operator>=(iterator const &it) { return _ptr >= it._ptr; }

		// 	iterator operator+=(difference_type const &x) { _ptr += x; return *this; }
		// 	iterator operator-=(difference_type const &x) { _ptr -= x; return *this; }
	};

	template <class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct const_iterator {

			typedef Category		iterator_category;
			typedef T				value_type;
			typedef Distance		difference_type;
			typedef Pointer			pointer;
			typedef const Reference	reference;

		// private:

		// 	pointer _ptr;
		
		// public:

		// 	const_iterator(pointer const &ptr) { _ptr = ptr; }
		// 	const_iterator(const_iterator const &it) { _ptr = it._ptr; }
		// 	~const_iterator() {}
		// 	const_iterator operator=(const_iterator const &it) { _ptr = it._ptr; return *this; }

		// 	const_iterator operator++() { _ptr++; return *this; }
		// 	const_iterator operator++(int) { const_iterator old(*this); _ptr++; return old; }

		// 	bool operator==(const_iterator const &it) { return _ptr == it._ptr; }
		// 	bool operator!=(const_iterator const &it) { return _ptr != it._ptr; }

		// 	reference operator*() { return *_ptr; }
		// 	reference operator->() { return *_ptr; }
		// 	reference operator[](difference_type const &x) { return *(_ptr + x); }

		// 	const_iterator operator--() { _ptr--; return *this; }
		// 	const_iterator operator--(int) { const_iterator old(*this); _ptr--; return old; }

		// 	const_iterator operator+(difference_type const &x) { const_iterator ret(*this); ret._ptr += x; return ret; }
		// 	const_iterator operator-(difference_type const &x) { const_iterator ret(*this); ret._ptr -= x; return ret; }
		// 	const_iterator operator-(const_iterator const &it) { const_iterator ret(*this); ret._ptr -= it._ptr; return ret; }

		// 	bool operator<(const_iterator const &it) { return _ptr < it._ptr; }
		// 	bool operator>(const_iterator const &it) { return _ptr > it._ptr; }
		// 	bool operator<=(const_iterator const &it) { return _ptr <= it._ptr; }
		// 	bool operator>=(const_iterator const &it) { return _ptr >= it._ptr; }

		// 	const_iterator operator+=(difference_type const &x) { _ptr += x; return *this; }
		// 	const_iterator operator-=(difference_type const &x) { _ptr -= x; return *this; }
	};

	template<class InputIt>
	typename iterator_traits<InputIt>::difference_type distance(InputIt first, InputIt last) {
		typename iterator_traits<InputIt>::difference_type retval=0;
		for (InputIt it=first; it!=last; it++)
			retval++;
		return retval;
	}
} // namespace ft

#endif