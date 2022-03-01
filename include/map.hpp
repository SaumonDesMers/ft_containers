#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include <iterator.hpp>
#include <reverse_iterator.hpp>
#include <iterator>
#include <exception>
#include <utils.hpp>
#include <other.hpp>
#include <pair.hpp>
#include <node.hpp>
#include <map_iterator.hpp>

namespace ft
{

	template <class Key, class Type, class Traits, class Allocator>
	class node;

	template <class Key, class Type, class Traits = std::less<Key>, class Allocator=std::allocator<ft::pair<const Key, Type> > >
	class map {

		public:

			typedef Key																		key_type;
			typedef Type																	mapped_type;
			typedef typename ft::pair<const Key, Type>										value_type;
			typedef node<Key, Type, Traits, Allocator>										node_type;
			typedef typename ft::map<Key, Type, Traits, Allocator>							map_type;
			typedef typename std::size_t													size_type;
			typedef typename std::ptrdiff_t													difference_type;
			typedef Traits																	key_compare;
			typedef Allocator																allocator_type;
			typedef value_type&																reference;
			typedef const value_type&														const_reference;
			typedef typename Allocator::pointer												pointer;
			typedef typename Allocator::const_pointer										const_pointer;
			typedef typename ft::map_iterator<node_type, Key, Type, Traits, Allocator>		iterator;
			typedef const iterator															const_iterator;
			typedef typename ft::map_reverse_iterator<iterator>								reverse_iterator;
			typedef typename ft::map_reverse_iterator<const_iterator>						const_reverse_iterator;
			typedef typename Allocator::template rebind<node<Key, Type, Traits> >::other	node_allocator_type;
		
		private:

			node_type			*_root;
			size_type			_size;
			allocator_type		_alloc;
			node_allocator_type	_node_alloc;

			node_type*			_end;
			node_type*			_rend;

			key_compare			_comp;

			// bool operator==(key_type const &k1, key_type const &k2) { return !comp(k1, k2) && !comp(k2, k1); }

			void construct_leaf() {
				_end = _node_alloc.allocate(1);
				_node_alloc.construct(_end, node_type(value_type(key_type(), "end"), NULL, node_type::END));
				_rend = _node_alloc.allocate(1);
				_node_alloc.construct(_rend, node_type(value_type(key_type(), "rend"), NULL, node_type::REND));
			}

			void destroy_leaf() {
				_node_alloc.destroy(_end);
				_node_alloc.deallocate(_end, 1);
				_node_alloc.destroy(_rend);
				_node_alloc.deallocate(_rend, 1);
			}

			void left_rotate(node_type *x) {
				node_type *y = x->right;
				x->right = y->left;
				if (y->left)
					x->right->parent = x;
				y->parent = x->parent;
				if (x->parent == NULL)
					_root = y;
				else if (x == x->parent->left)
					x->parent->left = y;
				else
					x->parent->right = y;
				y->left = x;
				x->parent = y;
				_root->update_branch_size();
			}

			void right_rotate(node_type *x) {
				node_type *y = x->parent;
				y->left = x->right;
				if (x->right)
					y->left->parent = y;
				x->parent = y->parent;
				if (y->parent == NULL)
					_root = x;
				else if (y == y->parent->left)
					y->parent->left = x;
				else
					y->parent->right = x;
				x->right = y;
				y->parent = x;
				_root->update_branch_size();
			}

			void left_right_rotate(node_type *x) {
				left_rotate(x);
				right_rotate(x->parent);
			}

			void right_left_rotate(node_type *x) {
				right_rotate(x->left);
				left_rotate(x->parent->parent);
			}

			void rebalance(node_type *node) {
				node_type *newNode = node;
				while (node) {
					if (node->balance() > 1 && newNode->value.first < node->left->value.first)
						right_rotate(node->left);
					else if (node->balance() > 1)
						left_right_rotate(node->left);
					if (node->balance() < -1 && newNode->value.first > node->right->value.first)
						left_rotate(node);
					else if (node->balance() < -1)
						right_left_rotate(node->right);
					node = node->parent;
				}
			}

		public:


			map() : _root(NULL), _size(0), _alloc(allocator_type()), _node_alloc(node_allocator_type()), _comp(key_compare()) {
				construct_leaf();
			}

			explicit map(const key_compare& comp, const Allocator& alloc = Allocator())
				: _root(NULL), _size(0), _alloc(alloc), _node_alloc(node_allocator_type()), _comp(comp) {
				construct_leaf();
			}
			
			template<class InputIt>
			map(InputIt first, InputIt last, const key_compare& comp = key_compare(), const Allocator& alloc = Allocator())
				: _root(NULL), _size(0), _alloc(alloc), _node_alloc(node_allocator_type()), _comp(comp) {
				construct_leaf();
				for (InputIt it = first; it != last; it++)
					(*this)[it->first] = it->second;
			}

