/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erase2.ipp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 20:26:30 by smun              #+#    #+#             */
/*   Updated: 2022/01/02 15:30:25 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Vector Erase
**
**  1. erase(iterator first, iterator last) 함수
*/

void	Erase2(value_type val1)
{
	Vector vec1(30, val1);
	for (int i = 0; i < 5; i++)
	{
		typename Vector::iterator it = vec1.erase(ft::next(vec1.begin(), i), ft::next(vec1.begin(), i * 2));
		typename Vector::difference_type n = ft::distance(vec1.begin(), it);
		PrintSizeAndCapacity(vec1);
		std::cout << n << std::endl;
	}
	PrintSizeAndCapacity(vec1);
	PrintElements(vec1);
}
