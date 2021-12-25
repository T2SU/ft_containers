#include <iostream>
#include "type_traits.hpp"
#include "vector.hpp"

class A {};
class B : private A {};
class C : public B {};

int main()
{
	std::cout << ft::has_iterator_typedef<ft::vector<int>::iterator>::value << std::endl;
	std::cout << ft::is_input_iterator<ft::vector<int>::iterator>::value << std::endl;
	std::cout << ft::is_input_iterator<int>::value << std::endl;
	std::cout << ft::is_base_of<ft::input_iterator_tag, ft::iterator_traits<ft::vector<int>::iterator>::iterator_category>::value << std::endl;
	std::cout << ft::is_base_of<ft::input_iterator_tag, ft::input_iterator_tag>::value << std::endl;

	return 0;
}
