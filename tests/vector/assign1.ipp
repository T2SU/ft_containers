/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign1.ipp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 20:26:30 by smun              #+#    #+#             */
/*   Updated: 2022/01/01 17:14:57 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Vector Assignment (Replacement)
**
**  1. assign() 함수
*/

void	Assign1(value_type val1)
{
	Vector vec1(50, val1);
	PrintSizeAndCapacity(vec1);
	PrintElements(vec1);
}
