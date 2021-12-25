/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basictest1.ipp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 20:26:30 by smun              #+#    #+#             */
/*   Updated: 2021/12/25 12:09:42 by smun             ###   ########.fr       */
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

void	BasicTest1()
{
	Vector vec;
	PrintSizeAndCapacity(vec);
	PrintElements(vec);
}
