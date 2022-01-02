/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erase_empty.ipp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 20:26:30 by smun              #+#    #+#             */
/*   Updated: 2022/01/02 15:24:21 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Vector Erase (Empty)
**
**  1. erase(iterator first, iterator last) 함수
*/

void	Erase_Empty(value_type val1)
{
	Vector vec2(3, val1);

	{
		typename Vector::iterator it = vec2.erase(vec2.begin(), vec2.begin());
		typename Vector::difference_type n = ft::distance(vec2.begin(), it);
		std::cout << n << std::endl;
	}

	{
		typename Vector::iterator it = vec2.erase(vec2.begin(), vec2.end());
		typename Vector::difference_type n = ft::distance(vec2.begin(), it);
		std::cout << n << std::endl;
	}

	{
		typename Vector::iterator it2 = vec2.erase(vec2.begin(), vec2.end());
		typename Vector::difference_type n2 = ft::distance(vec2.begin(), it2);
		std::cout << n2 << std::endl;
	}

	PrintSizeAndCapacity(vec2);
	PrintElements(vec2);
}
