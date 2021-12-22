#include <iostream>
#include <vector>

int main()
{
	std::vector<int> v;

	v.push_back(10);
	v.push_back(20);
	v.push_back(30);
	v.capacity();
	for (std::vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		std::cout << "capacity: " << v.capacity() << " / size: " << v.size() << std::endl;
		v.push_back((*it) + 5);
	}
	for (std::vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		std::cout << *it << std::endl;
	}
	return 0;
}
