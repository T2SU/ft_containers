/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 19:04:19 by smun              #+#    #+#             */
/*   Updated: 2021/12/25 13:29:58 by smun             ###   ########.fr       */
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
	END_EVAL;
}

int main(void)
{
	TestIntVector();
	TestStringVector();
	return 0;
}
