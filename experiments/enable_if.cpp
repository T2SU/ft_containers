/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enable_if.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 14:24:52 by smun              #+#    #+#             */
/*   Updated: 2022/01/29 15:37:24 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <list>
#include <map>
#include "../type_traits.hpp"
#include "../iterator.hpp"

int main()
{
	std::list<int> lst;

	typedef std::list<int>::iterator		list_iterator;
	typedef std::map<int, int>::iterator	map_iterator;

	bool v = ft::is_base_of<std::input_iterator_tag, list_iterator::iterator_category>::value;
	bool v2 = ft::is_base_of<std::random_access_iterator_tag, map_iterator::iterator_category>::value;
	bool v3 = ft::is_base_of<std::input_iterator_tag, map_iterator::iterator_category>::value;
	std::cout << v << std::endl;
	std::cout << v2 << std::endl;
	std::cout << v3 << std::endl;
	return 0;
}
