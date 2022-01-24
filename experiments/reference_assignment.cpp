/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reference_assignment.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 18:57:53 by smun              #+#    #+#             */
/*   Updated: 2022/01/21 22:01:39 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <map>

int main(void)
{
	int i = 1234;

	int& a = i;
	int& b = a;
	int k = i;
	int j = 5555;
	b = j;

	std::cout << &i << std::endl;
	std::cout << &a << std::endl;
	std::cout << &b << std::endl;
	std::cout << &j << std::endl;
	std::cout << k << std::endl;
	std::cout << i << std::endl;

	std::map<int, std::string> m;
	m[3] = "Hello";
	std::map<int, std::string>::iterator it = m.begin();
	++it;

	return 0;
}
