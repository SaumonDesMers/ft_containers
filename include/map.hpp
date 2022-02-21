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
#include <map_iterator.hpp>

namespace ft
{

	template <class Key, class Type, class Traits, class Allocator>
	class map;

	template <class Key, class Type, class Traits = std::less<Key>, class Allocator=std::allocator<ft::pair<const Key, Type> > >
	class node {

		public:

			typedef Key																key_type;
			typedef Type															mapped_type;
			typedef typename ft::pair<const Key, Type>								value_type;
			typedef typename ft::map<Key, Type, Traits, Allocator>					map_type;
			typedef typename std::size_t											size_type;
			typedef typename std::ptrdiff_t											difference_type;

			typedef Traits															key_compare;

			typedef value_type&														reference;
			typedef const value_type&												const_reference;

			typedef typename ft::node<Key, Type, Traits>*							pointer;
			typedef const pointer													const_pointer;

			typedef typename map_type::node_allocator_type							node_allocator_type;

			value_type	value;
			pointer		parent;
			pointer		left;
			pointer		right;

			node_allocator_type node_allocator;

			int			left_branch_size;
			int			right_branch_size;

			node(const_reference _value, pointer _parent, pointer _left = 0, pointer _right = 0)
				: value(_value), parent(_parent), left(_left), right(_right), node_allocator(node_allocator_type()), left_branch_size(0), right_branch_size(0) {}

			~node() {}

			void destroy() {
				if (left)
					left->destroy();
				if (right)
					right->destroy();
				node_allocator.destroy(this);
				node_allocator.deallocate(this, 1);
			}

			int balance() const {return left_branch_size - right_branch_size;}
			
	};

	template <class Key, class Type, class Traits = std::less<Key>, class Allocator=std::allocator<ft::pair<const Key, Type> > >
	class map {

		public:

			typedef Key																		key_type;
			typedef Type																	mapped_type;
			typedef typename ft::pair<const Key, Type>										value_type;
			typedef node<Key, Type, Traits, Allocator>										node_type;
			typedef typename std::size_t													size_type;
			typedef typename std::ptrdiff_t													difference_type;
			typedef Traits																	key_compare;
			typedef Allocator																allocator_type;
			typedef value_type&																reference;
			typedef const value_type&														const_reference;
			typedef typename Allocator::pointer												pointer;
			typedef typename Allocator::const_pointer										const_pointer;
			typedef typename ft::map_iterator<bidirectional_iterator_tag, value_type>		iterator;
			typedef const iterator															const_iterator;
			typedef typename ft::reverse_iterator<iterator>									reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>							const_reverse_iterator;
			typedef typename Allocator::template rebind<node<Key, Type, Traits> >::other	node_allocator_type;
		
		private:

			node_type			*_root;
			size_type			_size;
			allocator_type		_alloc;
			node_allocator_type	_node_alloc;

			key_compare			comp;

			// bool operator==(key_type const &k1, key_type const &k2) { return !comp(k1, k2) && !comp(k2, k1); std::cout << "test" << std::endl; }

		public:

			map() : _root(NULL), _size(0), _alloc(allocator_type()), _node_alloc(node_allocator_type()) {}
			explicit map(const key_compare& comp, const Allocator& alloc = Allocator());
			template<class InputIt>
			map(InputIt first, InputIt last, const key_compare& comp = key_compare(), const Allocator& alloc = Allocator());
			map(const map& other);

			~map() { clear(); }

			map& operator=(const map& other);

			allocator_type get_allocator() const { return _alloc; }

			mapped_type& at(const key_type& key) {
				node_type *current = _root;
				while (current) {
					if (key == current->value.first)
						return current->value.second;
					else if (comp(key, current->value.first))
						current = current->left;
					else
						current = current->right;
				}
				throw std::out_of_range("map::at");
			}

