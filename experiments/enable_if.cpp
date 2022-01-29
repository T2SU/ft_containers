/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enable_if.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 14:24:52 by smun              #+#    #+#             */
/*   Updated: 2022/01/29 19:38:13 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <list>
#include <map>
#include <vector>
#include <iterator>
#include <type_traits>
#include "../type_traits.hpp"
#include "../iterator.hpp"
#include "../vector.hpp"
#include "../map.hpp"

int main()
{
	ft::map<int, int> m;

	ft::map<int, int>::iterator it = m.begin();
	ft::map<int, int>::const_iterator it2 = m.end();

	bool v = it != it2;
	std::cout << v << std::endl;

	it2 = it;
	bool v2 = it == it2;
	std::cout << v2 << std::endl;

	return 0;
}
