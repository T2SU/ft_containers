/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erase2.ipp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 20:26:30 by smun              #+#    #+#             */
/*   Updated: 2022/01/02 16:03:36 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Vector Erase
**
**  1. erase(iterator first, iterator last) 함수
*/

void	Erase2(value_type val1)
{
	Vector vec1(14, val1);
	for (int i = 0; i < 5; i++)
	{
		typename Vector::difference_type len = ft::distance(ft::next(vec1.begin(), i), ft::next(vec1.begin(), i * 2));
		typename Vector::iterator it = vec1.erase(ft::next(vec1.begin(), i), ft::next(vec1.begin(), i * 2));
		typename Vector::difference_type n = ft::distance(vec1.begin(), it);
		PrintSizeAndCapacity(vec1);
		std::cout << "len: " << len << " / n: " << n << std::endl;
	}
	{
		typename Vector::difference_type len = ft::distance(vec1.begin(), ft::next(vec1.begin(), 4));
		typename Vector::iterator it = vec1.erase(vec1.begin(), ft::next(vec1.begin(), 4));
		typename Vector::difference_type n = ft::distance(vec1.begin(), it);
		PrintSizeAndCapacity(vec1);
		std::cout << "len: " << len << " / n: " << n << std::endl;
	}
	PrintSizeAndCapacity(vec1);
	PrintElements(vec1);
}
