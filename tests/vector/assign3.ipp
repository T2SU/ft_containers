/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign3.ipp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 20:26:30 by smun              #+#    #+#             */
/*   Updated: 2022/01/01 17:17:16 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Vector Assignment (Replacement)
**
**  1. assign() 함수
*/

void	Assign3(value_type val1)
{
	Vector vec3;
	vec3.assign(10, val1);
	PrintSizeAndCapacity(vec3);
	PrintElements(vec3);
}
