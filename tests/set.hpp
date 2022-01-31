/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 14:33:40 by smun              #+#    #+#             */
/*   Updated: 2022/01/31 16:45:34 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_SET_HPP
# define TESTS_SET_HPP

# include <iostream>
# include <set>
# include "../set.hpp"

namespace ft
{
	template<typename Set>
	class SetTest
	{
	private:
		SetTest(SetTest const&);
		SetTest& operator=(SetTest const&);

		void PrintSize(Set const& set)
		{
			std::cout << "size:" << set.size() << std::endl;
		}

		void PrintElements(Set const& set)
		{
			typename Set::const_iterator it = set.begin();
			typename Set::const_iterator end = set.end();
			for (; it != end; ++it)
				std::cout << *it << std::endl;
		}

	public:
		SetTest() {}
		virtual ~SetTest() {}

		typedef typename Set::key_type		key_type;
		typedef typename Set::value_type	value_type;
		typedef typename Set::size_type		size_type;

		# include "set/basictest1.ipp"
	};
}

#endif
