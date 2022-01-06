/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize.ipp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 20:26:30 by smun              #+#    #+#             */
/*   Updated: 2022/01/06 10:57:48 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Vector Resize
**
**  1. resize() 함수
*/

void	Resize(value_type val1, value_type val2, value_type val3)
{
	Vector vec;

	vec.resize(100);		// Resize (100)
	vec.resize(500, val1);	// Resize (500, val1)
	vec.resize(250, val2);	// Resize (250, val2)
	vec.resize(375, val3);	// Resize (375, val3)

	PrintSizeAndCapacity(vec);
	PrintElements(vec);
}
