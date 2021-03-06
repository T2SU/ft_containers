/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basictest1.ipp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 20:26:30 by smun              #+#    #+#             */
/*   Updated: 2022/02/02 18:38:31 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Map BasicTest1
**
**  1. 기본 생성자
**  2. size()
**  4. begin(), end(), iterator::operator*()
*/

void	BasicTest1()
{
	Map map;
	for (int i = 0; i < 5; i++)
		map.insert(makePairForTest(i, "42 Fourty two"));
	for (int i = 0; i < 5; i++)
		map.insert(makePairForTest(i, "42 Fourty two 2"));
	for (int i = 0; i < 5; i++)
		map.insert(makePairForTest(i, "42 Fourty two 3"));
	for (int i = 0; i < 5; i++)
		map[i] = "42 Fourty two 5";
	for (int i = 0; i < 5; i++)
		map.insert(makePairForTest(i, "42 Fourty two 4"));
	PrintSize(map);
	PrintElements(map);
}
