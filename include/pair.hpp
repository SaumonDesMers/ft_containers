#ifndef PAIR_HPP
#define PAIR_HPP

namespace ft
{

	template <class T1, class T2>
	struct pair {
		T1 first;
		T2 second;

		pair() {}
		pair(const pair<T1,T2>& pr) {
			first = pr.first;
			second = pr.second; 
		}
		pair(const T1& a, const T2& b) : first(a), second(b) {}
		~pair() {}

		template<class U, class V>
		pair& operator=(const pair<U, V>& pr) {
			this->first = static_cast<U>(pr.first);
			this->second = static_cast<V>(pr.second);
			return *this;
		}

		bool operator==(const pair<T1,T2>& rhs) const
		{ return this->first==rhs.first && this->second==rhs.second; }

		bool operator!=(const pair<T1,T2>& rhs) const
		{ return !(*this==rhs); }

		bool operator<(const pair<T1,T2>& rhs) const
		{ return this->first<rhs.first || (!(rhs.first<this->first) && this->second<rhs.second); }

		bool operator<=(const pair<T1,T2>& rhs) const
		{ return !(rhs<*this); }

		bool operator>(const pair<T1,T2>& rhs) const
		{ return rhs<*this; }

		bool operator>=(const pair<T1,T2>& rhs) const
		{ return !(*this<rhs); }
	};

	// template <class T1, class T2>
	// bool operator==(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	// { return lhs.first==rhs.first && lhs.second==rhs.second; }

	// template <class T1, class T2>
	// bool operator!=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	// { return !(lhs==rhs); }

	// template <class T1, class T2>
	// bool operator<(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	// { return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second); }

	// template <class T1, class T2>
	// bool operator<=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	// { return !(rhs<lhs); }

	// template <class T1, class T2>
	// bool operator>(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	// { return rhs<lhs; }

	// template <class T1, class T2>
	// bool operator>=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	// { return !(lhs<rhs); }

	template <class T1,class T2>
	pair<T1,T2> make_pair(T1 x, T2 y) { return (pair<T1,T2>(x,y)); }

} // namespace ft

#endif