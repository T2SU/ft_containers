/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 16:11:11 by smun              #+#    #+#             */
/*   Updated: 2022/01/31 16:24:38 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include <memory>
# include "vector.hpp"

namespace ft
{
	template<
		typename T,
		typename Container = ft::vector<T>
	>
	class stack
	{
	public:
		typedef Container							container_type;
		typedef typename Container::value_type		value_type;
		typedef typename Container::size_type		size_type;
		typedef typename Container::reference		reference;
		typedef typename Container::const_reference	const_reference;

		explicit
		stack(Container const& cont = Container())
			: c(cont)
		{}

		stack(stack const& other)
			: c(other.c)
		{}

		virtual ~stack() {}

		stack&	operator= (stack const& o)
		{
			c = o.c;
			return *this;
		}

		reference		top()				{ return c.back(); }
		const_reference	top() const			{ return c.back(); }
		bool			empty() const		{ return c.empty(); }
		size_type		size() const		{ return c.size(); }

		void push(const_reference value)	{ c.push_back(value); }
		void pop()							{ c.pop_back(); }

		friend bool operator==(stack const& lhs, stack const& rhs)
		{
			return lhs.c == rhs.c;
		}

		friend bool operator<(stack const& lhs, stack const& rhs)
		{
			return lhs.c < rhs.c;
		}

		friend bool operator!=(stack const& lhs, stack const& rhs)
		{
			return !(lhs == rhs);
		}

		friend bool operator<=(stack const& lhs, stack const& rhs)
		{
			return !(rhs < lhs);
		}

		friend bool operator>(stack const& lhs, stack const& rhs)
		{
			return rhs < lhs;
		}

		friend bool operator>=(stack const& lhs, stack const& rhs)
		{
			return !(lhs < rhs);
		}

	protected:
		Container	c;
	};
}

#endif
