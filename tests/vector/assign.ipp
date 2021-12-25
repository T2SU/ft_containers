/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign.ipp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 20:26:30 by smun              #+#    #+#             */
/*   Updated: 2021/12/25 19:33:52 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Vector Assignment (Replacement)
**
**  1. assign() 함수
*/

void	Assign(value_type val1)
{
	Vector vec1(50, val1);
	//Vector vec2(30);
	//vec2.assign(vec1.begin(), vec1.begin() + 5);
	//Vector vec3;
	//vec3.assign(10, value_type());
	//vec3.assign(vec2.begin(), vec2.end());
	PrintSizeAndCapacity(vec1);
	PrintElements(vec1);
}
