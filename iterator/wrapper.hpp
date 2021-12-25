/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 22:48:46 by smun              #+#    #+#             */
/*   Updated: 2021/12/25 19:58:31 by smun             ###   ########.fr       */
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
		typedef Iter												iterator_type;
		typedef typename iterator_traits<Iter>::value_type			value_type;
		typedef typename iterator_traits<Iter>::difference_type		difference_type;
		typedef typename iterator_traits<Iter>::pointer				pointer;
		typedef typename iterator_traits<Iter>::reference			reference;
		typedef typename iterator_traits<Iter>::iterator_category	iterator_category;

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

		Iter	base() const
		{
			return current;
		}

		reference	operator*() const
		{
			return *current;
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

		IteratorWrapper	operator-(difference_type n) const
		{
			return IteratorWrapper(current - n);
		}

		IteratorWrapper&	operator+=(difference_type n)
		{
			current += n;
			return *this;
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

	template<typename Iter>
	typename IteratorWrapper<Iter>::difference_type
	operator-(IteratorWrapper<Iter> const& x, IteratorWrapper<Iter> const& y)
	{
		return x.base() - y.base();
	}

	template<typename Iter>
	IteratorWrapper<Iter>
	operator+(typename IteratorWrapper<Iter>::difference_type n, IteratorWrapper<Iter> const& x)
	{
		return IteratorWrapper<Iter>(x.base() + n);
	}
}

#endif
