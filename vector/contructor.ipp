/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contructor.ipp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 13:21:50 by smun              #+#    #+#             */
/*   Updated: 2021/12/22 21:07:54 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

template <typename T, typename Allocator>
ft::vector<T, Allocator>::vector()
	: begin_ptr(nullptr)
	, end_ptr(nullptr)
	, end_cap(nullptr)
	, allocator(Allocator())
{
}

template <typename T, typename Allocator>
ft::vector<T, Allocator>::vector(const ft::vector<T, Allocator>& other)
	: allocator(other.get_allocator())
{
	difference_type count = other.size();
	begin_ptr = alloc.allocate(count);
	end_ptr = begin_ptr + count;
	end_cap = end_ptr;
	assign(other.begin(), other.end());
}

template <typename T, typename Allocator>
ft::vector<T, Allocator>::vector(const Allocator& alloc)
	: begin_ptr(nullptr)
	, end_ptr(nullptr)
	, end_cap(nullptr)
	, allocator(alloc)
{
}

template <typename T, typename Allocator>
ft::vector<T, Allocator>::vector(size_type count, const T& value = T(), const Allocator& alloc)
	: allocator(alloc)
{
	begin_ptr = alloc.allocate(count);
	end_ptr = begin_ptr + count;
	end_cap = end_ptr;
	assign(count, value);
}

template <typename T, typename Allocator>
template <typename InputIt>
ft::vector<T, Allocator>::vector(InputIt first, InputIt last, const Allocator& alloc)
	: begin_ptr(nullptr)
	, end_ptr(nullptr)
	, end_cap(nullptr)
	, allocator(alloc)
{
	difference_type count = distance(first, last);
	begin_ptr = alloc.allocate(count);
	end_ptr = begin_ptr + count;
	end_cap = end_ptr;
	assign(first, last);
}