			const mapped_type& at(const key_type& key) const {
				node_type *current = _root;
				while (current) {
					if (key == current->value.first)
						return current->value.second;
					else if (comp(key, current->value.first))
						current = current->left;
					else
						current = current->right;
				}
				throw std::out_of_range("map::at");
			}

			mapped_type& operator[](const key_type& key) {
				node_type *current = _root;
				node_type *parent = NULL;
				while (current) {
					parent = current;
					if (key == current->value.first)
						return current->value.second;
					else if (comp(key, current->value.first))
						current = current->left;
					else
						current = current->right;
				}

				node_type *newNode = _node_alloc.allocate(1);
				_node_alloc.construct(newNode, node_type(value_type(key, mapped_type()), parent));
				current = newNode;
				if (!_root)
					_root = current;
				else if (comp(key, parent->value.first))
					parent->left = current;
				else
					parent->right = current;
				_size++;
				return newNode->value.second;
			}

			bool empty() const { return _size == 0; }

			size_type size() const { return _size; }

			size_type max_size() const { return _node_alloc.maxsize(); }

			void clear() {
				if (_root)
					_root->destroy();
				_root = NULL;
				_size = 0;
			}

			ft::pair<iterator, bool> insert(const value_type& value);
			iterator insert(iterator hint, const value_type& value);
			template<class InputIt>
			void insert(InputIt first, InputIt last);

			void erase(iterator pos);
			void erase(iterator first, iterator last);

			void swap(map& other);

			size_type count(const key_type& key) const {
				node_type *current = _root;
				while (current)
				{
					if (key == current->value.first)
						return 1;
					else if (comp(key, current->value.first))
						current = current->left;
					else
						current = current->right;
				}
				return 0;
			}

			iterator find(const key_type& key);
			const_iterator find(const key_type& key) const;

			ft::pair<iterator,iterator> equal_range(const key_type& key);
			ft::pair<const_iterator,const_iterator> equal_range(const key_type& key) const;

			iterator lower_bound(const key_type& key);
			const_iterator lower_bound(const key_type& key) const;

			iterator upper_bound(const key_type& key);
			const_iterator upper_bound(const key_type& key) const;

			key_compare key_comp() const;

			// ft::map::value_compare value_comp() const;

			void parkour(node_type *current, std::string const &type) {
				if (type == "prefixe")
					log(current);
				if (current->left)
					parkour(current->left, type);
				if (type == "infixe")
					log(current);
				if (current->right)
					parkour(current->right, type);
				if (type == "sufixe")
					log(current);
			}

			void log(node_type * node) {
				std::cout << "\nNode < " << node->value.first << ", " << node->value.second << " > (" << node << ")";
				if (node->parent)
					std::cout << "\nparent < " << node->parent->value.first << ", " << node->parent->value.second << " > (" << node->parent << ")";
				if (node->left)
					std::cout << "\nleft < " << node->left->value.first << ", " << node->left->value.second << " > (" << node->left << ")";
				if (node->right)
					std::cout << "\nright < " << node->right->value.first << ", " << node->right->value.second << " > (" << node->right << ")";
				std::cout << std::endl;
			}

			void print() {
				parkour(_root, "infixe");
			}

	};

	template<class Key, class T, class Compare, class Alloc>
	bool operator==(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs);

	template<class Key, class T, class Compare, class Alloc>
	bool operator!=(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs);

	template<class Key, class T, class Compare, class Alloc>
	bool operator<(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs);

	template<class Key, class T, class Compare, class Alloc>
	bool operator<=(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs);

	template<class Key, class T, class Compare, class Alloc>
	bool operator>(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs);

	template<class Key, class T, class Compare, class Alloc>
	bool operator>=(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs);

	template<class Key, class T, class Compare, class Alloc>
	void swap(ft::map<Key, T, Compare, Alloc>& lhs,  ft::map<Key, T, Compare, Alloc>& rhs);

} // namespace ft

#endif