/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basictest2.ipp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 20:26:30 by smun              #+#    #+#             */
/*   Updated: 2021/12/25 12:09:55 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Vector BasicTest2
**
**  1. 복사 생성자
**  2. 대입 연산자
**  3. reserver() 함수
*/

void BasicTest2()
{
	Vector vec;
	vec.reserve(5000);
	Vector vec2 = vec;
	Vector vec3;
	vec3 = vec2;
	PrintSizeAndCapacity(vec3);
	PrintElements(vec3);
}
