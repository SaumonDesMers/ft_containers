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
	};

	template <class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct const_iterator {

			typedef Category		iterator_category;
			typedef T				value_type;
			typedef Distance		difference_type;
			typedef Pointer			pointer;
			typedef const Reference	reference;
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