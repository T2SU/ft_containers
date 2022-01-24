/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_map_test.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 23:09:06 by smun              #+#    #+#             */
/*   Updated: 2022/01/24 20:53:40 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../map.hpp"
#include <iostream>
#include <string>

int main()
{
	ft::map<int, std::string> m;

	m[7] = "i am 7";
	m[15] = "i am 4!!";
	m[3] = "number one";
	m[5] = "kong";

	//ft::map<int, int>::iterator it;
	//for (it = m.begin(); it != m.end(); ++it)
	//	std::cout << it->second << std::endl;
	std::cout << m[7] << std::endl;
	std::cout << m[15] << std::endl;
	std::cout << m[3] << std::endl;
	std::cout << m[5] << std::endl;

	m[5] = "kkkkkkkkkkong";
	std::cout << m[5] << std::endl;

	return 0;
}
