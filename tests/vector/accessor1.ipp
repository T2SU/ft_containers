/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   accessor1.ipp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 20:26:30 by smun              #+#    #+#             */
/*   Updated: 2022/01/03 17:14:54 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Vector Accessor
**
**  1. front, back, data 함수
*/

void	Accessor1(value_type val1, value_type val2)
{
	Vector vec1;
	for (int i = 0; i < 10; i++)
	{
		vec1.push_back(val1);
		std::cout << vec1.back() << std::endl;
		std::cout << vec1.front() << std::endl;
		std::cout << *vec1.data() << std::endl;
	}
	{
		vec1.insert(vec1.begin(), 5, val2);
		std::cout << vec1.back() << std::endl;
		std::cout << vec1.front() << std::endl;
		std::cout << *vec1.data() << std::endl;
	}
	PrintSizeAndCapacity(vec1);
	PrintElements(vec1);
}
