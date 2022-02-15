#ifndef AVL_ITERATOR_HPP
#define AVL_ITERATOR_HPP

#include <iostream>
#include <utils.hpp>

namespace ft
{

	template <class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct avl_iterator {

			typedef Category	iterator_category;
			typedef T			value_type;
			typedef Distance	difference_type;
			typedef Pointer		pointer;
			typedef Reference	reference;

		private:

			pointer _it;

		public:

			avl_iterator(iterator_type const &it = iterator_type()) { _it = it - 1; }
			template <class Iter>
			avl_iterator (avl_iterator<Iter> const &rit) { _it = const_cast<iterator_type>(rit.base() - 1); }
			~avl_iterator() {}
			avl_iterator operator=(avl_iterator const &rit) { _it = rit._it; return *this; }

			iterator_type base() const { return iterator_type(_it + 1); }

			avl_iterator operator++() { _it--; return *this; }
			avl_iterator operator++(int) { avl_iterator old(*this); _it--; return old; }

			bool operator==(avl_iterator const &rit) { return _it == rit._it; }
			bool operator!=(avl_iterator const &rit) { return _it != rit._it; }

			reference operator*() { return *_it; }
			pointer operator->() { return &(operator*()); }
			reference operator[](difference_type const &x) { return *(_it - x); }

			avl_iterator operator--() { _it++; return *this; }
			avl_iterator operator--(int) { avl_iterator old(*this); _it++; return old; }

			avl_iterator operator+(difference_type const &x) { avl_iterator ret(*this); ret._it -= x; return ret; }
			avl_iterator operator-(difference_type const &x) { avl_iterator ret(*this); ret._it += x; return ret; }
			difference_type operator-(avl_iterator const &rit) { difference_type ret = rit._it - _it; return ret; }

			avl_iterator operator+=(difference_type const &x) { _it -= x; return *this; }
			avl_iterator operator-=(difference_type const &x) { _it += x; return *this; }
	};

	// template<class It1, class It2>
	// bool operator<(avl_iterator<It1> const &lhs, avl_iterator<It2> const &rhs) { return lhs.base() > rhs.base(); }

	// template<class It1, class It2>
	// bool operator>(avl_iterator<It1> const &lhs, avl_iterator<It2> const &rhs) { return lhs.base() < rhs.base(); }

	// template<class It1, class It2>
	// bool operator<=(avl_iterator<It1> const &lhs, avl_iterator<It2> const &rhs) { return lhs.base() >= rhs.base(); }

	// template<class It1, class It2>
	// bool operator>=(avl_iterator<It1> const &lhs, avl_iterator<It2> const &rhs) { return lhs.base() <= rhs.base(); }


	// template<class Type, class It>
	// avl_iterator<It> operator+(Type const &x, avl_iterator<It> const &rit) {
	// 	avl_iterator<It> ret(rit);
	// 	for (Type i=0; i<x; i++)
	// 		ret++;
	// 	return ret;
	// }

	// template<class It, class Type>
	// avl_iterator<It> operator-(typename ft::enable_if<ft::is_integral<Type>::value, Type>::type const &x, avl_iterator<It> const &rit) {
	// 	avl_iterator<It> ret(rit);
	// 	for (Type i=0; i<x; i++)
	// 		ret--;
	// 	return ret;
	// }

} // namespace ft

#endif