/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stl_map.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 11:44:08 by smun              #+#    #+#             */
/*   Updated: 2022/01/21 12:18:22 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <map>
#include <iostream>
#include <string>

int main(void)
{
	std::map<int, std::string> m;

	m.insert(std::make_pair<int, std::string>(10, "I'm 10!"));
	m.insert(std::make_pair<int, std::string>(7, "I'm 7!"));
	m.insert(std::make_pair<int, std::string>(3, "I'm 3!"));
	m.insert(std::make_pair<int, std::string>(15, "I'm 15!"));

	std::map<int, std::string>::iterator it = m.begin();
	for (; it != m.end(); it++)
		std::cout << it->first << " - '" << it->second << "'" << std::endl;

	std::map<int, std::string>::value_compare v;

	return 0;
}
