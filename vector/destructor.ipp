/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructor.ipp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 20:27:45 by smun              #+#    #+#             */
/*   Updated: 2021/12/22 20:32:33 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

template <typename T, typename Allocator>
ft::vector<T, Allocator>::~vector()
{
	allocator.deallocate(begin_ptr, capacity());
	begin_ptr = nullptr;
	end_ptr = nullptr;
	end_cap = nullptr;
}
