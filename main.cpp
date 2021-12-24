/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 19:04:19 by smun              #+#    #+#             */
/*   Updated: 2021/12/24 23:00:31 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/lib/unittest.hpp"
#include "tests/vector.hpp"

static void	TestVector()
{
	typedef ft::VectorTest<std::vector<int> >	ExpectedContTest;
	typedef ft::VectorTest<ft::vector<int> >	YourContTest;

	ft::UnitTest<ExpectedContTest, YourContTest> ut1;

	/* Test contents are belongs to following files:
	**   ./tests/vector/{TEST_NAME}.ipp
	*/

	BEGIN_EVAL;
	REGISTER_EVAL(1, ut1, BasicTest1);
	REGISTER_EVAL(2, ut1, BasicTest2);
	REGISTER_EVAL(3, ut1, Resize);
	END_EVAL;
}

int main(void)
{
	TestVector();
	return 0;
}
