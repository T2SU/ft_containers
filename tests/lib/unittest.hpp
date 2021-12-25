/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unittest.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 20:18:30 by smun              #+#    #+#             */
/*   Updated: 2021/12/25 19:35:28 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_LIB_UNITTEST_HPP
# define TESTS_LIB_UNITTEST_HPP

# define RESET "\e[0m"
# define RED "\e[31m"
# define GREEN "\e[32m"
# define YELLOW "\e[33m"
# define BLUE "\e[34m"
# define REWIND "\e[2K\r"

# include <string>
# include <sstream>
# include <iostream>
# include <iomanip>
# include <sys/time.h>

# define BEGIN_EVAL \
for (unsigned long i = 1; ;++i) \
{ \
	switch(i) \
	{

# define _REGISTER_EVAL_REAL0(IDX, TESTOBJ, FUNCNAME) \
		case IDX: \
			if (!TESTOBJ.Eval \
					( \
						#FUNCNAME, \
						&decltype(TESTOBJ)::expected_test_type::FUNCNAME, \
						&decltype(TESTOBJ)::your_test_type::FUNCNAME \
					) \
				) \
				return; \
			break
# define _REGISTER_EVAL_REAL1(IDX, TESTOBJ, FUNCNAME, ARG1) \
		case IDX: \
			if (!TESTOBJ.Eval \
					( \
						#FUNCNAME, \
						&decltype(TESTOBJ)::expected_test_type::FUNCNAME, \
						&decltype(TESTOBJ)::your_test_type::FUNCNAME, \
						ARG1 \
					) \
				) \
				return; \
			break
# define _REGISTER_EVAL_REAL2(IDX, TESTOBJ, FUNCNAME, ARG1, ARG2) \
		case IDX: \
			if (!TESTOBJ.Eval \
					( \
						#FUNCNAME, \
						&decltype(TESTOBJ)::expected_test_type::FUNCNAME, \
						&decltype(TESTOBJ)::your_test_type::FUNCNAME, \
						ARG1, \
						ARG2 \
					) \
				) \
				return; \
			break
# define _REGISTER_EVAL_REAL3(IDX, TESTOBJ, FUNCNAME, ARG1, ARG2, ARG3) \
		case IDX: \
			if (!TESTOBJ.Eval \
					( \
						#FUNCNAME, \
						&decltype(TESTOBJ)::expected_test_type::FUNCNAME, \
						&decltype(TESTOBJ)::your_test_type::FUNCNAME, \
						ARG1, \
						ARG2, \
						ARG3 \
					) \
				) \
				return; \
			break

# define _GET_END_OF_ARG(IDX, TESTOBJ, FUNCNAME, ARG1, ARG2, ARG3, END, ...) END
# define _DO_TEST_EVAL_MACRO_CHOOSER(...) \
	_GET_END_OF_ARG(__VA_ARGS__, _REGISTER_EVAL_REAL3, \
				_REGISTER_EVAL_REAL2, _REGISTER_EVAL_REAL1, _REGISTER_EVAL_REAL0, )

# define REGISTER_EVAL(...) _DO_TEST_EVAL_MACRO_CHOOSER(__VA_ARGS__)(__VA_ARGS__)

# define END_EVAL \
		default: goto _END_TEST; \
	} \
} \
_END_TEST:

namespace ft
{
	class RedirectStd
	{
	private:
		std::ostream		&_os;
		std::streambuf		*_old;

		RedirectStd();
		RedirectStd(RedirectStd const&);
		RedirectStd& operator=(RedirectStd const&);
	public:
		virtual ~RedirectStd()
		{
			_os.rdbuf(_old);
		}

		RedirectStd(std::ostream& os, std::stringstream& ss)
			: _os(os)
		{
			_old = os.rdbuf(ss.rdbuf());
		}
	};

	template<typename ExpectedContTest, typename YourContTest>
	class UnitTest
	{
	public:
		typedef typename ExpectedContTest::value_type	value_type;
		typedef typename YourContTest::value_type		value_type2;

	private:
		ExpectedContTest	cont1;
		YourContTest		cont2;
		std::stringstream	cont1ss;
		std::stringstream	cont2ss;
		time_t				st1;
		time_t				et1;
		time_t				st2;
		time_t				et2;

		UnitTest(UnitTest const&);
		UnitTest& operator=(UnitTest const&);

		static time_t	GetTimeMicroseconds()
		{
			static time_t		start_s;
			static suseconds_t	start_us;
			struct timeval		t;
			time_t				seconds;
			suseconds_t			microseconds;

			gettimeofday(&t, NULL);
			if (!start_s)
			{
				start_s = t.tv_sec;
				start_us = t.tv_usec;
			}
			seconds = t.tv_sec - start_s;
			if (t.tv_usec > start_us)
				microseconds = t.tv_usec - start_us;
			else if (seconds > 0)
			{
				seconds--;
				microseconds = 1000000 + t.tv_usec - start_us;
			}
			else
				microseconds = 0;
			return (seconds * 1000000 + microseconds);
		}

		void	PrepareEval(const char* funcName)
		{

			cont1ss.str("");
			cont2ss.str("");
			std::cout << YELLOW << "Testing.... : [ " << std::setw(14) << std::left << funcName << "]" << RESET;
		}

		bool	CompleteEval(const char* funcName)
		{
			std::string const cont1out = cont1ss.str();
			std::string const cont2out = cont2ss.str();
			std::cout << REWIND;
			if (cont1out != cont2out)
			{
				std::cout << RED << "Test Failed : [ " << std::setw(14) << std::left << funcName << "] (STL:" << (et1 - st1) << "μs, Your:" << (et2 - st2) << "μs)" << RESET << std::endl;
				std::cout << GREEN << "=====> Expected output <=====" << std::endl;
				std::cout << cont1out << std::endl;
				std::cout << RED << "=====> Your output <=====" << std::endl;
				std::cout << cont2out << std::endl;
				std::cout << RESET;
				return false;
			}
			else
			{
				std::cout << GREEN << "Test Success: [ " << std::setw(14) << std::left << funcName << "] (STL:" << (et1 - st1) << "μs, Your:" << (et2 - st2) << "μs)" << RESET << std::endl;
				return true;
			}
		}

	public:
		UnitTest() {}
		virtual ~UnitTest() {}

		typedef	ExpectedContTest						expected_test_type;
		typedef YourContTest							your_test_type;

		bool	Eval(const char* funcName, void(ExpectedContTest::*fn1)(), void(YourContTest::*fn2)())
		{
			PrepareEval(funcName);
			{
				RedirectStd rdout(std::cout, cont1ss);
				RedirectStd rderr(std::cerr, cont1ss);
				st1 = GetTimeMicroseconds();
				(cont1.*fn1)();
				et1 = GetTimeMicroseconds();
			}
			{
				RedirectStd rdout(std::cout, cont2ss);
				RedirectStd rderr(std::cerr, cont2ss);
				st2 = GetTimeMicroseconds();
				(cont2.*fn2)();
				et2 = GetTimeMicroseconds();
			}
			return CompleteEval(funcName);
		}

		bool	Eval(const char* funcName, void(ExpectedContTest::*fn1)(value_type), void(YourContTest::*fn2)(value_type2), value_type arg1)
		{
			PrepareEval(funcName);
			{
				RedirectStd rdout(std::cout, cont1ss);
				RedirectStd rderr(std::cerr, cont1ss);
				st1 = GetTimeMicroseconds();
				(cont1.*fn1)(arg1);
				et1 = GetTimeMicroseconds();
			}
			{
				RedirectStd rdout(std::cout, cont2ss);
				RedirectStd rderr(std::cerr, cont2ss);
				st2 = GetTimeMicroseconds();
				(cont2.*fn2)(arg1);
				et2 = GetTimeMicroseconds();
			}
			return CompleteEval(funcName);
		}

		bool	Eval(const char* funcName, void(ExpectedContTest::*fn1)(value_type, value_type), void(YourContTest::*fn2)(value_type2, value_type2), value_type arg1, value_type arg2)
		{
			PrepareEval(funcName);
			{
				RedirectStd rdout(std::cout, cont1ss);
				RedirectStd rderr(std::cerr, cont1ss);
				st1 = GetTimeMicroseconds();
				(cont1.*fn1)(arg1, arg2);
				et1 = GetTimeMicroseconds();
			}
			{
				RedirectStd rdout(std::cout, cont2ss);
				RedirectStd rderr(std::cerr, cont2ss);
				st2 = GetTimeMicroseconds();
				(cont2.*fn2)(arg1, arg2);
				et2 = GetTimeMicroseconds();
			}
			return CompleteEval(funcName);
		}

		bool	Eval(const char* funcName, void(ExpectedContTest::*fn1)(value_type, value_type, value_type), void(YourContTest::*fn2)(value_type2, value_type2, value_type2), value_type arg1, value_type arg2, value_type arg3)
		{
			PrepareEval(funcName);
			{
				RedirectStd rdout(std::cout, cont1ss);
				RedirectStd rderr(std::cerr, cont1ss);
				st1 = GetTimeMicroseconds();
				(cont1.*fn1)(arg1, arg2, arg3);
				et1 = GetTimeMicroseconds();
			}
			{
				RedirectStd rdout(std::cout, cont2ss);
				RedirectStd rderr(std::cerr, cont2ss);
				st2 = GetTimeMicroseconds();
				(cont2.*fn2)(arg1, arg2, arg3);
				et2 = GetTimeMicroseconds();
			}
			return CompleteEval(funcName);
		}
	};
}

#endif
