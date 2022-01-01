/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_back.ipp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 20:26:30 by smun              #+#    #+#             */
/*   Updated: 2022/01/01 18:02:17 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Vector Push Back
**
**  1. push_back() 함수
*/

void	PushBack(value_type val1, value_type val2)
{
	Vector vec1(5);
	for (int i = 0; i < 5; i++)
	{
		PrintSizeAndCapacity(vec1);
		vec1.push_back(val1);
	}
	for (int i = 0; i < 5; i++)
	{
		PrintSizeAndCapacity(vec1);
		vec1.push_back(val2);
	}
	PrintSizeAndCapacity(vec1);
	PrintElements(vec1);
}
