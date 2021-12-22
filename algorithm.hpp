/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 22:10:09 by smun              #+#    #+#             */
/*   Updated: 2021/12/22 22:22:11 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGORITHM_HPP
# define ALGORITHM_HPP

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

	template <typename T1, typename T2 = T1>
	struct less
	{
		bool operator(T1 const& x, T2 const& y) const
		{
			return x < y;
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
}

#endif
