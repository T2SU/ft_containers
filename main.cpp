/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 19:04:19 by smun              #+#    #+#             */
/*   Updated: 2022/01/31 16:47:33 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/lib/unittest.hpp"
#include "tests/vector.hpp"
#include "tests/map.hpp"
#include "tests/stack.hpp"
#include "tests/set.hpp"
#include "utility.hpp"

/* Test contents are belongs to following files:
**   ./tests/vector/{TEST_NAME}.ipp
*/

static void	TestStringVector(ft::pair<int, int*> numpair)
{
	typedef ft::VectorTest<std::vector<std::string> >	ExpectedContTest;
	typedef ft::VectorTest<ft::vector<std::string> >	YourContTest;
	std::pair<int, int> d;

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
	REGISTER_EVAL(11, ut1, Erase1, "aaaaaaaaaaaaaaaaaaaaaaaAAAAAAAAAAAAAaaaaaaaaaaaaaaaa");
	REGISTER_EVAL(12, ut1, Erase2, "aaaaaaaaaaaaaaaaaaaaaaaAAAAAAAAAAAAAaaaaaaaaaaaaaaaa");
	REGISTER_EVAL(13, ut1, Erase_Empty, "&&");
	REGISTER_EVAL(14, ut1, Pop_Back, "aaaaaaaaaaaaaaaaaaaaaaaAAAAAAAAAAAAAaaaaaaaaaaaaaaaa");
	REGISTER_EVAL(15, ut1, Accessor1, "99", "**");
	END_EVAL;
}

static void	TestPairStringMap(ft::pair<int, int*> numpair)
{
	typedef ft::MapTest<std::map<int, std::string> >	ExpectedContTest;
	typedef ft::MapTest<ft::map<int, std::string> >		YourContTest;

	ft::UnitTest<ExpectedContTest, YourContTest> ut1;

	BEGIN_EVAL;
	REGISTER_EVAL(1, ut1, BasicTest1);
	END_EVAL;
}

static void	TestStringStack(ft::pair<int, int*> numpair)
{
	typedef ft::StackTest<std::stack<std::string> >	ExpectedContTest;
	typedef ft::StackTest<ft::stack<std::string> >		YourContTest;

	ft::UnitTest<ExpectedContTest, YourContTest> ut1;

	BEGIN_EVAL;
	REGISTER_EVAL(1, ut1, BasicTest1);
	END_EVAL;
}

static void	TestStringSet(ft::pair<int, int*> numpair)
{
	typedef ft::SetTest<std::set<std::string> >	ExpectedContTest;
	typedef ft::SetTest<ft::set<std::string> >		YourContTest;

	ft::UnitTest<ExpectedContTest, YourContTest> ut1;

	BEGIN_EVAL;
	REGISTER_EVAL(1, ut1, BasicTest1);
	END_EVAL;
}

enum
{
	All = -1,
	StringVector = 1 << 0,
	PairStringMap = 1 << 1,
	StringStack = 1 << 2,
	StringSet = 1 << 3
};

static int	parseCategories(int argc, char* argv[])
{
	int	ret = 0;
	for (int i = 1; i < argc; ++i)
	{
		const std::string	arg(argv[i]);
		if (arg == "--stringvector")
			ret |= StringVector;
		if (arg == "--pairstringmap")
			ret |= PairStringMap;
		if (arg == "--stringstack")
			ret |= StringStack;
		if (arg == "--stringset")
			ret |= StringSet;
	}
	if (ret == 0)
		ret = All;
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

	ft::map<int, int> m;
	ft::vector<int> v;
	//ft::map<int, int>::
	//ft::vector<int>::


	if (flags & StringVector)
	{
		std::cout << "[[ vector<std::string> ]]" << std::endl;
		TestStringVector(numpair);
		std::cout << std::endl;
	}
	if (flags & PairStringMap)
	{
		std::cout << "[[ map<int, std::string> ]]" << std::endl;
		TestPairStringMap(numpair);
		std::cout << std::endl;
	}
	if (flags & StringStack)
	{
		std::cout << "[[ stack<std::string> ]]" << std::endl;
		TestStringStack(numpair);
		std::cout << std::endl;
	}
	if (flags & StringSet)
	{
		std::cout << "[[ set<std::string> ]]" << std::endl;
		TestStringSet(numpair);
		std::cout << std::endl;
	}

	delete[] numpair.second;
	return 0;
}
