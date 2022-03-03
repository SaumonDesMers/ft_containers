#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>
#include <iomanip>
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

			enum type_e {
				NODE,
				END,
				REND
			} type;

			int			left_branch_size;
			int			right_branch_size;

			node_allocator_type node_alloc;

			node(const_reference _value, node_pointer _parent, type_e _type = NODE, node_pointer _left = 0, node_pointer _right = 0, int lbs = 0, int rbs = 0)
				: value(_value),
				parent(_parent),
				left(_left),
				right(_right),
				type(_type),
				left_branch_size(lbs),
				right_branch_size(rbs),
				node_alloc(node_allocator_type()) {}

			node(node_type const &other)
				: value(other.value),
				parent(other.parent),
				left(other.left),
				right(other.right),
				type(other.type),
				left_branch_size(other.left_branch_size),
				right_branch_size(other.right_branch_size),
				node_alloc(other.node_alloc) {}

			~node() {}

			void destroy() {
				if (left && left->type == NODE)
					left->destroy();
				if (right && right->type == NODE)
					right->destroy();
				node_alloc.destroy(this);
				node_alloc.deallocate(this, 1);
			}

			node_pointer clone(node_pointer copy_parent) {
				node_pointer copy = node_alloc.allocate(1);
				node_pointer left_copy = left ? left->clone(copy) : NULL;
				node_pointer right_copy = right ? right->clone(copy) : NULL;

				node_alloc.construct(copy, node_type(value, copy_parent, type, left_copy, right_copy, left_branch_size, right_branch_size));
				return copy;
			}

			int update_branch_size() {
				left_branch_size = (left && left->type == NODE) ? left->update_branch_size() : 0;
				right_branch_size = (right && right->type == NODE) ? right->update_branch_size() : 0;
				return std::max(left_branch_size, right_branch_size) + 1;
			}

			int balance() const { return left_branch_size - right_branch_size; }

			key_type key() { return value.first; }

			void print() {
				int max_depth = std::max(left_branch_size, right_branch_size);
				std::string *output = new std::string[max_depth + 1];

				size_t delta = 4;
				for (int i=0; i<max_depth; i++)
					delta = delta * 2 + 1;

				this->fill_output(output, delta);

				for (int i=0; i<max_depth + 1; i++) {
					std::cout << output[i].substr(delta / 2, output[i].size() - delta / 2) << std::endl;
					delta = (delta - 1) / 2;
				}
				delete[] output;
			}

			int fill_output(std::string *output, int delta, int index = 0, int depth = 0) {
				if (left && left->type == NODE)
					left->fill_output(output, (delta - 1) / 2, index * 2, depth + 1);
				if (right && right->type == NODE)
					right->fill_output(output, (delta - 1) / 2, index * 2 + 1, depth + 1);

				while (output[depth].size() < static_cast<size_t>(((delta + 1) * (index + 1)) - 1))
					output[depth] += " ";
				output[depth] += itoa(value.first);
				return 1;
			}
	};

} // namespace ft

#endif