/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert2.ipp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 20:26:30 by smun              #+#    #+#             */
/*   Updated: 2022/01/02 13:56:53 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Vector Insert
**
**  1. insert(iterator pos, size_type n, T const value) 함수
*/

void	Insert2(value_type val1, value_type val2)
{
	Vector vec1;
	for (int i = 0; i < 10; i++)
		vec1.push_back(val1);
	for (int i = 0; i < 10; i++)
	{
		PrintSizeAndCapacity(vec1);
		vec1.insert(ft::next(vec1.begin(), i + 2), i, val2);
	}
	PrintSizeAndCapacity(vec1);
	PrintElements(vec1);
}
