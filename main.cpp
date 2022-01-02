/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 19:04:19 by smun              #+#    #+#             */
/*   Updated: 2022/01/02 14:12:05 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/lib/unittest.hpp"
#include "tests/vector.hpp"
#include "utility.hpp"

/* Test contents are belongs to following files:
**   ./tests/vector/{TEST_NAME}.ipp
*/

static void	TestStringVector(ft::pair<int, int*> numpair)
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
	REGISTER_EVAL(7, ut1, Push_Back, "aaaaaaaaaaaaaaaaaaaaaaaAAAAAAAAAAAAAaaaaaaaaaaaaaaaa", "--");
	REGISTER_EVAL(8, ut1, Insert1, "aaaaaaaaaaaaaaaaaaaaaaaAAAAAAAAAAAAAaaaaaaaaaaaaaaaa", "++");
	REGISTER_EVAL(9, ut1, Insert2, "aaaaaaaaaaaaaaaaaaaaaaaAAAAAAAAAAAAAaaaaaaaaaaaaaaaa", "**");
	REGISTER_EVAL(10, ut1, Insert3, "aaaaaaaaaaaaaaaaaaaaaaaAAAAAAAAAAAAAaaaaaaaaaaaaaaaa", "^^");
	END_EVAL;
}

enum
{
	Undefined = 0,
	StringVector = 1 << 0
};

static int	parseCategories(int argc, char* argv[])
{
	int	ret = Undefined;
	for (int i = 1; i < argc; ++i)
	{
		const std::string	arg(argv[i]);
		if (arg == "--stringvector")
			ret = StringVector;
	}
	return ret;
}

static ft::pair<int, int*>	parseNumbers(int argc, char* argv[])
{
	int*	nums = new int[argc];
	int		count = 0;
	int*	ret;
	int		counter = argc;

	while (counter-- > 0)
	{
		nums[counter] = -1;
		try
		{
			nums[counter] = std::stoi(argv[counter]);
			++count;
		}
		catch (std::exception)
		{
		}
	}
	if (count > 0)
	{
		ret = new int[count];
		int k = 0;
		for (int i = 1; i < argc; ++i)
			if (nums[i] != -1)
				ret[k++] = nums[i];
	}
	else
		ret = nullptr;
	delete[] nums;
	return ft::make_pair<int, int*>(count, ret);
}

int main(int argc, char* argv[])
{
	int	flags = parseCategories(argc, argv);
	ft::pair<int, int*>	numpair = parseNumbers(argc, argv);

	if (flags == Undefined || flags == StringVector)
		TestStringVector(numpair);

	delete[] numpair.second;
	return 0;
}
