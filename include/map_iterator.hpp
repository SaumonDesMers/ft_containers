#ifndef MAP_ITERATOR_HPP
#define MAP_ITERATOR_HPP

#include <iostream>
#include <utils.hpp>
#include <map.hpp>

namespace ft
{

	template <class Key, class Type, class Traits, class Allocator>
	class map;

	template <class T, class Key, class Type, class Traits, class Allocator>
	struct map_iterator {

			typedef bidirectional_iterator_tag									iterator_category;
			typedef T															node_type;
			typedef typename node_type::value_type								value_type;
			typedef typename std::ptrdiff_t										difference_type;
			typedef T*															node_pointer;
			typedef T&															node_reference;
			typedef typename ft::map<Key, Type, Traits, Allocator>::key_compare	key_compare;
			typedef value_type*													pointer;
			typedef value_type&													reference;


		private:

			node_pointer 	_node;
			key_compare		_comp;
			node_pointer	_leaf;

		public:

			map_iterator(node_pointer const &ptr = node_pointer(), node_pointer leaf = NULL)
				: _node(ptr), _comp(key_compare()), _leaf(leaf) {}
			
			map_iterator (map_iterator const &mit)
				: _node(mit._node), _comp(key_compare()), _leaf(mit._leaf) {}
			
			~map_iterator() {}

			map_iterator operator=(map_iterator const &mit) { _node = mit._node; return *this; }

			bool operator==(map_iterator const &mit) { return _node == mit._node; }
			bool operator!=(map_iterator const &mit) { return _node != mit._node; }

			value_type& operator*() { return _node->value; }
			value_type* operator->() { return &(operator*()); }

			map_iterator operator++() {
				if (_node->right != _leaf) {
					_node = _node->right;
					while (_node->left != _leaf)
						_node = _node->left;
				}
				else {
					Key key = _node->value.first;
					while (_node->parent && _comp(_node->parent->value.first, key))
						_node = _node->parent;
					if (_node->parent == NULL) {
						_node = _leaf;
						return *this;
					}
					_node = _node->parent;
				}
				return *this;
			}

			map_iterator operator++(int) {
				node_pointer tmp = _node;
				if (_node->right != _leaf) {
					_node = _node->right;
					while (_node->left != _leaf)
						_node = _node->left;
				}
				else {
					Key key = _node->value.first;
					while (_node->parent && _comp(_node->parent->value.first, key))
						_node = _node->parent;
					if (_node->parent == NULL) {
						_node = _leaf;
						return map_iterator(tmp, _leaf);
					}
					_node = _node->parent;
				}
				return map_iterator(tmp, _leaf);
			}

			map_iterator operator--() {
				if (_node->left != _leaf) {
					_node = _node->left;
					while (_node->right != _leaf)
						_node = _node->right;
				}
				else {
					Key key = _node->value.first;
					while (_node->parent && _comp(key, _node->parent->value.first))
						_node = _node->parent;
					if (_node->parent == NULL) {
						_node = _leaf;
						return *this;
					}
					_node = _node->parent;
				}
				return *this;
			}

			map_iterator operator--(int) {
				node_pointer tmp = _node;
				if (_node->left != _leaf) {
					_node = _node->left;
					while (_node->right != _leaf)
						_node = _node->right;
				}
				else {
					Key key = _node->value.first;
					while (_node->parent && _comp(key, _node->parent->value.first))
						_node = _node->parent;
					if (_node->parent == NULL) {
						_node = _leaf;
						return map_iterator(tmp, _leaf);
					}
					_node = _node->parent;
				}
				return map_iterator(tmp, _leaf);
			}

	};

} // namespace ft

#endif