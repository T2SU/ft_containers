/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert1.ipp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 20:26:30 by smun              #+#    #+#             */
/*   Updated: 2022/01/01 19:52:31 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Vector Insert
**
**  1. insert(iterator pos, T const value) 함수
*/

void	Insert1(value_type val1, value_type val2)
{
	Vector vec1(5);
	for (int i = 0; i < 5; i++)
		vec1.push_back(val1);
	for (int i = 0; i < 10; i++)
	{
		PrintSizeAndCapacity(vec1);
		typename Vector::iterator inserted = vec1.insert(ft::next(vec1.begin(), i * 2), val2);
		std::cout << *inserted << "(" << ft::distance(vec1.begin(), inserted) << ")" << std::endl;
	}
	PrintSizeAndCapacity(vec1);
	PrintElements(vec1);
}
