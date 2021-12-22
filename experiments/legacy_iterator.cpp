#include <iterator>
#include <iostream>
#include <vector>
#include <string>

int main()
{
	std::vector<int> vi;
	std::vector<std::string> vs;

	std::vector<int>::iterator begin = vi.begin();
	vi.push_back(12345);
	std::vector<int>::iterator end = vi.end();

	//std::cout << *reinterpret_cast<long*>(&begin) << std::endl;
	//std::cout << *reinterpret_cast<long*>(&end) << std::endl;


	begin--;
	std::cout << *reinterpret_cast<long*>(&begin) << std::endl;
	begin--;
	std::cout << *reinterpret_cast<long*>(&begin) << std::endl;
	begin--;
	std::cout << *reinterpret_cast<long*>(&begin) << std::endl;
	end--;
	std::cout << *reinterpret_cast<long*>(&end) << std::endl;
	end--;
	std::cout << *reinterpret_cast<long*>(&end) << std::endl;
	end--;
	std::cout << *reinterpret_cast<long*>(&end) << std::endl;

	std::cout << sizeof(std::vector<int>::iterator::difference_type) << std::endl;

	int *i = 0, *j = 0;
	std::cout << i << std::endl;
	i++;
	std::cout << i << std::endl;
	i++;
	std::cout << i << std::endl;
	i++;
	std::cout << i << std::endl;

	std::cout << std::distance(j, i) << std::endl;

	std::random_access_iterator_tag;


	return 0;
}
