/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 19:04:19 by smun              #+#    #+#             */
/*   Updated: 2022/01/02 13:34:58 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/lib/unittest.hpp"
#include "tests/vector.hpp"
#include "utility.hpp"

/* Test contents are belongs to following files:
**   ./tests/vector/{TEST_NAME}.ipp
*/

static void	TestIntVector(ft::pair<int, int*> numpair)
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
	REGISTER_EVAL(8, ut1, PushBack, INT_MIN, INT_MAX);
	REGISTER_EVAL(9, ut1, Insert1, INT_MIN, INT_MAX);
	END_EVAL;
}

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
	REGISTER_EVAL(7, ut1, PushBack, "aaaaaaaaaaaaaaaaaaaaaaaAAAAAAAAAAAAAaaaaaaaaaaaaaaaa", "--");
	REGISTER_EVAL(8, ut1, Insert1, "aaaaaaaaaaaaaaaaaaaaaaaAAAAAAAAAAAAAaaaaaaaaaaaaaaaa", "++");
	END_EVAL;
}

enum
{
	Undefined = 0,
	StringVector = 1 << 0,
	IntVector = 1 << 1
};

static int	parseCategories(int argc, char* argv[])
{
	int	ret = Undefined;
	for (int i = 1; i < argc; ++i)
	{
		const std::string	arg(argv[i]);
		if (arg == "--stringvector")
			ret = StringVector;
		else if (arg == "--intvector")
			ret = IntVector;
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
	if (flags == Undefined || flags == IntVector)
		TestIntVector(numpair);

	delete[] numpair.second;
	return 0;
}
