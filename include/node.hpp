#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>
#include <iterator.hpp>
#include <reverse_iterator.hpp>
#include <iterator>
#include <exception>
#include <utils.hpp>
#include <other.hpp>
#include <pair.hpp>
#include <map.hpp>
#include <map_iterator.hpp>

namespace ft
{

	template <class Key, class Type, class Traits, class Allocator>
	class map;

	template <class Key, class Type, class Traits = std::less<Key>, class Allocator=std::allocator<ft::pair<const Key, Type> > >
	class node {

		public:

			typedef Key													key_type;
			typedef Type												mapped_type;
			typedef typename ft::pair<const Key, Type>					value_type;
			typedef typename ft::node<Key, Type, Traits, Allocator>		node_type;
			typedef typename ft::map<Key, Type, Traits, Allocator>		map_type;
			typedef typename std::size_t								size_type;
			typedef typename std::ptrdiff_t								difference_type;
			typedef Traits												key_compare;
			typedef value_type&											reference;
			typedef const value_type&									const_reference;
			typedef node_type*											node_pointer;
			typedef const node_pointer									const_node_pointer;
			typedef typename map_type::node_allocator_type				node_allocator_type;

			value_type			value;
			node_pointer		parent;
			node_pointer		left;
			node_pointer		right;

			node_pointer		leaf;

			int			left_branch_size;
			int			right_branch_size;

			node_allocator_type node_alloc;

			node(const_reference _value, node_pointer _parent, node_pointer _leaf, node_pointer _left = 0, node_pointer _right = 0, int lbs = 0, int rbs = 0)
				: value(_value),
				parent(_parent),
				leaf(_leaf),
				left_branch_size(lbs),
				right_branch_size(rbs),
				node_alloc(node_allocator_type()) {
					left = _left ? _left : leaf;
					right = _right ? _right : leaf;
				}

			node(node_type const &other)
				: value(other.value),
				parent(other.parent),
				left(other.left),
				right(other.right),
				leaf(other.leaf),
				left_branch_size(other.left_branch_size),
				right_branch_size(other.right_branch_size),
				node_alloc(other.node_alloc) {}

			~node() {}

			void destroy() {
				if (left != leaf)
					left->destroy();
				if (right != leaf)
					right->destroy();
				node_alloc.destroy(this);
				node_alloc.deallocate(this, 1);
			}

			node_pointer clone(node_pointer copy_parent, node_pointer other_leaf) {
				node_pointer copy = node_alloc.allocate(1);
				node_pointer left_copy = left != leaf ? left->clone(copy, leaf) : other_leaf;
				node_pointer right_copy = right != leaf ? right->clone(copy, leaf) : other_leaf;

				node_alloc.construct(copy, node_type(value, copy_parent, left_copy, right_copy, left_branch_size, right_branch_size));
				return copy;
			}

			int balance() const { return left_branch_size - right_branch_size; }
			
	};

} // namespace ft

#endif