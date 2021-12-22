/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.ipp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 18:13:24 by smun              #+#    #+#             */
/*   Updated: 2021/12/22 20:45:13 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

template<typename T, typename Alloc>
typename ft::vector<T, Alloc>::iterator
ft::vector<T, Alloc>::begin()
{
	return iterator(begin_ptr);
}

template<typename T, typename Alloc>
typename ft::vector<T, Alloc>::const_iterator
ft::vector<T, Alloc>::begin() const
{
	return const_iterator(begin_ptr);
}

template<typename T, typename Alloc>
typename ft::vector<T, Alloc>::iterator
ft::vector<T, Alloc>::end()
{
	return iterator(end_ptr);
}

template<typename T, typename Alloc>
typename ft::vector<T, Alloc>::const_iterator
ft::vector<T, Alloc>::end() const
{
	return const_iterator(end_ptr);
}

template<typename T, typename Alloc>
typename ft::vector<T, Alloc>::reverse_iterator
ft::vector<T, Alloc>::rbegin()
{
	return reverse_iterator(end_ptr);
}

template<typename T, typename Alloc>
typename ft::vector<T, Alloc>::const_reverse_iterator
ft::vector<T, Alloc>::rbegin() const
{
	return const_reverse_iterator(end_ptr);
}

template<typename T, typename Alloc>
typename ft::vector<T, Alloc>::reverse_iterator
ft::vector<T, Alloc>::rend()
{
	return reverse_iterator(begin_ptr);
}

template<typename T, typename Alloc>
typename ft::vector<T, Alloc>::const_reverse_iterator
ft::vector<T, Alloc>::rend() const
{
	return const_reverse_iterator(begin_ptr);
}
