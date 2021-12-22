/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modifier.ipp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 21:05:15 by smun              #+#    #+#             */
/*   Updated: 2021/12/22 21:53:16 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

template <typename T, typename Allocator>
void	ft::vector<T, Allocator>::ExpandStorageForPushBack()
{
	difference_type cap = capacity();
	difference_type count = cap << 1;
	if (count  < cap)
		count = std::numeric_limits<difference_type>::max();
	pointer nptr = allocator.allocate(count);
	MoveElements(begin(), end(), iterator(nptr));
	allocator.deallocate(begin_ptr, cap);
	begin_ptr = nptr;
	end_ptr = begin_ptr + cap;
	end_cap = end_ptr;
}

template <typename T, typename Allocator>
void	ft::vector<T, Allocator>::MoveElements(iterator first, iterator last, iterator out)
{
	while (first != last)
	{
		*out = *first;
		++first;
		++out;
	}
}
