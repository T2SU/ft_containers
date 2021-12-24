/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unittest.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 20:18:30 by smun              #+#    #+#             */
/*   Updated: 2021/12/24 22:53:35 by smun             ###   ########.fr       */
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

# include <csignal>
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

# define REGISTER_EVAL(IDX, TESTOBJ, FUNCNAME) \
		case IDX: if (!TESTOBJ.Eval(#FUNCNAME, &decltype(TESTOBJ)::expected_test_type::FUNCNAME, &decltype(TESTOBJ)::your_test_type::FUNCNAME)) return; break

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
	private:
		ExpectedContTest	cont1;
		YourContTest		cont2;
		std::stringstream	cont1ss;
		std::stringstream	cont2ss;

		UnitTest(UnitTest const&);
		UnitTest& operator=(UnitTest const&);

		static void	HandleSig(int sig)
		{
			if (sig == SIGABRT)
				std::cerr << "Aborted" << std::endl;
			else if (sig == SIGSEGV)
				std::cerr << "Segmentation Fault" << std::endl;
			else if (sig == SIGBUS)
				std::cerr << "Bus Error" << std::endl;
			else if (sig == SIGALRM)
				std::cerr << "!! Timed-out !!" << std::endl;
			else
				std::cerr << "Signal: " << sig << std::endl;
		}

		static void	EnableSigHandler(void(*fn)(int))
		{
			std::signal(SIGABRT, fn);
			std::signal(SIGSEGV, fn);
			std::signal(SIGBUS, fn);
		}

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

	public:
		UnitTest() {}
		virtual ~UnitTest() {}

		typedef	ExpectedContTest	expected_test_type;
		typedef YourContTest		your_test_type;

		bool	Eval(const char* funcName, void(ExpectedContTest::*fn1)(), void(YourContTest::*fn2)())
		{
			time_t st1, et1, st2, et2;

			cont1ss.str("");
			cont2ss.str("");
			std::cout << YELLOW << "Testing.... : [ " << std::setw(14) << std::left << funcName << "]" << RESET;
			EnableSigHandler(&HandleSig);
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
			EnableSigHandler(SIG_DFL);
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
	};
}

#endif
