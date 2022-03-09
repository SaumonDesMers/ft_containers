#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include "iterator.hpp"
#include "reverse_iterator.hpp"
#include <iterator>
#include <exception>
#include "utils.hpp"
#include "other.hpp"

namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
	class vector {

		public:

			typedef T															value_type;
			typedef Alloc														allocator_type;
			typedef typename std::size_t										size_type;
			typedef typename std::ptrdiff_t										difference_type;
			typedef value_type&													reference;
			typedef const value_type&											const_reference;
			typedef typename Alloc::pointer										pointer;
			typedef typename Alloc::const_pointer								const_pointer;
			typedef T*															iterator;
			typedef const T*													const_iterator;
			typedef typename ft::reverse_iterator<iterator>						reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>				const_reverse_iterator;

		private:

			value_type			*_arr;
			size_type			_size;

			allocator_type		_alloc;
			size_type			_capacity;

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
				_capacity = src.size();
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
				_size = src.size();
				if (_capacity < src.size()) {
					_alloc.deallocate(_arr, _capacity);
					_capacity = src.capacity();
					_alloc = src.get_allocator();
					_arr = _alloc.allocate(_capacity);
				}
				else
					_alloc = src.get_allocator();
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
					+ itoa(pos) + ") >= this->size() (which is "
					+ itoa(_size) + ")");
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
					while (_size > count) {
						_alloc.destroy(&_arr[_size - 1]);
						_size--;
					}
					while (_size < count)
						_alloc.construct(&_arr[_size++], value);
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
				if (_size >= _capacity)
					reserve(_capacity == 0 ? 1 : _capacity * 2);
				_alloc.construct(&_arr[_size++], value);
			}

			void pop_back() {
				_alloc.destroy(&_arr[--_size]);
			}

			void swap(vector& other) {
				std::swap(_arr, other._arr);
				std::swap(_size, other._size);
				std::swap(_capacity, other._capacity);
				std::swap(_alloc, other._alloc);
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

			iterator insert(iterator pos, const value_type& value) {
				try {
					ft::vector<value_type, allocator_type> tmp(*this);
					iterator tmp_pos = tmp.begin() + ft::distance(begin(), pos);
					size_type idx= ft::distance(begin(), pos);
					if (_size + 1 > _capacity)
						reserve(_size * 2);
					clear();
					for (iterator it=tmp.begin(); it!=tmp_pos; it++)
						push_back(*it);
					push_back(value);
					for (iterator it=tmp_pos; it!=tmp.end(); it++)
						push_back(*it);

					return &_arr[idx];
				} catch (const std::exception& e) {
					throw std::length_error("vector::_M_fill_insert");
				}
			}

			void insert(iterator pos, size_type count, const value_type& value) {
				try {
					ft::vector<value_type, allocator_type> tmp(*this);
					iterator tmp_pos = tmp.begin() + ft::distance(begin(), pos);
					if (_size + count > _capacity)
						reserve(std::max(_size + count, _size * 2));
					clear();
					for (iterator it=tmp.begin(); it!=tmp_pos; it++)
						push_back(*it);
					for (size_type i=0; i<count; i++)
						push_back(value);
					for (iterator it=tmp_pos; it!=tmp.end(); it++)
						push_back(*it);
				} catch (const std::exception& e) {
					throw std::length_error("vector::_M_fill_insert");
				}
			}

			template<class InputIt>
			void insert(iterator pos, InputIt first, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type last) {
				try {
					ft::vector<value_type, allocator_type> tmp(*this);
					iterator tmp_pos = tmp.begin() + ft::distance(begin(), pos);
					size_type count = ft::distance(first, last);
					if (_size + count > _capacity)
						reserve(std::max(_size + count, _size * 2));
					clear();
					for (iterator it=tmp.begin(); it!=tmp_pos; it++)
						push_back(*it);
					for (InputIt it=first; it!=last; it++)
						push_back(*it);
					for (iterator it=tmp_pos; it!=tmp.end(); it++)
						push_back(*it);
				} catch (const std::exception& e) {
					throw std::length_error("vector::_M_fill_insert");
				}
			}

			iterator erase(iterator pos) {
				try {
					for (iterator it=pos; (it + 1)!=end(); it++) {
						_alloc.destroy(it);
						_alloc.construct(it, *(it + 1));
					}
					_size--;
					_alloc.destroy(&_arr[_size]);
					return pos;
				} catch (const std::exception& e) {
					throw;
				}
			}

			iterator erase(iterator first, iterator last) {
				try {
					// std::cout << "Erase [" << *first << "," << (last == end() ? "end" : *last) << ") = [" << (first - begin()) << "," << (last - begin()) << ")" << std::endl;
					size_type offset = ft::distance(first, last);
					for (iterator it=first; (it + offset)!=end(); it++) {
						_alloc.destroy(it);
						_alloc.construct(it, *(it + offset));
					}
					for (size_type i=0; i<offset; i++)
						_alloc.destroy(&_arr[--_size]);
					return first;
				} catch (const std::exception& e) {
					throw;
				}
			}

			iterator begin() { return iterator(_arr); }
			iterator end() { return iterator(&_arr[_size]); }

			const_iterator begin() const { return iterator(_arr); }
			const_iterator end() const { return iterator(&_arr[_size]); }

			reverse_iterator rbegin() { return reverse_iterator(&_arr[_size]); }
			reverse_iterator rend() { return reverse_iterator(_arr); }

			const_reverse_iterator rbegin() const { return const_reverse_iterator(&_arr[_size]); }
			const_reverse_iterator rend() const { return const_reverse_iterator(_arr); }

	};

	template <class T, class Alloc>
	bool operator==(const ft::vector<T, Alloc>& left, const ft::vector<T, Alloc>& right) {
		bool flag = left.size() == right.size();
		return (flag && left.size() == 0) || (flag && ft::equal(left.begin(), left.end(), right.begin()));
	}

	template <class T, class Alloc>
	bool operator!=(const ft::vector<T, Alloc>& left, const ft::vector<T, Alloc>& right) { return !(left == right); }

	template <class T, class Alloc>
	bool operator<(const ft::vector<T, Alloc>& left, const ft::vector<T, Alloc>& right) { return ft::lexicographical_compare(left.begin(), left.end(), right.begin(), right.end()); }

	template <class T, class Alloc>
	bool operator>(const ft::vector<T, Alloc>& left, const ft::vector<T, Alloc>& right) { return ft::lexicographical_compare(right.begin(), right.end(), left.begin(), left.end()); }

	template <class T, class Alloc>
	bool operator<=(const ft::vector<T, Alloc>& left, const ft::vector<T, Alloc>& right) { return !(left>right); }

	template <class T, class Alloc>
	bool operator>=(const ft::vector<T, Alloc>& left, const ft::vector<T, Alloc>& right) { return !(left<right); }

	template <class T, class Alloc>
	void swap(ft::vector<T, Alloc>& left, ft::vector<T, Alloc>& right) { left.swap(right); }
	
} // namespace ft

#endif