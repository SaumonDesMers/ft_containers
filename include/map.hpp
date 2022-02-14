#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include <iterator.hpp>
#include <reverse_iterator.hpp>
#include <iterator>
#include <exception>
#include <utils.hpp>
#include <other.hpp>
#include <avl.hpp>

template <class Key, class Type, class Traits = std::less<Key>, class Allocator=std::allocator<ft::pair <const Key, Type>>>
class map {

	public:

		typedef typename Key									key_type;
		typedef typename Type									mapped_type;
		typedef typename ft::pair<const Key, Type>				value_type;
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

		avl		_avl<Key, Type, Traits, Allocator>;

	public:

		map();
		explicit map(const Compare& comp, const Allocator& alloc = Allocator());
		template< class InputIt >
		map(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator());
		map(const map& other);

		~map();

		map& operator=(const map& other);

		allocator_type get_allocator() const;

		Type& at(const Key& key);
		const Type& at(const Key& key) const;

		Type& operator[](const Key& key);

		bool empty() const;

		size_type size() const;

		size_type max_size() const;

		void clear();

		ft::pair<iterator, bool> insert(const value_type& value);
		iterator insert(iterator hint, const value_type& value);
		template< class InputIt >
		void insert(InputIt first, InputIt last);

		void erase(iterator pos);
		void erase(iterator first, iterator last);

		void swap(map& other);

		size_type count(const Key& key) const;

		iterator find(const Key& key);
		const_iterator find(const Key& key) const;

		ft::pair<iterator,iterator> equal_range(const Key& key);
		ft::pair<const_iterator,const_iterator> equal_range(const Key& key) const;

		iterator lower_bound(const Key& key);
		const_iterator lower_bound(const Key& key) const;

		iterator upper_bound(const Key& key);
		const_iterator upper_bound(const Key& key) const;

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


#endif