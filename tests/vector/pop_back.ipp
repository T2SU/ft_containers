/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pop_back.ipp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 16:04:31 by smun              #+#    #+#             */
/*   Updated: 2022/01/03 17:01:54 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Vector Pop Back
**
**  1. pop_back() 함수
*/

void	Pop_Back(value_type val1)
{
	Vector vec1(5);
	for (int i = 0; i < 5; i++)
	{
		PrintSizeAndCapacity(vec1);
		vec1.push_back(val1);
	}
	for (int i = 0; i < 8; i++)
	{
		PrintSizeAndCapacity(vec1);
		vec1.pop_back();
	}
	PrintSizeAndCapacity(vec1);
	PrintElements(vec1);
}
