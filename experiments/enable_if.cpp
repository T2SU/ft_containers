/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enable_if.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 14:24:52 by smun              #+#    #+#             */
/*   Updated: 2022/01/30 18:22:06 by smun             ###   ########.fr       */
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
	using std::string;

	string hello = "hello";

	ft::map<int, int> m;

	typedef ft::map<int, int>::pointer			pointer;
	typedef ft::map<int, int>::const_pointer	const_pointer;
	typedef ft::map<int, int>::reference		reference;
	typedef ft::map<int, int>::const_reference	const_reference;

	bool v = ft::is_convertible_to<pointer, const_pointer>::value;
	std::cout << v << std::endl;

	v = ft::is_convertible_to<reference, const_reference>::value;
	std::cout << v << std::endl;

	typedef ft::map<int, int>::iterator			iterator;
	typedef ft::map<int, int>::const_iterator	const_iterator;

	v = ft::is_convertible_to<iterator, const_iterator>::value;
	std::cout << v << std::endl;

	ft::map<int, int>::iterator it = m.begin();
	ft::map<int, int>::const_iterator it2 = m.end();

	it2 = it;
	bool v4 = it == it2;

	std::cout << v4 << std::endl;

	return 0;
}
