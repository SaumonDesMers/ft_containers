#ifndef UTILS_HPP
#define UTILS_HPP

namespace ft
{
	//########################################################################

	template< class Iter >
	struct iterator_traits {
		typedef typename Iter::iterator_category iterator_category;
		typedef typename Iter::value_type value_type;
		typedef typename Iter::difference_type difference_type;
		typedef difference_type distance_type;
		typedef typename Iter::pointer pointer;
		typedef typename Iter::reference reference;
	};

	//########################################################################
	
	template<bool B, class T = void>
	struct enable_if {};
	
	template<class T>
	struct enable_if<true, T> { typedef T type; };
	
	//########################################################################

	template<class T>
	struct is_integral { static const bool value = false; };

	template<> struct is_integral<bool> { static const bool value = true; };
	template<> struct is_integral<char> { static const bool value = true; };
	template<> struct is_integral<wchar_t> { static const bool value = true; };
	template<> struct is_integral<signed char> { static const bool value = true; };
	template<> struct is_integral<short int> { static const bool value = true; };
	template<> struct is_integral<int> { static const bool value = true; };
	template<> struct is_integral<long int> { static const bool value = true; };
	template<> struct is_integral<long long int> { static const bool value = true; };
	template<> struct is_integral<unsigned char> { static const bool value = true; };
	template<> struct is_integral<unsigned short int> { static const bool value = true; };
	template<> struct is_integral<unsigned int> { static const bool value = true; };
	template<> struct is_integral<unsigned long int> { static const bool value = true; };
	template<> struct is_integral<unsigned long long int> { static const bool value = true; };
	
} // namespace ft

#endif