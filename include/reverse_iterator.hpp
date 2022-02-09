#ifndef ITERATOR_REVERSE_HPP
#define ITERATOR_REVERSE_HPP

#include <iostream>

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

			pointer _ptr;

		public:

			pointer ptr() const { return _ptr; }
		
			reverse_iterator(iterator_type const &it) { _ptr = it - 1; }
			template <class Iter>
			reverse_iterator (reverse_iterator<Iter> const &rev_it) : _ptr(rev_it.ptr()) {}
			~reverse_iterator() {}
			reverse_iterator operator=(reverse_iterator const &rev_it) { _ptr = rev_it._ptr; return *this; }

			iterator_type base() const { return iterator_type(_ptr); }

			reverse_iterator operator++() { _ptr--; return *this; }
			reverse_iterator operator++(int) { reverse_iterator old(*this); _ptr--; return old; }

			bool operator==(reverse_iterator const &rev_it) { return _ptr == rev_it._ptr; }
			bool operator!=(reverse_iterator const &rev_it) { return _ptr != rev_it._ptr; }

			reference operator*() { return *_ptr; }
			reference operator->() { return *_ptr; }
			reference operator[](difference_type const &x) { return *(_ptr + x); }

			reverse_iterator operator--() { _ptr++; return *this; }
			reverse_iterator operator--(int) { reverse_iterator old(*this); _ptr++; return old; }

			reverse_iterator operator+(difference_type const &x) { reverse_iterator ret(*this); ret._ptr -= x; return ret; }
			reverse_iterator operator-(difference_type const &x) { reverse_iterator ret(*this); ret._ptr += x; return ret; }
			reverse_iterator operator-(reverse_iterator const &rev_it) { reverse_iterator ret(*this); ret._ptr += rev_it; return ret; }

			bool operator<(reverse_iterator const &rev_it) { return _ptr > rev_it._ptr; }
			bool operator>(reverse_iterator const &rev_it) { return _ptr < rev_it._ptr; }
			bool operator<=(reverse_iterator const &rev_it) { return _ptr >= rev_it._ptr; }
			bool operator>=(reverse_iterator const &rev_it) { return _ptr <= rev_it._ptr; }

			reverse_iterator operator+=(difference_type const &x) { _ptr += x; return *this; }
			reverse_iterator operator-=(difference_type const &x) { _ptr -= x; return *this; }
	};

} // namespace ft

#endif