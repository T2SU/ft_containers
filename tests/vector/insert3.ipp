/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert3.ipp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 20:26:30 by smun              #+#    #+#             */
/*   Updated: 2022/01/02 14:08:21 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Vector Insert
**
**  1. insert(iterator pos, InputIt first, InputIt last) 함수
*/

void	Insert3(value_type val1, value_type val2)
{
	Vector vec1;
	for (int i = 0; i < 10; i++)
		vec1.push_back(val1);
	Vector vec2(10, val2);
	for (int i = 0; i < 3; i++)
	{
		PrintSizeAndCapacity(vec1);
		vec1.insert(ft::next(vec1.begin(), i), vec2.begin(), ft::next(vec2.begin(), i));
	}
	PrintSizeAndCapacity(vec1);
	PrintElements(vec1);
}
