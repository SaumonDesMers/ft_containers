#ifndef UTILS_HPP
#define UTILS_HPP

namespace ft
{
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

	//########################################################################

	template <class Iter1, class Iter2>
	bool lexicographical_compare (Iter1 first1, Iter1 last1, Iter2 first2, Iter2 last2) {
		while (first1!=last1)
		{
			if (first2==last2 || *first2<*first1)
				return false;
			else if (*first1<*first2)
				return true;
			++first1; ++first2;
		}
		return (first2!=last2);
	}

	template <class Iter1, class Iter2, class Compare>
	bool lexicographical_compare (Iter1 first1, Iter1 last1, Iter2 first2, Iter2 last2, Compare comp) {
		while (first1!=last1)
		{
			if (first2==last2 || comp(*first2, *first1))
				return false;
			else if (comp(*first1, *first2))
				return true;
			++first1; ++first2;
		}
		return (first2!=last2);
	}

	//########################################################################

	template <class Iter1, class Iter2>
	bool equal ( Iter1 first1, Iter1 last1, Iter2 first2 ) {
		while (first1!=last1) {
			if (!(*first1 == *first2))
				return false;
			++first1; ++first2;
		}
		return true;
	}

	template <class Iter1, class Iter2, class Compare>
	bool equal ( Iter1 first1, Iter1 last1, Iter2 first2, Compare comp ) {
		while (first1!=last1) {
			if (!comp(*first1, *first2))
				return false;
			++first1; ++first2;
		}
		return true;
	}

} // namespace ft

#endif