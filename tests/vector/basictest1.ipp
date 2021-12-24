/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basictest1.ipp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 20:26:30 by smun              #+#    #+#             */
/*   Updated: 2021/12/24 22:48:34 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Vector BasicTest1
**
**  1. 기본 생성자
**  2. size()
**  3. capacity()
**  4. begin(), end(), iterator::operator*()
*/

template<typename Vector>
void	VectorTest<Vector>::BasicTest1()
{
	Vector vec;
	PrintSizeAndCapacity(vec);
	PrintElements(vec);
}
