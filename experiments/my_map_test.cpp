/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_map_test.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 23:09:06 by smun              #+#    #+#             */
/*   Updated: 2022/01/31 17:07:40 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../map.hpp"
#include <iostream>
#include <string>
#include <map>

int main()
{
	/*ft::map<std::pair<int, std::string>, std::string> m;

	std::cout << "size: " << m.size() << std::endl;

	ft::map<std::pair<int, std::string>, std::string>::iterator it;
	for (it = m.begin(); it != m.end(); ++it)
			std::cout << "[(" << it->first.first << "," << it->first.second << ")-" << it->second << "]" << std::endl;*/

	ft::map<int, std::string> m;

	m[7]	= "i am 7";
	m[15]	= "i am 15!!";
	m[3]	= "numb 3";
	m[5]	= "numb 5";

	if (m[7] != "i am 7")
		assert("not matched m[7]");
	if (m[15] != "i am 15!!")
		assert("not matched m[15]");
	if (m[3] != "numb 3")
		assert("not matched m[3]");
	if (m[5] != "numb 5")
		assert("not matched m[5]");

	m.insert(ft::make_pair<const int, std::string>(10, "Good"));
	m.insert(ft::make_pair(11, "Not Good"));

	std::map<int, std::string> sm;
	sm.insert(std::make_pair(10, "Good?"));

	std::cout << "size: " << m.size() << std::endl;
	ft::map<int, std::string>::iterator it;
	for (it = m.begin(); it != m.end(); ++it)
		std::cout << it->second << std::endl;

	m.clear();

	std::cout << "size: " << m.size() << std::endl;
	std::cout << std::endl;
	m.erase(3);
	m.erase(15);
	m[10] = "NEW!!! FACE (10)";
	m[3] =  "NEWNEW FACE (3)";

	std::cout << "size: " << m.size() << std::endl;
	for (it = m.end(); it != m.begin(); )
		std::cout << (--it)->second << std::endl;


	return 0;
}
