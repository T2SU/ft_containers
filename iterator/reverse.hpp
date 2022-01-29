/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 18:59:30 by smun              #+#    #+#             */
/*   Updated: 2022/01/29 19:19:10 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_REVERSE_HPP
# define ITERATOR_REVERSE_HPP

# include "base.hpp"

namespace ft
{
	template<typename Iter>
	class reverse_iterator :
		public iterator<typename iterator_traits<Iter>::iterator_category,
						typename iterator_traits<Iter>::value_type,
						typename iterator_traits<Iter>::difference_type,
						typename iterator_traits<Iter>::pointer,
						typename iterator_traits<Iter>::reference>
	{
	protected:
		Iter current;

	public:

		typedef Iter											iterator_type;
		typedef typename iterator_traits<Iter>::difference_type	difference_type;
		typedef typename iterator_traits<Iter>::reference		reference;
		typedef typename iterator_traits<Iter>::pointer			pointer;

		virtual ~reverse_iterator() {}
		reverse_iterator() : current() {}
		reverse_iterator(Iter iter) : current(iter) {}
		reverse_iterator(reverse_iterator<Iter> const& origin) : current(origin.base()) {}

		template<typename Tp>
		reverse_iterator(reverse_iterator<Tp> const& another,
			typename ft::enable_if<ft::is_convertible_to<Tp, Iter>::value, Iter>::type* = 0)
			: current(another.base()) {}

		reverse_iterator& operator=(reverse_iterator<Iter> const& another)
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
			Iter tmp = current;
			return *--tmp;
		}

		pointer	operator->() const
		{
			return &(operator*());
		}

		reverse_iterator&	operator++()
		{
			--current;
			return *this;
		}

		reverse_iterator	operator++(int)
		{
			reverse_iterator tmp(*this);
			--current;
			return tmp;
		}

		reverse_iterator&	operator--()
		{
			++current;
			return *this;
		}

		reverse_iterator	operator--(int)
		{
			reverse_iterator tmp(*this);
			++current;
			return tmp;
		}

		reverse_iterator	operator+(difference_type n) const
		{
			return reverse_iterator(current - n);
		}

		reverse_iterator&	operator+=(difference_type n)
		{
			current -= n;
			return *this;
		}

		reverse_iterator	operator-(difference_type n) const
		{
			return reverse_iterator(current + n);
		}

		reverse_iterator&	operator-=(difference_type n)
		{
			current += n;
			return *this;
		}

		reference	operator[](difference_type n) const
		{
			return *(*this + n);
		}
	};

	template<typename Iter1, typename Iter2>
	bool	operator==(reverse_iterator<Iter1> const& lhs, reverse_iterator<Iter2> const& rhs)
	{
		return lhs.base() == rhs.base();
	}

	template<typename Iter1, typename Iter2>
	bool	operator!=(reverse_iterator<Iter1> const& lhs, reverse_iterator<Iter2> const& rhs)
	{
		return lhs.base() != rhs.base();
	}

	template<typename Iter1, typename Iter2>
	bool	operator<(reverse_iterator<Iter1> const& lhs, reverse_iterator<Iter2> const& rhs)
	{
		return lhs.base() > rhs.base();
	}

	template<typename Iter1, typename Iter2>
	bool	operator<=(reverse_iterator<Iter1> const& lhs, reverse_iterator<Iter2> const& rhs)
	{
		return lhs.base() >= rhs.base();
	}

	template<typename Iter1, typename Iter2>
	bool	operator>(reverse_iterator<Iter1> const& lhs, reverse_iterator<Iter2> const& rhs)
	{
		return lhs.base() < rhs.base();
	}

	template<typename Iter1, typename Iter2>
	bool	operator>=(reverse_iterator<Iter1> const& lhs, reverse_iterator<Iter2> const& rhs)
	{
		return lhs.base() <= rhs.base();
	}

	template<typename Iter1, typename Iter2>
	typename reverse_iterator<Iter1>::difference_type
	operator-(reverse_iterator<Iter1> const& x, reverse_iterator<Iter2> const& y)
	{
		return y.base() - x.base();
	}

	template<typename Iter>
	reverse_iterator<Iter>
	operator+(typename reverse_iterator<Iter>::difference_type n, reverse_iterator<Iter> const& x)
	{
		return reverse_iterator<Iter>(x.base() - n);
	}
}

#endif
