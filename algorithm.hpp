/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 22:10:09 by smun              #+#    #+#             */
/*   Updated: 2021/12/23 21:09:06 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGORITHM_HPP
# define ALGORITHM_HPP

# include "iterator.hpp"

namespace ft
{
	template<typename T>
	void	swap(T& o1, T& o2)
	{
		if (&o1 == &o2)
			return;
		T tmp = o1;
		o1 = o2;
		o2 = tmp;
	}

	template <typename OutputIter, typename Size, typename Type>
	OutputIter	fill_n(OutputIter first, Size n, const Type& value)
	{
		while (n > 0)
		{
			*first = value;
			++first;
			--n;
		}
		return first;
	}

	template <typename OutputIter, typename Size, typename Type>
	void		fill(OutputIter first, Size n, const Type& value)
	{
		fill_n(first, n, value);
	}

	template <typename InputIter, typename OutputIter>
	void		move(InputIter first, InputIter last, OutputIter out)
	{
		while (first != last)
		{
			*out = *first;
			++first;
			++out;
		}
	}

	template <typename InputIter, typename OutputIter>
	void		move_backward(InputIter first, InputIter last, OutputIter out)
	{
		while (last != first)
		{
			*out = *last;
			--last;
			--out;
		}
	}

	template <typename T1, typename T2 = T1>
	struct less
	{
		bool operator(T1 const& x, T2 const& y) const
		{
			return x < y;
		}
	};

	template <typename T1, typename T2 = T1>
	struct equal_to
	{
		bool operator(T1 const& x, T2 const& y) const
		{
			return x == y;
		}
	};

	template <typename Type, class Compare>
	Type const&	max(Type const& a, Type const& b, Compare comp)
	{
		return comp(a, b) ? b : a;
	}

	template <typename Type>
	Type const&	max(Type const& a, Type const& b)
	{
		return max(a, b, less<Type>());
	}

	template <typename Type, class Compare>
	Type const&	min(Type const& a, Type const& b, Compare comp)
	{
		return comp(a, b) ? a : b;
	}

	template <typename Type>
	Type const&	min(Type const& a, Type const& b)
	{
		return min(a, b, less<Type>());
	}

	template<typename InputIter>
	typename iterator_traits<InputIter>::difference_type
	distance(InputIter& first, InputIter& last)
	{
		return IteratorManipulator(first).distance(last);
	}

	template<typename InputIter>
	InputIter
	next(InputIter& iter, typename iterator_traits<InputIter>::difference_type n = 1)
	{
		return IteratorManipulator(iter).advance(n);
	}

	template<typename InputIter>
	InputIter
	prev(InputIter& iter, typename iterator_traits<InputIter>::difference_type n = 1)
	{
		return IteratorManipulator(iter).advance(-n);
	}

	template<typename InputIter>
	void
	advance(InputIter& iter, typename iterator_traits<InputIter>::difference_type n)
	{
		iter = IteratorManipulator(iter).advance(n);
	}

	template<typename InputIter1, typename InputIter2, typename BinaryPredicate>
	bool
	equal(InputIter1 first1, InputIter1 last1, InputIter2 first2, BinaryPredicate pred)
	{
		while (first1 != last1)
		{
			if (!pred(*first1, *first2))
				return false;
			++first1;
			++first2;
		}
		return true;
	}

	template<typename InputIter1, typename InputIter2>
	bool
	equal(InputIter1 first1, InputIter1 last1, InputIter2 first)
	{
		return equal(
			first1,
			last1,
			first2,
			equal_to<
				typename iterator_traits<InputIter1>::value_type,
				typename iterator_traits<InputIter2>::value_type
			>()
		);
	}

	template<typename InputIter1, typename InputIter2, typename Compare>
	bool
	lexicographical_compare(InputIter1 first1, InputIter1 last1, InputIter2 first2, InputIter2 last2, Compare comp)
	{
		while (first2 != last2)
		{
			if (first1 == last1) // reached to end
				return true;
			if (comp(*first1, *first2)) // *first1 < *first2 --> true
				return true;
			if (comp(*first2, *first1)) // *first1 > *first2 --> false
				return false;
			++first1;
			++first2;
		}
		return false; // else case --> false
	}

	template<typename InputIter1, typename InputIter2>
	bool
	lexicographical_compare(InputIter1 first1, InputIter1 last1, InputIter2 first2, InputIter2 last2)
	{
		return lexicographical_compare(
			first1,
			last1,
			first2,
			last2,
			less<
				typename iterator_traits<InputIter1>::value_type,
				typename iterator_traits<InputIter2>::value_type
			>()
		);
	}
}

#endif
