/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enable_if.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 14:24:52 by smun              #+#    #+#             */
/*   Updated: 2021/12/25 14:52:12 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include <iostream>
#include <vector>
#include <iterator>

int main()
{
	std::enable_if<true, bool>();
	std::vector<int> vec2(50, 5);
	return 0;
}
