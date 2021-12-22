/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 18:59:30 by smun              #+#    #+#             */
/*   Updated: 2021/12/22 21:57:39 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

# include "iterator_base.hpp"

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
		explicit reverse_iterator(Iter iter) : current(iter) {}
		reverse_iterator(reverse_iterator<Iter> const& origin) : current(origin.base()) {}

		reverse_iterator& operator=(reverse_iterator<Iter> const& another)
		{
			if (this == &another)
				return *this;
			curret = another.base();
			return *this;
		}

		Iter	base()
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
}

#endif
