/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 19:04:19 by smun              #+#    #+#             */
/*   Updated: 2021/12/24 15:05:23 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include "vector.hpp"
#include "algorithm.hpp"

int main(void)
{
	ft::vector<int> v;

	std::cout << "size: " << v.size() << " / capacity: " << v.capacity() << std::endl;
	v.push_back(1);
	std::cout << "size: " << v.size() << " / capacity: " << v.capacity() << std::endl;
	v.push_back(2);
	std::cout << "size: " << v.size() << " / capacity: " << v.capacity() << std::endl;
	v.insert(v.begin(), 3, 1234);
	std::cout << "size: " << v.size() << " / capacity: " << v.capacity() << std::endl;

	ft::vector<int> v2 = v;
	v.insert(ft::next(v.begin()), ft::next(v2.begin(), 2), v2.end());

	ft::vector<int>::iterator it = v.begin();
	for (; it != v.end(); ++it)
		std::cout << *it << std::endl;
	return 0;
}
