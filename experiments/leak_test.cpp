/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leak_test.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 17:27:47 by smun              #+#    #+#             */
/*   Updated: 2022/01/31 19:05:58 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <map>
#include "../map.hpp"

#define _map std::map
#define _make_pair std::make_pair
typedef std::plus<int> Compare;

static void fillMap(_map<int, int, Compare>& mp)
{
	mp.insert(_make_pair(16, 3));
	mp.insert(_make_pair(8, 3));
	mp.insert(_make_pair(23, 3));
	mp.insert(_make_pair(7, 3));
	mp.insert(_make_pair(19, 3));
	mp.insert(_make_pair(29, 3));
	mp.insert(_make_pair(41, 3));
	mp.insert(_make_pair(4, 3));
	mp.insert(_make_pair(11, 3));
}

std::vector<int> size_test(_map<int, int, Compare> mp)
{
	std::vector<int> v;
	for (int i = 0, j = 0; i < 100 * 30; ++i, ++j)
		mp.insert(_make_pair(i, j));
	v.push_back(mp.size());
	for (int i = 0; i < 43 * 30; ++i)
		mp.erase(i);
	v.push_back(mp.size());
	return v;
}

static void my_map_test(_map<int, int, Compare> mp)
{
	_map<int, int, Compare> mpp;


}

int main(void)
{
	_map<int, int, Compare> mp;

	my_map_test(mp);
	size_test(mp);

	fillMap(mp);

	_map<int, int, Compare>::const_iterator it = mp.begin();
	for (; it != mp.end(); ++it)
		std::cout << it->first << std::endl;

	//system("leaks leak_test.out");

	return 0;
}
