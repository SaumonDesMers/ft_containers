#ifndef MAP_ITERATOR_HPP
#define MAP_ITERATOR_HPP

#include <iostream>
#include "utils.hpp"
#include "map.hpp"

namespace ft
{

	template <class Key, class Type, class Traits, class Allocator>
	class map;

	template <class Node, class Value, class Traits, class Allocator>
	struct map_iterator {

			typedef bidirectional_iterator_tag					iterator_category;
			typedef Node										node_type;
			typedef Value										value_type;
			typedef typename node_type::map_type				map_type;
			typedef typename node_type::key_type				key_type;
			typedef typename node_type::mapped_type				mapped_type;
			typedef typename std::ptrdiff_t						difference_type;
			typedef Node*										node_pointer;
			typedef Node&										node_reference;
			typedef Traits										key_compare;
			typedef value_type*									pointer;
			typedef const value_type*							const_pointer;
			typedef value_type&									reference;
			typedef const value_type&							const_reference;

			typedef typename map_type::const_iterator			const_iterator;

		private:

			node_pointer 	_node;
			key_compare		_comp;

		public:

			map_iterator(node_pointer const ptr = node_pointer())
				: _node(ptr), _comp(key_compare()) {}
			
			map_iterator(map_iterator const &it)
				: _node(it._node), _comp(key_compare()) {}
			
			~map_iterator() {}

			map_iterator operator=(map_iterator const &it) {
				_node = it._node;
				_comp = it._comp;
				return *this;
			}

			bool operator==(map_iterator const &it) const { return _node == it._node; }
			bool operator!=(map_iterator const &it) const { return _node != it._node; }

			reference operator*() { return _node->value; }
			const_reference operator*() const { return _node->value; }
			pointer operator->() { return &(operator*()); }
			const_pointer operator->() const { return &(operator*()); }

			map_iterator &operator++() {
				if (_node->right) {
					_node = _node->right;
					while (_node->left)
						_node = _node->left;
				}
				else if (_node->type != node_type::END && _node->parent) {
					key_type key = _node->value.first;
					while (_node->parent && _comp(_node->parent->value.first, key))
						_node = _node->parent;
					_node = _node->parent;
				}
				return *this;
			}

			map_iterator operator++(int) {
				node_pointer tmp = _node;
				if (_node->right) {
					_node = _node->right;
					while (_node->left)
						_node = _node->left;
				}
				else if (_node->type != node_type::END && _node->parent) {
					key_type key = _node->value.first;
					while (_node->parent && _comp(_node->parent->value.first, key))
						_node = _node->parent;
					_node = _node->parent;
				}
				return map_iterator(tmp);
			}

			map_iterator &operator--() {
				if (_node->left) {
					_node = _node->left;
					while (_node->right)
						_node = _node->right;
				}
				else if (_node->type != node_type::REND && _node->parent) {
					key_type key = _node->value.first;
					while (_node->parent && _comp(key, _node->parent->value.first) && _node->type == node_type::NODE)
						_node = _node->parent;
					_node = _node->parent;
				}
				return *this;
			}

			map_iterator operator--(int) {
				node_pointer tmp = _node;
				if (_node->left) {
					_node = _node->left;
					while (_node->right)
						_node = _node->right;
				}
				else if (_node->type != node_type::REND && _node->parent) {
					key_type key = _node->value.first;
					while (_node->parent && _comp(key, _node->parent->value.first) && _node->type == node_type::NODE)
						_node = _node->parent;
					_node = _node->parent;
				}
				return map_iterator(tmp);
			}

			operator const_iterator() const {
				const_iterator ret(_node);
				return ret;
			}

	};
	template <class Node, class Value, class Traits, class Allocator>
	struct const_map_iterator {

			typedef bidirectional_iterator_tag					iterator_category;
			typedef Node										node_type;
			typedef Value										value_type;
			typedef typename node_type::map_type				map_type;
			typedef typename node_type::key_type				key_type;
			typedef typename node_type::mapped_type				mapped_type;
			typedef typename std::ptrdiff_t						difference_type;
			typedef Node*										node_pointer;
			typedef Node&										node_reference;
			typedef Traits										key_compare;
			typedef value_type*									pointer;
			typedef const value_type*							const_pointer;
			typedef value_type&									reference;
			typedef const value_type&							const_reference;

			typedef typename map_type::const_iterator			const_iterator;

			typedef typename std::allocator<value_type>			alloc_type;

		private:

