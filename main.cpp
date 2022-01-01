/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 19:04:19 by smun              #+#    #+#             */
/*   Updated: 2022/01/01 17:17:00 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/lib/unittest.hpp"
#include "tests/vector.hpp"

/* Test contents are belongs to following files:
**   ./tests/vector/{TEST_NAME}.ipp
*/

static void	TestIntVector()
{
	typedef ft::VectorTest<std::vector<int> >	ExpectedContTest;
	typedef ft::VectorTest<ft::vector<int> >	YourContTest;

	ft::UnitTest<ExpectedContTest, YourContTest> ut1;

	BEGIN_EVAL;
	REGISTER_EVAL(1, ut1, BasicTest1);
	REGISTER_EVAL(2, ut1, BasicTest2);
	REGISTER_EVAL(3, ut1, Resize, 1234, 5678, 9876);
	REGISTER_EVAL(4, ut1, Resize, 999555, 174534, 13333333);
	REGISTER_EVAL(5, ut1, Assign1, INT_MAX);
	REGISTER_EVAL(6, ut1, Assign2, INT_MAX);
	REGISTER_EVAL(7, ut1, Assign3, INT_MAX);
	END_EVAL;
}

static void	TestStringVector()
{
	typedef ft::VectorTest<std::vector<std::string> >	ExpectedContTest;
	typedef ft::VectorTest<ft::vector<std::string> >	YourContTest;

	ft::UnitTest<ExpectedContTest, YourContTest> ut1;

	BEGIN_EVAL;
	REGISTER_EVAL(1, ut1, BasicTest1);
	REGISTER_EVAL(2, ut1, BasicTest2);
	REGISTER_EVAL(3, ut1, Resize, "Hello", "World", "4242424242Fourty-Two");
	REGISTER_EVAL(4, ut1, Assign1, "aaaaaaaaaaaaaaaaaaaaaaaAAAAAAAAAAAAAaaaaaaaaaaaaaaaa");
	REGISTER_EVAL(5, ut1, Assign2, "aaaaaaaaaaaaaaaaaaaaaaaAAAAAAAAAAAAAaaaaaaaaaaaaaaaa");
	REGISTER_EVAL(6, ut1, Assign3, "aaaaaaaaaaaaaaaaaaaaaaaAAAAAAAAAAAAAaaaaaaaaaaaaaaaa");
	END_EVAL;
}

int main(void)
{
	TestStringVector();
	TestIntVector();
	return 0;
}
