/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign2.ipp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 20:26:30 by smun              #+#    #+#             */
/*   Updated: 2022/01/01 17:16:27 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Vector Assignment (Replacement)
**
**  1. assign() 함수
*/

void	Assign2(value_type val1)
{
	Vector vec1;
	vec1.resize(50, val1);
	Vector vec2(30);
	vec2.assign(vec1.begin(), vec1.begin() + 5);
	PrintSizeAndCapacity(vec2);
	PrintElements(vec2);
}