			node_pointer 	_node;
			key_compare		_comp;
			mutable value_type		_value;
			alloc_type _alloc;

			reference value() {
				_alloc.destroy(&_value);
				if (_node)
					_alloc.construct(&_value, _node->value);
				return _value;
			}

		public:

			const_map_iterator(node_pointer const ptr = node_pointer())
				: _node(ptr), _comp(key_compare()), _value(value_type()), _alloc(alloc_type()) { value(); }
			
			const_map_iterator(const_map_iterator const &it)
				: _node(it._node), _comp(key_compare()) { value(); }
			
			~const_map_iterator() {}

			const_map_iterator operator=(const_map_iterator const &it) {
				_node = it._node;
				_comp = it._comp;
				value();
				return *this;
			}

			bool operator==(const_map_iterator const &it) const { return _node == it._node; }
			bool operator!=(const_map_iterator const &it) const { return _node != it._node; }

			reference operator*() { return _value; }
			const_reference operator*() const { return _value; }
			pointer operator->() { return &(operator*()); }
			const_pointer operator->() const { return &(operator*()); }

			const_map_iterator &operator++() {
				if (_node->right) {
					_node = _node->right;
					while (_node->left)
						_node = _node->left;
				}
				else if (_node->type != node_type::END && _node->parent) {
					key_type key = _node->value.first;
					while (_node->parent && _comp(_node->parent->value.first, key))
						_node = _node->parent;
					_node = _node->parent;
				}
				value();
				return *this;
			}

			const_map_iterator operator++(int) {
				node_pointer tmp = _node;
				if (_node->right) {
					_node = _node->right;
					while (_node->left)
						_node = _node->left;
				}
				else if (_node->type != node_type::END && _node->parent) {
					key_type key = _node->value.first;
					while (_node->parent && _comp(_node->parent->value.first, key))
						_node = _node->parent;
					_node = _node->parent;
				}
				value();
				return const_map_iterator(tmp);
			}

			const_map_iterator &operator--() {
				if (_node->left) {
					_node = _node->left;
					while (_node->right)
						_node = _node->right;
				}
				else if (_node->type != node_type::REND && _node->parent) {
					key_type key = _node->value.first;
					while (_node->parent && _comp(key, _node->parent->value.first) && _node->type == node_type::NODE)
						_node = _node->parent;
					_node = _node->parent;
				}
				value();
				return *this;
			}

			const_map_iterator operator--(int) {
				node_pointer tmp = _node;
				if (_node->left) {
					_node = _node->left;
					while (_node->right)
						_node = _node->right;
				}
				else if (_node->type != node_type::REND && _node->parent) {
					key_type key = _node->value.first;
					while (_node->parent && _comp(key, _node->parent->value.first) && _node->type == node_type::NODE)
						_node = _node->parent;
					_node = _node->parent;
				}
				value();
				return const_map_iterator(tmp);
			}

	};
	template <class Iterator>
	struct map_reverse_iterator {

			typedef Iterator 												iterator_type;
			typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename iterator_traits<Iterator>::value_type			value_type;
			typedef typename iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename iterator_traits<Iterator>::pointer				pointer;
			typedef typename iterator_traits<Iterator>::reference			reference;
			typedef const value_type&										const_reference;
			typedef const value_type*										const_pointer;

		private:

			iterator_type _it;

		public:

			map_reverse_iterator() : _it(iterator_type()) {}
			map_reverse_iterator(iterator_type const &it) : _it(it) { _it--; }
			template <class Iter>
			map_reverse_iterator (map_reverse_iterator<Iter> const &rit) : _it(rit.base()) { _it--; }
			~map_reverse_iterator() {}
			map_reverse_iterator operator=(map_reverse_iterator const &rit) { _it = rit._it; return *this; }

			iterator_type base() const { iterator_type ret = _it; ret++; return ret; }

			map_reverse_iterator operator++() { _it--; return *this; }
			map_reverse_iterator operator++(int) { map_reverse_iterator old(*this); _it--; return old; }

			bool operator==(map_reverse_iterator const &rit) { return _it == rit._it; }
			bool operator!=(map_reverse_iterator const &rit) { return _it != rit._it; }

			reference operator*() { return *_it; }
			const_reference operator*() const { return *_it; }
			pointer operator->() { return &(operator*()); }
			const_pointer operator->() const { return &(operator*()); }

			map_reverse_iterator operator--() { _it++; return *this; }
			map_reverse_iterator operator--(int) { map_reverse_iterator old(*this); _it++; return old; }

	};

} // namespace ft

#endif