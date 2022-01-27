/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_map_test.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 23:09:06 by smun              #+#    #+#             */
/*   Updated: 2022/01/27 17:21:38 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../map.hpp"
#include <iostream>
#include <string>
#include <map>

int main()
{
	ft::map<int, std::string> m;

	m[7] = "i am 7";
	m[15] = "i am 15!!";
	m[3] = "number three";
	m[5] = "number five";

	std::cout << m[7] << std::endl;
	std::cout << m[15] << std::endl;
	std::cout << m.at(3) << std::endl;
	std::cout << m[5] << std::endl;

	m[5] = "mc kkkkkkkkkkong FIVE!";

	std::cout << std::endl;

	ft::map<int, std::string>::iterator it;
	for (it = m.begin(); it != m.end(); ++it)
		std::cout << it->second << std::endl;

	std::cout << std::endl;

	for (it = m.end(); it != m.begin(); )
		std::cout << (--it)->second << std::endl;

	return 0;
}
