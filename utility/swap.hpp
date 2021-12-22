/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 13:40:12 by smun              #+#    #+#             */
/*   Updated: 2021/12/22 17:36:54 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SWAP_HPP
# define SWAP_HPP

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
}

#endif
