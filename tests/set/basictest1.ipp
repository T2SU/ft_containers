/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basictest1.ipp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 16:43:07 by smun              #+#    #+#             */
/*   Updated: 2022/02/02 18:41:13 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	BasicTest1()
{
	Set	set;
	for (int i = 0; i < 5; i++)
		set.insert("42 Fourty two");
	for (int i = 0; i < 5; i++)
		set.insert("42 Fourty two 2");
	for (int i = 0; i < 5; i++)
		set.insert("42 Fourty two 3");
	for (int i = 0; i < 5; i++)
		set.insert("42 Fourty two 4");
	for (int i = 0; i < 5; i++)
		set.insert("42 Fourty two 5");
	PrintSize(set);
	PrintElements(set);
	for (int i = 0; i < 5; i++)
		set.erase("42");
	PrintSize(set);
	PrintElements(set);
	for (int i = 0; i < 5; i++)
		set.erase("");
	PrintSize(set);
	PrintElements(set);
	set.clear();
	PrintSize(set);
	PrintElements(set);
}
