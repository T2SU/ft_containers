#include <memory>
#include <iostream>

int main()
{
	std::allocator<long> a;
	std::allocator<int> b;
	std::cout << a.max_size() << std::endl;
	std::cout << b.max_size() << std::endl;

	return 0;
}
