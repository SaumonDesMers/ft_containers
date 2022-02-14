#ifndef AVL_HPP
#define AVL_HPP

#include <iostream>
#include <iterator.hpp>
#include <reverse_iterator.hpp>
#include <iterator>
#include <exception>
#include <utils.hpp>
#include <other.hpp>
#include <pair.hpp>

typedef enum side {
	root,
	left,
	right
} side_t;

template <class Key, class Type, class Traits = std::less<Key>, class Allocator=std::allocator<ft::pair<const Key, Type>>>
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

		side_t		parent_side;	

		node(const_reference _value, side_t _parent_side, pointer _left = NULL, pointer _right = NULL)
			: value(_value), left(_left), right(_right), left_branch_size(0), right_branch_size(0), parent_side(_parent_side); {}

		int balance() const {return left_branch_size - right_branch_size;}
		
};

template <class Key, class Type, class Traits = std::less<Key>, class Allocator=std::allocator<ft::pair<const Key, Type>>>
class avl {

	public:

		typedef typename Key									key_type;
		typedef typename T										mapped_type;
		typedef typename ft::pair<const Key, T>					value_type;
		typedef typename std::size_t							size_type;
		typedef typename std::ptrdiff_t							difference_type;
		typedef typename Traits									key_compare;
		typedef typename Allocator								allocator_type;
		typedef typename value_type&							reference;
		typedef const value_type&								const_reference;
		typedef typename Allocator::pointer						pointer
		typedef typename Allocator::const_pointer				const_pointer;
		// typedef typename value_type								iterator;
		// typedef typename const value_type						const_iterator;
		// typedef typename ft::reverse_iterator<iterator>		reverse_iterator;
		// typedef typename ft::reverse_iterator<const_iterator>	const_reverse_iterator;
	
	private:

		node	*_root;
		node	*_current;

		allocator_type	_alloc;
	
	public:

		avl(const allocator_type& alloc = allocator_type()) : _root(NULL), _current(NULL), _alloc(alloc) {}

		void add_node(const_reference value) {
			
		}

		reference acces_node(const_reference value) {
			
		}

		void erase_node(const_reference value) {
			
		}

};

#endif