			map(const map& other) : _root(NULL) {
				if (other._root) {
					_root = other._root->clone(NULL);
					_end = _root;
					while (_end->type != node_type::END)
						_end = _end->right;
					_rend = _root;
					while (_rend->type != node_type::REND)
						_rend = _rend->left;
				}
				else
					construct_leaf();
				_size = other._size;
				_alloc = other._alloc;
				_node_alloc = other._node_alloc;
				_comp = other._comp;
			}

			~map() { clear(); }

			map& operator=(const map& other) {
				clear();
				if (other._root) {
					_root = other._root->clone(NULL);
					_end = _root;
					while (_end->type != node_type::END)
						_end = _end->right;
					_rend = _root;
					while (_rend->type != node_type::REND)
						_rend = _rend->left;
				}
				_size = other._size;
				_alloc = other._alloc;
				_node_alloc = other._node_alloc;
				_comp = other._comp;
				return *this;
			}

			allocator_type get_allocator() const { return _alloc; }

			mapped_type& operator[](const key_type& key) {
				node_type *current = _root;
				node_type *parent = NULL;
				while (current && current->type == node_type::NODE) {
					parent = current;
					if (key == current->value.first)
						return current->value.second;
					else if (_comp(key, current->value.first))
						current = current->left;
					else
						current = current->right;
				}

				node_type *newNode = _node_alloc.allocate(1);
				_node_alloc.construct(newNode, node_type(value_type(key, mapped_type()), parent));
				if (empty()) {
					_root = newNode;
					newNode->left = _rend;
					newNode->right = _end;
					_end->parent = _root;
					_rend->parent = _root;
				}
				else {
					if (current) {
						current->parent = newNode;
						if (current->type == node_type::END) {
							newNode->right = current;
							parent->right = newNode;
						}
						else if (current->type == node_type::REND) {
							newNode->left = current;
							parent->left = newNode;
						}
					}
					else if (_comp(key, parent->value.first))
						parent->left = newNode;
					else
						parent->right = newNode;
				}
				_size++;
				_root->update_branch_size();
				rebalance(newNode);
				return newNode->value.second;
			}

			bool empty() const { return _size == 0; }

			size_type size() const { return _size; }

			size_type max_size() const { return _node_alloc.maxsize(); }

			void clear() {
				if (_root)
					_root->destroy();
				else
					destroy_leaf();
				_root = NULL;
				_size = 0;
			}

			ft::pair<iterator, bool> insert(const value_type& value) {
				size_type flag = count(value.first);
				(*this)[value.first] = value.second;
				return ft::make_pair(find(value.first), flag ? false : true);
			}

			iterator insert(iterator hint, const value_type& value) {
				(void)hint;
				(*this)[value.first] = value.second;
				return find(value.first);
			}

			template<class InputIt>
			void insert(InputIt first, InputIt last) {
				for (InputIt it = first; it != last; it++)
					(*this)[it->first] = it->second;
			}

			void erase(iterator pos);
			void erase(iterator first, iterator last);

			void swap(map_type& other) {
				std::swap(_root, other._root);
				std::swap(_size, other._size);
				std::swap(_alloc, other._alloc);
				std::swap(_node_alloc, other._node_alloc);
				std::swap(_end, other._end);
				std::swap(_rend, other._rend);
				std::swap(_comp, other._comp);
			}

			size_type count(const key_type& key) const {
				node_type *current = _root;
				while (current && current->type == node_type::NODE)
				{
					if (key == current->value.first)
						return 1;
					else if (_comp(key, current->value.first))
						current = current->left;
					else
						current = current->right;
				}
				return 0;
			}

			iterator find(const key_type& key) {
				node_type *current = _root;
				while (current && current->type == node_type::NODE) {
					if (key == current->value.first)
						return iterator(current);
					else if (_comp(key, current->value.first))
						current = current->left;
					else
						current = current->right;
				}
				return end();
			}

			const_iterator find(const key_type& key) const {
				node_type *current = _root;
				while (current && current->type == node_type::NODE) {
					if (key == current->value.first)
						return const_iterator(current);
					else if (_comp(key, current->value.first))
						current = current->left;
					else
						current = current->right;
				}
				return end();
			}

			ft::pair<iterator,iterator> equal_range(const key_type& key) {
				return ft::make_pair(lower_bound(key), upper_bound(key));
			}

			ft::pair<const_iterator,const_iterator> equal_range(const key_type& key) const {
				return ft::make_pair(lower_bound(key), upper_bound(key));
			}

