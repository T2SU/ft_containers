/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basictest1.ipp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 16:35:59 by smun              #+#    #+#             */
/*   Updated: 2022/01/31 16:37:04 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void BasicTest1()
{
	MutantStack st;
	for (int i = 0; i < 10; i++)
		st.push("Hello Hello");
	PrintSize(st);
	PrintElements(st);
	for (int i = 0; i < 10; i++)
		st.pop();
	PrintSize(st);
	PrintElements(st);
}
