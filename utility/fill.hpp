/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 20:57:34 by smun              #+#    #+#             */
/*   Updated: 2021/12/22 21:00:40 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILL_HPP
# define FILL_HPP

namespace ft
{
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
}

#endif
