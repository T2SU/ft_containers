/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 22:10:39 by smun              #+#    #+#             */
/*   Updated: 2021/12/22 22:11:05 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITY_HPP
# define UTILITY_HPP

namespace ft
{
	template<typename T1, typename T2>
	class pair
	{
	public:
		typedef typename T1		first_type;
		typedef typename T2		second_type;

		T1	first;
		T2	second;

		pair()
		{
		}

		pair(T1 first, T2 second)
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

		pair<T1, T2>& operator=(pair<T1, T2> const& another)
		{
			if (this == &another)
				return *this;
			first = another.first;
			second = another.second;
			return *this;
		}

		void	swap(pair<T1, T2>& another)
		{
			ft::swap(*this, &another);
		}
	};

	template<typename T1, typename T2>
	pair<T1, T2>	make_pair(T1 first, T2 second)
	{
		return ft::pair<T1, T2>(first, second);
	}
}

#endif
