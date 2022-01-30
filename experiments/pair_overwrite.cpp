#include <string>
#include <map>
#include <iostream>

int main(void)
{
	std::map<int, std::string> m;

	typedef std::map<int, std::string>::iterator iterator;
	typedef std::pair<int, std::string> _pair;

	m.insert(std::pair<int, std::string>(42, "hello"));
	iterator ret = m.insert(m.end(), _pair(42, "goodboy"));

	std::cout << ret->first << std::endl;
	std::cout << ret->second << std::endl;

	return 0;
}
