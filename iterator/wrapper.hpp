/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 22:48:46 by smun              #+#    #+#             */
/*   Updated: 2021/12/23 22:55:35 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRAPPER_HPP
# define WRAPPER_HPP

# include "base.hpp"

namespace ft
{
	template<typename Iter>
	class IteratorWrapper
	{
	protected:
		Iter	current;

	public:
		typedef Iter										iterator_type;
		typedef iterator_traits<Iter>::value_type			value_type;
		typedef iterator_traits<Iter>::difference_type		difference_type;
		typedef iterator_traits<Iter>::pointer				pointer;
		typedef iterator_traits<Iter>::reference			reference;
		typedef iterator_traits<Iter>::iterator_category	iterator_category;

		IteratorWrapper() : current() {}
		virtual ~IteratorWrapper() {}
		explicit IteratorWrapper(Iter iter) : current(iter) {}
		IteratorWrapper(IteratorWrapper const& origin) : current(origin.base()) {}

		IteratorWrapper& operator=(IteratorWrapper<Iter> const& another)
		{
			if (this == &another)
				return *this;
			current = another.base();
			return *this;
		}

		Iter	base()
		{
			return current;
		}

		reference	operator*() const
		{
			Iter tmp = current;
			return *++tmp;
		}

		pointer	operator->() const
		{
			return &(operator*());
		}

		IteratorWrapper&	operator++()
		{
			++current;
			return *this;
		}

		IteratorWrapper	operator++(int)
		{
			IteratorWrapper tmp(*this);
			++current;
			return tmp;
		}

		IteratorWrapper&	operator--()
		{
			--current;
			return *this;
		}

		IteratorWrapper	operator--(int)
		{
			IteratorWrapper tmp(*this);
			--current;
			return tmp;
		}

		IteratorWrapper	operator+(difference_type n) const
		{
			return IteratorWrapper(current + n);
		}

		IteratorWrapper&	operator+=(difference_type n)
		{
			current += n;
			return *this;
		}

		IteratorWrapper	operator-(difference_type n) const
		{
			return IteratorWrapper(current - n);
		}

		IteratorWrapper&	operator-=(difference_type n)
		{
			current -= n;
			return *this;
		}

		reference	operator[](difference_type n) const
		{
			return *(*this + n);
		}
	};

	template<typename Iter>
	bool	operator==(IteratorWrapper<Iter> const& lhs, IteratorWrapper<Iter> const& rhs)
	{
		return lhs.base() == rhs.base();
	}

	template<typename Iter>
	bool	operator!=(IteratorWrapper<Iter> const& lhs, IteratorWrapper<Iter> const& rhs)
	{
		return lhs.base() != rhs.base();
	}

	template<typename Iter>
	bool	operator<(IteratorWrapper<Iter> const& lhs, IteratorWrapper<Iter> const& rhs)
	{
		return lhs.base() < rhs.base();
	}

	template<typename Iter>
	bool	operator<=(IteratorWrapper<Iter> const& lhs, IteratorWrapper<Iter> const& rhs)
	{
		return lhs.base() <= rhs.base();
	}

	template<typename Iter>
	bool	operator>(IteratorWrapper<Iter> const& lhs, IteratorWrapper<Iter> const& rhs)
	{
		return lhs.base() > rhs.base();
	}

	template<typename Iter>
	bool	operator>=(IteratorWrapper<Iter> const& lhs, IteratorWrapper<Iter> const& rhs)
	{
		return lhs.base() >= rhs.base();
	}
}

#endif
