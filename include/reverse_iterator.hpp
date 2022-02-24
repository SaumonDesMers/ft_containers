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

			iterator_type _it;

		public:

			reverse_iterator(iterator_type const &it = iterator_type()) { _it = it; _it--; }
			template <class Iter>
			reverse_iterator (reverse_iterator<Iter> const &rit) { _it = const_cast<iterator_type>(rit.base()); _it--; }
			~reverse_iterator() {}
			reverse_iterator operator=(reverse_iterator const &rit) { _it = rit._it; return *this; }

			iterator_type base() const { iterator_type ret = _it; ret++; return ret; }

			reverse_iterator operator++() { _it--; return *this; }
			reverse_iterator operator++(int) { reverse_iterator old(*this); _it--; return old; }

			bool operator==(reverse_iterator const &rit) { return _it == rit._it; }
			bool operator!=(reverse_iterator const &rit) { return _it != rit._it; }

			reference operator*() { return *_it; }
			pointer operator->() { return &(operator*()); }
			reference operator[](difference_type const &x) { return *(_it - x); }

			reverse_iterator operator--() { _it++; return *this; }
			reverse_iterator operator--(int) { reverse_iterator old(*this); _it++; return old; }

			reverse_iterator operator+(difference_type const &x) { reverse_iterator ret(*this); ret._it -= x; return ret; }
			reverse_iterator operator-(difference_type const &x) { reverse_iterator ret(*this); ret._it += x; return ret; }
			difference_type operator-(reverse_iterator const &rit) { difference_type ret = rit._it - _it; return ret; }

			reverse_iterator operator+=(difference_type const &x) { _it -= x; return *this; }
			reverse_iterator operator-=(difference_type const &x) { _it += x; return *this; }
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