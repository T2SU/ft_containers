/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 22:10:39 by smun              #+#    #+#             */
/*   Updated: 2022/02/02 15:49:17 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITY_HPP
# define UTILITY_HPP

# include "algorithm.hpp"

namespace ft
{
	template<typename T1, typename T2>
	class pair
	{
	public:
		T1	first;
		T2	second;

		pair()
			: first()
			, second()
		{
		}

		pair(T1 const& first, T2 const& second)
			: first(first)
			, second(second)
		{
		}

		virtual ~pair()
		{
		}

		pair(pair<T1, T2> const& origin)
			: first(origin.first)
			, second(origin.second)
		{
		}

		template<typename U1, typename U2>
		pair(pair<U1, U2> const& origin)
			: first(origin.first)
			, second(origin.second)
		{
		}

		pair<T1, T2>& operator=(pair<T1, T2> const& another)
		{
			if (this == &another)
				return *this;
			first = another.first;
			second = another.second;
			return *this;
		}

		void	swap(pair<T1, T2>& rhs)
		{
			ft::swap(first, rhs.first);
			ft::swap(second, rhs.second);
		}
	};

	template<typename T1, typename T2>
	pair<T1, T2>	make_pair(T1 first, T2 second)
	{
		return ft::pair<T1, T2>(first, second);
	}

	template<typename T1, typename T2>
	bool	operator==(pair<T1, T2> const& lhs, pair<T1, T2> const& rhs)
	{
		return lhs.first == rhs.first && lhs.second == rhs.second;
	}

	template<typename T1, typename T2>
	bool	operator!=(pair<T1, T2> const& lhs, pair<T1, T2> const& rhs)
	{
		return !(lhs == rhs);
	}

	template<typename T1, typename T2>
	bool	operator<(pair<T1, T2> const& lhs, pair<T1, T2> const& rhs)
	{
		return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
	}

	template<typename T1, typename T2>
	bool	operator<=(pair<T1, T2> const& lhs, pair<T1, T2> const& rhs)
	{
		return !(rhs < lhs);
	}

	template<typename T1, typename T2>
	bool	operator>(pair<T1, T2> const& lhs, pair<T1, T2> const& rhs)
	{
		return rhs < lhs;
	}

	template<typename T1, typename T2>
	bool	operator>=(pair<T1, T2> const& lhs, pair<T1, T2> const& rhs)
	{
		return !(lhs < rhs);
	}

	template<typename T1, typename T2>
	void	swap(pair<T1, T2>& lhs, pair<T1, T2>& rhs)
	{
		lhs.swap(rhs);
	}
}

#endif
