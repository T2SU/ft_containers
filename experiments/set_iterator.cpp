#include <set>
#include <iostream>
#include <string>
#include "../set.hpp"

int main()
{
	std::set<int> s;
	std::set<int>::const_iterator it2 = s.begin();
	std::set<int>::iterator it = it2;

	ft::set<int> ft_s;
	ft::set<int>::const_iterator ft_it2 = ft_s.begin();
	ft::set<int>::iterator ft_it = ft_it2;
	return 0;
}
