#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include <iterator.hpp>
#include <reverse_iterator.hpp>
#include <iterator>
#include <exception>
#include <utils.hpp>
#include <other.hpp>

namespace ft
{

	template <class Key, class Type, class Traits = std::less<Key>>
	class node {

		public:

			typedef typename Key									key_type;
			typedef typename T										mapped_type;
			typedef typename ft::pair<const Key, T>					value_type;
			typedef typename std::size_t							size_type;
			typedef typename std::ptrdiff_t							difference_type;
			typedef typename Compare								key_compare;
			typedef typename Allocator								allocator_type;
			typedef typename value_type&							reference;
			typedef const value_type&								const_reference;
			typedef typename Allocator::pointer						pointer;
			typedef typename Allocator::const_pointer				const_pointer;

			value_type	value;
			pointer		left;
			pointer		right;

			int			left_branch_size;
			int			right_branch_size;

			node(const_reference _value, pointer _left = NULL, pointer _right = NULL)
				: value(_value), left(_left), right(_right), left_branch_size(0), right_branch_size(0), {}

			int balance() const {return left_branch_size - right_branch_size;}
			
	};

	template <class Key, class Type, class Traits = std::less<Key>, class Allocator=std::allocator<ft::pair<const Key, Type>>>
	class map {

		public:

			typedef typename Key														key_type;
			typedef typename Type														mapped_type;
			typedef typename ft::pair<const Key, Type>									value_type;
			typedef typename std::size_t												size_type;
			typedef typename std::ptrdiff_t												difference_type;
			typedef typename Traits														key_compare;
			typedef typename Allocator													allocator_type;
			typedef typename value_type&												reference;
			typedef const value_type&													const_reference;
			typedef typename Allocator::pointer											pointer;
			typedef typename Allocator::const_pointer									const_pointer;
			// typedef typename value_type													iterator;
			// typedef typename const value_type											const_iterator;
			// typedef typename ft::reverse_iterator<iterator>								reverse_iterator;
			// typedef typename ft::reverse_iterator<const_iterator>						const_reverse_iterator;
			typedef typename Allocator::template rebind<node<Key, Type, Traits>>::other	node_allocator_type;
		
		private:

			node				*_root;
			size_type			_size;
			allocator_type		_alloc;
			node_allocator_type	_node_alloc;

			bool operator==(key_type const &k1, key_type const &k2) { return !key_compare(k1, k2) && !key_compare(k2, k1); }

			infix_count(node *current, const key_type& key, int &count) {
				if (current->left != NULL && !count)
					infix_count(current->left, key, count);
				if (key == current->value.first)
					count = 1;
				if (current->right != NULL && !count)
					infix_count(current->right, key, count);
			}

		public:

			map();
			explicit map(const Compare& comp, const Allocator& alloc = Allocator());
			template< class InputIt >
			map(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator());
			map(const map& other);

			~map();

			map& operator=(const map& other);

			allocator_type get_allocator() const { return _alloc; }

			mapped_type& at(const key_type& key);
			const mapped_type& at(const key_type& key) const;

			mapped_type& operator[](const key_type& key) {
				node *current;
				while (key == )

				node *newNode = _node_alloc.allocate(1);
				_node_alloc.construct(newNode, node(ft::pair(key, mapped_type())));

				return newNode->value.second;
			}

			bool empty() const { return _size == 0; }

			size_type size() const { return _size; }

			size_type max_size() const { return _node_alloc.maxsize(); }

			void clear();

			ft::pair<iterator, bool> insert(const value_type& value);
			iterator insert(iterator hint, const value_type& value);
			template< class InputIt >
			void insert(InputIt first, InputIt last);

			void erase(iterator pos);
			void erase(iterator first, iterator last);

			void swap(map& other);

			size_type count(const key_type& key) const {
				return infix_count(root, key, 0);
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

			ft::map::value_compare value_comp() const;
	};

	template< class Key, class T, class Compare, class Alloc >
	bool operator==(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs);

	template< class Key, class T, class Compare, class Alloc >
	bool operator!=(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs);

	template< class Key, class T, class Compare, class Alloc >
	bool operator<(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs);

	template< class Key, class T, class Compare, class Alloc >
	bool operator<=(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs);

	template< class Key, class T, class Compare, class Alloc >
	bool operator>(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs);

	template< class Key, class T, class Compare, class Alloc >
	bool operator>=(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs);

	template< class Key, class T, class Compare, class Alloc >
	void swap(ft::map<Key, T, Compare, Alloc>& lhs,  ft::map<Key, T, Compare, Alloc>& rhs);

} // namespace ft

#endif