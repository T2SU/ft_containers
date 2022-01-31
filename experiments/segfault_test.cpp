/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segfault_test.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 17:27:47 by smun              #+#    #+#             */
/*   Updated: 2022/01/31 19:01:37 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <map>
#include "../map.hpp"

static void fillMap(ft::map<int, int>& mp)
{
	mp.insert(ft::make_pair(16, 3));
	mp.insert(ft::make_pair(8, 3));
	mp.insert(ft::make_pair(23, 3));
	mp.insert(ft::make_pair(7, 3));
	mp.insert(ft::make_pair(19, 3));
	mp.insert(ft::make_pair(29, 3));
	mp.insert(ft::make_pair(41, 3));
	mp.insert(ft::make_pair(4, 3));
	mp.insert(ft::make_pair(11, 3));
}

typedef int T;
typedef int V;
#define _map std::map
#define _ratio 30
#define _make_pair std::make_pair

std::vector<int> size_test(_map<T, V> mp, _map<T, V> m2)
{
	std::vector<int> v;
    v.push_back(mp.erase(3));
    for (int i = 0, j = 0; i < 30 * _ratio; ++i, ++j)
        mp.insert(_make_pair(i, j));
    _map<T, V>::iterator it = mp.begin();
    v.push_back(it->first);
    v.push_back(mp.erase(-5));
    v.push_back(mp.size());
    v.push_back(mp.erase(0));
    v.push_back(mp.size());
    it = mp.begin();
    v.push_back(it->first);
    _map<T, V>::iterator it4 = mp.begin();
    for (; it4 != mp.end(); it4 = mp.begin())
        mp.erase(it4->first);
	std::cout << mp.size() << std::endl;
    _map<T, V>::iterator it2 = mp.end();
    it2--;
    v.push_back(mp.erase(30 * _ratio - 1));
    v.push_back(mp.size());
    _map<int, int> mp2;
    for (int i = 0, j = 0; i < 10 ; ++i, ++j)
        mp2.insert(_make_pair(i, j));
    mp2.erase(2);
    mp2.erase(7);
    _map<T, V>::iterator it3 = mp2.begin();
    for (; it3 != mp2.end(); ++it3) {
        v.push_back(it3->first);
        v.push_back(it3->second);
    }
    return v;
}

static void my_map_test(_map<T, V> mp)
{
	_map<T, V> mpp;

	size_test(mp, mpp);
}

int main(void)
{
	_map<T, V> dd;

	for (int i = 0; i < 10; i++)
		dd.insert(_make_pair(i, i * 10));

    _map<T, V>::iterator it4 = dd.begin();
    for (; it4 != dd.end(); it4 = dd.begin())
        dd.erase(it4->first);

	//_map<T, V>::iterator it = dd.end();
	//it--;

	_map<T, V> mp;

	my_map_test(mp);

	system("leaks segfault_test.out");

	return 0;
}
