/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 10:56:57 by smun              #+#    #+#             */
/*   Updated: 2021/12/22 23:10:06 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include "algorithm.hpp"

namespace ft
{
	template <typename T, typename Allocator = std::allocator<T> >
	class vector
	{
	public:
		/* Type definitions */
		typedef T											value_type;
		typedef Allocator									allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::size_type			size_type;
		typedef typename allocator_type::difference_type	difference_type;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef typename iterator_wrapper<pointer>			iterator;
		typedef typename iterator_wrapper<const_pointer>	const_iterator;
		typedef typename reverse_iterator<iterator>			reverse_iterator;
		typedef typename reverse_iterator<const_iterator>	const_reverse_iterator;

	protected:
		pointer			_begin_ptr;
		pointer			_end_ptr;
		pointer			_end_cap;
		size_type		_cap;
		allocator_type	_allocator;

	public:
		/* Constructors */
		vector()
		: _begin_ptr(nullptr)
		, _end_ptr(nullptr)
		, _end_cap(nullptr)
		, _cap(0)
		, _allocator(Allocator())
		{
		}

		vector(const vector& other)
		: _allocator(other.get_allocator())
		{
			ConstructBy(other.begin(), other.end());
		}

		explicit
		vector(const Allocator& alloc)
		: _begin_ptr(nullptr)
		, _end_ptr(nullptr)
		, _end_cap(nullptr)
		, _cap(0)
		, _allocator(alloc)
		{
		}

		explicit
		vector(size_type count, const T& value = T(), const Allocator& alloc = Allocator())
		: _begin_ptr(nullptr)
		, _end_ptr(nullptr)
		, _end_cap(nullptr)
		, _cap(0)
		, _allocator(alloc)
		{
			assign(count, value);
		}

		template <typename InputIt>
		vector(InputIt first, InputIt last, const Allocator& alloc = Allocator())
		: _begin_ptr(nullptr)
		, _end_ptr(nullptr)
		, _end_cap(nullptr)
		, _cap(0)
		, _allocator(alloc)
		{
			assign(first, last);
		}

		/* Destructor */
		virtual ~vector()
		{
			allocator.deallocate(_begin_ptr, capacity());
			_begin_ptr = nullptr;
			_end_ptr = nullptr;
			_end_cap = nullptr;
			_cap = 0;
		}


		/* Operators */
		vector&					operator=(const vector& other);
		bool					operator==(const vector<T, Allocator>& rhs) const;
		bool					operator!=(const vector<T, Allocator>& rhs) const;
		bool					operator<(const vector<T, Allocator>& rhs) const;
		bool					operator<=(const vector<T, Allocator>& rhs) const;
		bool					operator>(const vector<T, Allocator>& rhs) const;
		bool					operator>=(const vector<T, Allocator>& rhs) const;


		/* Replacement */
		void					assign(size_type count, const T& value);

		template <typename InputIt>
		void					assign(InputIt first, InputIt last);


		/* Get Allocator */
		allocator_type			get_allocator() const { return _allocator; }


		/* Accessors */
		reference				at(size_type pos)
		{
			if (pos >= size())
				throw std::out_of_range("vector<T, Alloc>::at(size_t pos)"
										" 'pos' exceeds container's size");
			return _begin_ptr[n];
		}

		const_reference			at(size_type pos) const
		{
			if (pos >= size())
				throw std::out_of_range("vector<T, Alloc>::at(size_t pos)"
										" 'pos' exceeds container's size");
			return _begin_ptr[n];
		}

		reference				operator[](size_type pos)			{}
		const_reference			operator[](size_type pos)	const	{}
		reference				front()								{}
		const_reference			front()						const	{}
		reference				back()								{}
		const_reference			back()						const	{}
		T*						data()								{}
		const T*				data()						const	{}


		/* Iterators */
		iterator				begin()				{ return iterator(_begin_ptr);				}
		const_iterator			begin()		const	{ return const_iterator(_begin_ptr);			}
		iterator				end()				{ return iterator(_end_ptr);					}
		const_iterator			end()		const	{ return const_iterator(_end_ptr);			}
		reverse_iterator		rbegin()			{ return reverse_iterator(_end_ptr);			}
		const_reverse_iterator	rbegin()	const	{ return const_reverse_iterator(_end_ptr);	}
		reverse_iterator		rend()				{ return reverse_iterator(_begin_ptr);		}
		const_reverse_iterator	rend()		const	{ return const_reverse_iterator(_begin_ptr);	}


		/* Capacity */
		bool					empty()		const	{ return begin() == end(); }
		size_type				size()		const	{ return static_cast<size_type>(_end_ptr - _begin_ptr); }
		size_type				max_size()	const	{ return allocator.max_size(); }
		size_type				capacity()	const	{ return _cap; }
		void					reserve(size_type new_cap)
		{
			if (new_cap <= capacity())
				return;
			Allocate(new_cap);
		}


		/* Modifiers */
		void					clear();
		iterator				insert(iterator pos, const T& value);
		void					insert(iterator pos, size_type count, const T& value);

		template <typename InputIt>
		void					insert(iterator pos, InputIt first, InputIt last);

		iterator				erase(iterator pos);
		iterator				erase(iterator first, iterator last);

		void					push_back(const T& value);
		void					pop_back();
		void					resize(size_type count);
		void					resize(size_type count, T value = T());
		void					swap(vector& other);

	private:
		size_type				RecommendedSize(size_type desired) const
		{
			const size_type ms = max_size();
			if (desired > ms)
				throw std::length_error("vector<T, Alloc>::RecommendedSize(size_t d)"
										" 'd' exceeds maximum supported size");
			const size_type cap = capacity();
			if (cap >= ms / 2)
				return ms;
			return max(2 * cap, desired);
		}

		void					Allocate(size_type n)
		{
			pointer nptr = _allocator.allocate(n);
			_begin_ptr = nptr;
			_end_ptr = nptr; ++_end_ptr;
			_end_cap = _begin_ptr + n;
			_cap = n;
		}

		void					ExpandStorage(size_type n)
		{
			const iterator first = begin();
			const iterator last = end();
			const size_type oldcap = capacity();
			Allocate(n);
			move(first, last, begin());
			_end_ptr = begin() + oldcap;
			_allocator.deallocate(_begin_ptr, oldcap);
		}

		void					ConstructBy(iterator first, iterator last)
		{
			const difference_type count = distance(first, last);
			const size_type ms = max_size();
			if (count > ms)
				throw std::length_error("vector<T, Alloc>::vector(InputIt first, InputIt last, const Allocator& alloc)"
										" iterator distance exceeds maximum supported size");
			Allocate(count);
			move(first, last, begin());
			_end_ptr = begin() + count;
		}

		void					ConstructAs(iterator out, size_type n, const T& value)
		{
			const size_type ms = max_size();
			if (n > ms)
				throw std::length_error("vector<T, Alloc>::vector(size_type count, const T& value, const Allocator& alloc)"
										" 'count' exceeds maximum supported size");
			Allocate(n);
			fill(begin(), n, value);
		}

	};
}
#endif
