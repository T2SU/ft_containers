/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulator.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 19:00:42 by smun              #+#    #+#             */
/*   Updated: 2021/12/23 11:26:32 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MANIPULATOR_HPP
# define MANIPULATOR_HPP

# include "base.hpp"

namespace ft
{
	template<typename Iter>
	class IteratorManipulator
	{
	private:
		Iter iter;

		IteratorManipulator();
		IteratorManipulator(IteratorManipulator const&);
		IteratorManipulator& operator=(IteratorManipulator const&);

		typedef typename iterator_traits<Iter>::iterator_category	iterator_category;
		typedef typename iterator_traits<Iter>::difference_type		difference_type;

		difference_type	distance(input_iterator_tag) const
		{
			difference_type r(0);
			Iter i = iter;
			while (i != another)
			{
				++r;
				++i;
			}
			return r;
		}

		difference_type	distance(random_access_iterator_tag) const
		{
			return another - iter;
		}

		Iter	advance(difference_type n, input_iterator_tag)
		{
			for (; n > 0; --n)
				++iter;
			return iter;
		}

		Iter	advance(difference_type n, bidirectional_iterator_tag)
		{
			if (n > 0)
				for (; n > 0; --n)
					++iter;
			else
				for (; n < 0; ++n)
					--iter;
			return iter;
		}

		Iter	advance(difference_type n, random_access_iterator_tag)
		{
			iter += n;
			return iter;
		}

	public:
		virtual ~IteratorManipulator() {}
		IteratorManipulator(Iter& iter)
			: iter(iter) {}

		difference_type	distance(Iter& another) const
		{
			return distance(another, iterator_category());
		}

		Iter	advance(difference_type n)
		{
			return advance(n, iterator_category());
		}
	};
}

#endif
