#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>

int main()
{
	std::vector<int> d1;
	std::vector<int> d2;

	std::lexicographical_compare(d1.begin(), d1.end(), d2.begin(), d2.end());
	// std::equal();

	return 0;
}
