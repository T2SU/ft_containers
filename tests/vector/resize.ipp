/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize.ipp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 20:26:30 by smun              #+#    #+#             */
/*   Updated: 2021/12/24 22:52:11 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Vector BasicTest2
**
**  1. resize() 함수
*/

template<typename Vector>
void	VectorTest<Vector>::Resize()
{
	Vector vec;
	vec.resize(100);
	vec.resize(static_cast<typename Vector::size_type>(500), 1234);
	vec.resize(static_cast<typename Vector::size_type>(250), 5678);
	vec.resize(static_cast<typename Vector::size_type>(375), 9876);
	PrintSizeAndCapacity(vec);
	PrintElements(vec);
}
