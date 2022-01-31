/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 19:59:27 by smun              #+#    #+#             */
/*   Updated: 2022/01/31 16:37:36 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_STACK_HPP
# define TESTS_STACK_HPP

# include <iostream>
# include <stack>
# include "../stack.hpp"

namespace ft
{
	template<typename Stack>
	class StackTest
	{
	private:
		class MutantStack : public Stack
		{
		public:
			MutantStack() {}
			MutantStack(const MutantStack& src) { *this = src; }
			MutantStack& operator=(const MutantStack& rhs)
			{
				this->c = rhs.c;
				return *this;
			}
			~MutantStack() {}

			typedef typename Stack::container_type::iterator iterator;
			typedef typename Stack::container_type::const_iterator const_iterator;

			iterator begin() { return this->c.begin(); }
			iterator end() { return this->c.end(); }
			const_iterator begin() const { return this->c.begin(); }
			const_iterator end() const { return this->c.end(); }
		};

		StackTest(StackTest const&);
		StackTest& operator=(StackTest const&);

		void PrintSize(MutantStack const& st)
		{
			std::cout << "size:" << st.size() << std::endl;
		}

		void PrintElements(MutantStack const& st)
		{
			typename MutantStack::const_iterator it = st.begin();
			for (; it != st.end(); ++it)
				std::cout << *it << std::endl;
		}

	public:
		StackTest() {}
		virtual ~StackTest() {}

		typedef typename Stack::value_type	value_type;
		typedef typename Stack::size_type	size_type;

		#include "stack/basictest1.ipp"

	};

}

#endif
