#ifndef ITERATOR_REVERSE_HPP
#define ITERATOR_REVERSE_HPP

#include <iostream>
#include <utils.hpp>

namespace ft
{

	template <class Iterator>
	struct reverse_iterator {

			typedef Iterator 												iterator_type;
			typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename iterator_traits<Iterator>::value_type			value_type;
			typedef typename iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename iterator_traits<Iterator>::pointer				pointer;
			typedef typename iterator_traits<Iterator>::reference			reference;

		private:

			iterator_type _ptr;

		public:

			reverse_iterator(iterator_type const &it = iterator_type()) { _ptr = it - 1; }
			template <class Iter>
			reverse_iterator (reverse_iterator<Iter> const &rit) { _ptr = const_cast<iterator_type>(rit.base() - 1); }
			~reverse_iterator() {}
			reverse_iterator operator=(reverse_iterator const &rit) { _ptr = rit._ptr; return *this; }

			iterator_type base() const { return iterator_type(_ptr + 1); }

			reverse_iterator operator++() { _ptr--; return *this; }
			reverse_iterator operator++(int) { reverse_iterator old(*this); _ptr--; return old; }

			bool operator==(reverse_iterator const &rit) { return _ptr == rit._ptr; }
			bool operator!=(reverse_iterator const &rit) { return _ptr != rit._ptr; }

			reference operator*() { return *_ptr; }
			pointer operator->() { return &(operator*()); }
			reference operator[](difference_type const &x) { return *(_ptr - x); }

			reverse_iterator operator--() { _ptr++; return *this; }
			reverse_iterator operator--(int) { reverse_iterator old(*this); _ptr++; return old; }

			reverse_iterator operator+(difference_type const &x) { reverse_iterator ret(*this); ret._ptr -= x; return ret; }
			reverse_iterator operator-(difference_type const &x) { reverse_iterator ret(*this); ret._ptr += x; return ret; }
			difference_type operator-(reverse_iterator const &rit) { difference_type ret = rit._ptr - _ptr; return ret; }

			reverse_iterator operator+=(difference_type const &x) { _ptr -= x; return *this; }
			reverse_iterator operator-=(difference_type const &x) { _ptr += x; return *this; }
	};

	template<class It1, class It2>
	bool operator<(reverse_iterator<It1> const &lhs, reverse_iterator<It2> const &rhs) { return lhs.base() > rhs.base(); }

	template<class It1, class It2>
	bool operator>(reverse_iterator<It1> const &lhs, reverse_iterator<It2> const &rhs) { return lhs.base() < rhs.base(); }

	template<class It1, class It2>
	bool operator<=(reverse_iterator<It1> const &lhs, reverse_iterator<It2> const &rhs) { return lhs.base() >= rhs.base(); }

	template<class It1, class It2>
	bool operator>=(reverse_iterator<It1> const &lhs, reverse_iterator<It2> const &rhs) { return lhs.base() <= rhs.base(); }


	template<class Type, class It>
	reverse_iterator<It> operator+(Type const &x, reverse_iterator<It> const &rit) {
		reverse_iterator<It> ret(rit);
		for (Type i=0; i<x; i++)
			ret++;
		return ret;
	}

	// template<class It, class Type>
	// reverse_iterator<It> operator-(typename ft::enable_if<ft::is_integral<Type>::value, Type>::type const &x, reverse_iterator<It> const &rit) {
	// 	reverse_iterator<It> ret(rit);
	// 	for (Type i=0; i<x; i++)
	// 		ret--;
	// 	return ret;
	// }

} // namespace ft

#endif