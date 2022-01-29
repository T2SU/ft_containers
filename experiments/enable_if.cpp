/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enable_if.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 14:24:52 by smun              #+#    #+#             */
/*   Updated: 2022/01/29 19:07:29 by smun             ###   ########.fr       */
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

/*template<typename T>
void
test_EnableIf_At_Paramter(
	typename ft::enable_if<ft::is_input_iterator<T>::value, T>::type first,
	typename ft::enable_if<ft::is_input_iterator<T>::value, T>::type last)
{
	while (first != last)
		std::cout << *(first++) << std::endl;
}*/

template<typename T>
typename ft::enable_if<ft::is_input_iterator<T>::value, void>::type
test_EnableIf_At_ReturnType(
	T first,
	T last)
{
	while (first != last)
		std::cout << *(first++) << std::endl;
}

int main()
{
	std::list<int> lst;
	lst.push_back(1);
	lst.push_back(2);
	lst.push_back(3);

	ft::vector<std::pair<int, int> > myvec;
	typedef ft::vector<std::pair<int, int> >::pointer p;
	typedef ft::vector<std::pair<int, int> >::const_pointer cp;
	typedef ft::vector<std::pair<int, int> >::const_iterator constit;
	typedef ft::vector<std::pair<int, int> >::iterator it;

	std::vector<int> dd;
	dd.begin();

	bool v = ft::is_base_of<cp, p>::value;
	std::cout << v << std::endl;

	ft::vector<std::pair<int, int> > vec;
	it t = vec.begin();
	constit t2 = vec.end();


	bool cv = ft::is_convertible_to<std::pair<int, int>*, const std::pair<int, int>*>::value;
	//bool cv = t != t2;
	std::cout << cv << std::endl;

	//test_EnableIf_At_Paramter(lst.begin(), lst.end());
	test_EnableIf_At_ReturnType(lst.begin(), lst.end());
	return 0;
}
