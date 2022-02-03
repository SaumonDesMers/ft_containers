#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <iterator.hpp>
#include <iterator>
#include <exception>
#include <utils.hpp>

namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
	class vector {

		public:

			typedef T														value_type;
			typedef Alloc													allocator_type;
			typedef typename std::size_t									size_type;
			typedef typename std::ptrdiff_t									difference_type;
			typedef value_type&												reference;
			typedef const value_type&										const_reference;
			typedef typename Alloc::pointer									pointer;
			typedef typename Alloc::const_pointer							const_pointer;
			// typedef typename ft::iterator<random_access_iterator_tag, T>	iterator;
			typedef T*	iterator;
			// typedef typename ft::iterator<const_iterator>					const_iterator;
			// typedef typename ft::reverse_iterator<iterator>					reverse_iterator;
			// typedef typename ft::reverse_iterator<const_iterator>			const_reverse_iterator;

		private:

			value_type			*_arr;
			size_type			_size;

			allocator_type		_alloc;
			size_type			_capacity;

			size_type _getNeededCapacity(size_type size) {
				size_type capacity = 1;
				while (capacity < size)
					capacity *= 2;
				return capacity;
			}

		public:

			explicit vector(const allocator_type& alloc = allocator_type()) {
				_alloc = alloc;
				_size = 0;
				_capacity = 0;
				_arr = _alloc.allocate(_capacity);
				// _alloc.construct(_arr, value_type());
			}

			explicit vector(size_type n, const_reference val = value_type(), const allocator_type& alloc = allocator_type()) {
				_alloc = alloc;
				_size = n;
				_capacity = _size;
				_arr = _alloc.allocate(_capacity);
				for (size_type i=0; i<_size; i++)
					_alloc.construct(&_arr[i], val);
			}

			template <class It>
        	vector(It first, typename ft::enable_if<!ft::is_integral<It>::value, It>::type last, const allocator_type& alloc = allocator_type()) {
				_alloc = alloc;
				_size = std::distance(first, last);
				_capacity = _size;
				_arr = _alloc.allocate(_capacity);
				for (size_type i=0; i<_size; i++)
					_alloc.construct(&_arr[i], *(first++));
			}

			vector(const vector& src) {
				_size = src.size();
				_capacity = src.capacity();
				_alloc = src.get_allocator();
				_arr = _alloc.allocate(_capacity);
				for (size_type i=0; i<_size; i++)
					_alloc.construct(&_arr[i], src[i]);
			}

			~vector(void) {
				clear();
				_alloc.deallocate(_arr, _capacity);
			}

			vector& operator=(const vector& src) {
				clear();
				_alloc.deallocate(_arr, _capacity);
				_size = src.size();
				_capacity = src.capacity();
				_alloc = src.get_allocator();
				_arr = _alloc.allocate(_capacity);
				for (size_type i=0; i<_size; i++)
					_alloc.construct(&_arr[i], src[i]);
				return *this;
			}

			//###########################################################

			size_type size() const { return _size; }

			bool empty() const { return _size == 0; }

			size_type capacity() const { return _capacity; }

			size_type max_size() const { return _alloc.max_size(); }

			allocator_type get_allocator() const { return _alloc; }

			//###########################################################

			reference operator[](size_type pos) { return _arr[pos]; }

			const_reference operator[](size_type pos) const { return _arr[pos]; }

			reference at(size_type pos) {
				std::string str;
				if (pos < 0 || pos > _size)
					throw std::out_of_range("vector::_M_range_check: __n (which is "
					+ stoa(pos) + ") >= this->size() (which is "
					+ stoa(_size) + ")");
				return _arr[pos];
			}

			const_reference at(size_type pos) const {
				if (pos < 0 || pos > _size)
					throw std::out_of_range("vector::at");
				return _arr[pos];
			}

			reference front() { return _arr[0]; }

			const_reference front() const { return _arr[0]; }

			reference back() { return _arr[_size - 1]; }

			const_reference back() const { return _arr[_size - 1]; }

			T* data();

			const T* data() const;

			//###########################################################

			void reserve(size_type new_cap) {
				if (new_cap > max_size())
					throw std::length_error("vector::reserve");
				else if (new_cap > _capacity) {
					vector tmp = *this;
					clear();
					_alloc.deallocate(_arr, _capacity);
					_capacity = new_cap;
					_arr = _alloc.allocate(_capacity);
					_size = tmp.size();
					for (size_type i=0; i<tmp.size(); i++)
						_alloc.construct(&_arr[i], tmp[i]);
				}
			}

			void resize(size_type count, value_type value = value_type()) {
				try {
					if (count > _capacity)
						reserve(std::max(_size * 2, count));
					while (_size < count) {
						_alloc.destroy(&_arr[_size]);
						_alloc.construct(&_arr[_size++], value);
					}
					_size = count;
				} catch (const std::exception& e) {
					throw std::length_error("vector::_M_fill_insert");
				}
			}

			void clear() {
				for (size_type i=0; i<_size; i++)
					_alloc.destroy(&_arr[i]);
				_size = 0;
			}

			//###########################################################

			void push_back(const_reference value) {
				if (_size == _capacity)
					reserve(_capacity == 0 ? 1 : _capacity * 2);
				_alloc.construct(&_arr[_size++], value);
			}

			void pop_back() {
				_alloc.destroy(&_arr[--_size]);
			}

			void swap(vector& other) {
				ft::vector<value_type, allocator_type> tmp(*this);
				*this = other;
				other = tmp;
			}

			void assign(size_type count, const_reference value) {
				try {
					if (count > _capacity)
						reserve(count);
					clear();
					for (size_type i=0; i<count; i++)
						_alloc.construct(&_arr[i], value);
					_size = count;
				} catch (const std::exception& e) {
					throw std::length_error("cannot create std::vector larger than max_size()");
				}
			}

			template<class It>
			void assign(It first, typename ft::enable_if<!ft::is_integral<It>::value, It>::type last) {
				try {
					size_type count = std::distance(first, last);
					if (count > _capacity)
						reserve(count);
					clear();
					for (It it=first; it!=last; it++)
						_alloc.construct(&_arr[_size++], *it);
				} catch (const std::exception& e) {
					throw std::length_error("cannot create std::vector larger than max_size()");
				}
			}

			// iterator insert(iterator pos, const value_type& value) {
			// 	try {
			// 		if (_size + 1 > _capacity)
			// 			reserve(_size * 2);
			// 		for (iterator it=pos; it!=end(); it++)

			// 		_size++;
			// 	} catch (const std::exception& e) {
			// 		throw std::length_error("vector::_M_fill_insert");
			// 	}
			// }

			// void insert(iterator pos, size_type count, const T& value) {

			// }

			// template<class InputIt>
			// void insert(iterator pos, InputIt first, InputIt last) {

			// }

			iterator begin() { return iterator(_arr); }

			iterator end() { return iterator(&_arr[_size]); }

	};

	template <class T, class Alloc>
	bool operator==(const ft::vector<T, Alloc>& left, const ft::vector<T, Alloc>& right) {
		return lexicographical_compare(left.first(), left.end(), right.first(), right.last());
	}

	template <class T, class Alloc>
	bool operator!=(const ft::vector<T, Alloc>& left, const ft::vector<T, Alloc>& right) {
		return lexicographical_compare(left.first(), left.end(), right.first(), right.last());
	}

	template <class T, class Alloc>
	bool operator<(const ft::vector<T, Alloc>& left, const ft::vector<T, Alloc>& right) {
		return lexicographical_compare(left.first(), left.end(), right.first(), right.last());
	}

	template <class T, class Alloc>
	bool operator>(const ft::vector<T, Alloc>& left, const ft::vector<T, Alloc>& right) {
		return lexicographical_compare(left.first(), left.end(), right.first(), right.last());
	}

	template <class T, class Alloc>
	bool operator<=(const ft::vector<T, Alloc>& left, const ft::vector<T, Alloc>& right) {
		return lexicographical_compare(left.first(), left.end(), right.first(), right.last());
	}

	template <class T, class Alloc>
	bool operator>=(const ft::vector<T, Alloc>& left, const ft::vector<T, Alloc>& right) {
		return lexicographical_compare(left.first(), left.end(), right.first(), right.last());
	}

	template <class T, class Alloc>
	void swap(ft::vector<T, Alloc>& left, ft::vector<T, Alloc>& right) {
		ft::vector<T, Alloc> tmp(left);
		left = right;
		right = tmp;
	}
	
} // namespace ft

#endif