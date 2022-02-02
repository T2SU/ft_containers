/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basictest2.ipp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 20:26:30 by smun              #+#    #+#             */
/*   Updated: 2022/02/02 18:40:19 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Map BasicTest2
**
**  1. insert, erase
**  2. clear
*/

void	BasicTest2()
{
	Map map;
	for (int i = 0; i < 500; i++)
		map.insert(makePairForTest(i, "42 Fourty two"));
	for (int i = -500; i < 300; i++)
		map.erase(i);
	PrintSize(map);
	PrintElements(map);
	map.clear();
	PrintSize(map);
	PrintElements(map);
	for (int i = -500; i < 300; i++)
		map.erase(i);
	PrintSize(map);
	PrintElements(map);
}
