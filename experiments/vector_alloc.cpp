#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>

int main()
{
	std::vector<int> vi(3);
	std::vector<int> vi2 = vi;

	std::allocator<int> al;
	std::pair<int, int> dd;

	std::cout << vi.size() << "/" << vi.capacity() << std::endl;
	vi.push_back(5);
	std::cout << vi.size() << "/" << vi.capacity() << std::endl;
	vi.assign(5, 1);
	std::cout << vi.size() << "/" << vi.capacity() << std::endl;
	vi.assign(10, 5);
	std::cout << vi.size() << "/" << vi.capacity() << std::endl;
	vi.push_back(5);
	std::cout << vi.size() << "/" << vi.capacity() << std::endl;
	vi.assign(0, -1);
	std::cout << vi.size() << "/" << vi.capacity() << std::endl;

	vi.resize(5);
	std::cout << vi.size() << "/" << vi.capacity() << std::endl;

	return 0;
}