			iterator lower_bound(const key_type& key) {
				if (_comp(key, begin()->first))
					return begin();
				else if (_comp(rbegin()->first, key))
					return end();
				node_type *current = _root;
				node_type *parent = NULL;
				while (current && current->type == node_type::NODE) {
					if (key == current->value.first)
						return iterator(current);
					else if (_comp(key, current->value.first)) {
						parent = current;
						current = current->left;
					}
					else
						current = current->right;
				}
				return iterator(parent);
			}

			const_iterator lower_bound(const key_type& key) const {
				if (_comp(key, begin()->first))
					return begin();
				else if (_comp(rbegin()->first, key))
					return end();
				node_type *current = _root;
				node_type *parent = NULL;
				while (current && current->type == node_type::NODE) {
					if (key == current->value.first)
						return const_iterator(current);
					else if (_comp(key, current->value.first)) {
						parent = current;
						current = current->left;
					}
					else
						current = current->right;
				}
				return const_iterator(parent);
			}

			iterator upper_bound(const key_type& key) {
				if (_comp(key, begin()->first))
					return begin();
				else if (!_comp(key, rbegin()->first))
					return end();
				node_type *current = _root;
				node_type *parent = NULL;
				while (current && current->type == node_type::NODE) {
					if (_comp(key, current->value.first)) {
						parent = current;
						current = current->left;
					}
					else
						current = current->right;
				}
				return iterator(parent);
			}

			const_iterator upper_bound(const key_type& key) const {
				if (_comp(key, begin()->first))
					return begin();
				else if (!_comp(key, rbegin()->first))
					return end();
				node_type *current = _root;
				node_type *parent = NULL;
				while (current && current->type == node_type::NODE) {
					if (_comp(key, current->value.first)) {
						parent = current;
						current = current->left;
					}
					else
						current = current->right;
				}
				return const_iterator(parent);
			}

			key_compare key_comp() const { return _comp; }

			// ft::map::value_compare value_comp() const;

			iterator begin() {
				node_type *node = _root;
				if (empty())
					return end();
				while (node->left->type == node_type::NODE)
					node = node->left;
				return iterator(node);
			}
			const_iterator begin() const {
				node_type *node = _root;
				if (empty())
					return end();
				while (node->left->type == node_type::NODE)
					node = node->left;
				return const_iterator(node);
			}

			iterator end() { return iterator(_end); }
			const_iterator end() const { return const_iterator(_end); }

			reverse_iterator rbegin() {
				node_type *node = _root;
				if (empty())
					return rend();
				while (node->right->type == node_type::NODE)
					node = node->right;
				return reverse_iterator(iterator(node));
			}
			const_reverse_iterator rbegin() const {
				node_type *node = _root;
				if (empty())
					return rend();
				while (node->right->type == node_type::NODE)
					node = node->right;
				return const_reverse_iterator(const_iterator(node));
			}

			reverse_iterator rend() { return reverse_iterator(iterator(_rend)); }
			const_reverse_iterator rend() const { return const_reverse_iterator(const_iterator(_rend)); }

			void parkour(node_type *current) {
				if (current->left)
					parkour(current->left);
				log(current);
				if (current->right)
					parkour(current->right);
			}

			void log(node_type * node) {
				std::cout << "\nNode < " << node->value.first << ", " << node->value.second << " > (balance = " << node->balance() << ")";
				if (node->parent)
					std::cout << "\nparent < " << node->parent->value.first << ", " << node->parent->value.second << " >";
				if (node->left)
					std::cout << "\nleft < " << node->left->value.first << ", " << node->left->value.second << " > (size = " << node->left_branch_size << ")";
				if (node->right)
					std::cout << "\nright < " << node->right->value.first << ", " << node->right->value.second << " > (size = " << node->right_branch_size << ")";
				std::cout << std::endl;
			}

			void print() {
				std::cout << std::endl;
				_root->print();
				std::cout << std::endl;
			}

	};

	template<class Key, class T, class Compare, class Alloc>
	bool operator==(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs) {
		return ft::equal(lhs.begin(), lhs.end(), rhs.begin()) && lhs.size() == rhs.size();
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator!=(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs) { return !(lhs == rhs); }

	template<class Key, class T, class Compare, class Alloc>
	bool operator<(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator<=(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs) { return !(rhs < lhs); }

	template<class Key, class T, class Compare, class Alloc>
	bool operator>(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs) { return rhs < lhs; }

	template<class Key, class T, class Compare, class Alloc>
	bool operator>=(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs) { return !(lhs < rhs); }

	template<class Key, class T, class Compare, class Alloc>
	void swap(ft::map<Key, T, Compare, Alloc>& lhs,  ft::map<Key, T, Compare, Alloc>& rhs) { lhs.swap(rhs); }

} // namespace ft

#endif