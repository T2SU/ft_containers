/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 10:56:57 by smun              #+#    #+#             */
/*   Updated: 2021/12/24 22:55:01 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include "iterator.hpp"
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
		typedef ft::IteratorWrapper<pointer>				iterator;
		typedef ft::IteratorWrapper<const_pointer>			const_iterator;
		typedef ft::reverse_iterator<iterator>				reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

	protected:
		pointer			_begin_ptr;
		pointer			_end_ptr;
		pointer			_end_cap;
		size_type		_cap;
		allocator_type	_allocator;

	public:
		/* Default Constructor */
		vector()
		: _begin_ptr(nullptr)
		, _end_ptr(nullptr)
		, _end_cap(nullptr)
		, _cap(0)
		, _allocator(Allocator())
		{
		}

		/* Copy Constructor */
		vector(const vector& other)
		: _begin_ptr(nullptr)
		, _end_ptr(nullptr)
		, _end_cap(nullptr)
		, _cap(0)
		, _allocator(other.get_allocator())
		{
			assign(other.begin(), other.end());
		}

		/* Parameterized Constructor (Allocator) */
		explicit
		vector(const Allocator& alloc)
		: _begin_ptr(nullptr)
		, _end_ptr(nullptr)
		, _end_cap(nullptr)
		, _cap(0)
		, _allocator(alloc)
		{
		}

		/* Parameterized Constructor (Assignment and Allocator) */
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

		/* Parameterized Constructor (Source iterator and Allocator) */
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
			_allocator.deallocate(_begin_ptr, capacity());
			_begin_ptr = nullptr;
			_end_ptr = nullptr;
			_end_cap = nullptr;
			_cap = 0;
		}


		/* Operators */
		vector&		operator=(const vector& other)
		{
			if (this == &other)
				return *this;
			assign(other.begin(), other.end());
			return *this;
		}


		/* Replacement */
		void	assign(size_type count, const T& value)
		{
			clear();
			EnsureStorage(count);
			ft::fill(begin(), count, value);
		}

		template <typename InputIt>
		void	assign(InputIt first, InputIt last)
		{
			clear();
			const difference_type count = ft::distance(first, last);
			EnsureStorage(count);
			ft::move(first, last, begin());
			_end_ptr = _begin_ptr + count;
		}


		/* Get Allocator */
		allocator_type			get_allocator() const { return _allocator; }


		/* Accessors */
		reference				at(size_type pos)
		{
			if (pos >= size()) // undefined exception at (pos < 0)
				throw std::out_of_range("vector<T, Alloc>::at(size_t pos)"
										" 'pos' out of bound");
			return _begin_ptr[pos];
		}

		const_reference			at(size_type pos) const
		{
			if (pos >= size()) // undefined exception at (pos < 0)
				throw std::out_of_range("vector<T, Alloc>::at(size_t pos)"
										" 'pos' out of bound");
			return _begin_ptr[pos];
		}

		reference				operator[](size_type pos)
		{
			// not defined exceptions at any cases.
			// Accessing a nonexistent element through this operator is undefined behavior.
			return _begin_ptr[pos];
		}

		const_reference			operator[](size_type pos) const
		{
			// not defined exceptions at any cases.
			// Accessing a nonexistent element through this operator is undefined behavior.
			return _begin_ptr[pos];
		}

		reference				front()			{ return _begin_ptr[0];	}
		const_reference			front()	const	{ return _begin_ptr[0];	}
		reference				back()			{ return _end_ptr[-1];	}
		const_reference			back()	const	{ return _end_ptr[-1];	}
		T*						data()			{ return _begin_ptr;	}
		const T*				data()	const	{ return _begin_ptr;	}


		/* Iterators */
		iterator				begin()				{ return iterator(_begin_ptr);				}
		const_iterator			begin()		const	{ return const_iterator(_begin_ptr);		}
		iterator				end()				{ return iterator(_end_ptr);				}
		const_iterator			end()		const	{ return const_iterator(_end_ptr);			}
		reverse_iterator		rbegin()			{ return reverse_iterator(_end_ptr);		}
		const_reverse_iterator	rbegin()	const	{ return const_reverse_iterator(_end_ptr);	}
		reverse_iterator		rend()				{ return reverse_iterator(_begin_ptr);		}
		const_reverse_iterator	rend()		const	{ return const_reverse_iterator(_begin_ptr);}


		/* Capacity */
		bool					empty()		const			{ return begin() == end(); }
		size_type				size()		const			{ return static_cast<size_type>(_end_ptr - _begin_ptr); }
		size_type				max_size()	const			{ return _allocator.max_size(); }
		size_type				capacity()	const			{ return _cap; }
		void					reserve(size_type new_cap)	{ EnsureStorage(new_cap); }


		/* Modifiers */
		void		clear()
		{
			for (pointer p = _begin_ptr; p != _end_ptr; ++p)
				_allocator.destroy(p);
			_end_ptr = _begin_ptr;
		}

		iterator	insert(iterator pos, const_reference value)
		{
			const difference_type idx = ft::distance(begin(), pos);
			EnsureStorage(RecommendedSize(size() + 1));
			iterator mbegin = ft::next(begin(), idx);
			MoveElements(idx, idx + 1);
			++_end_ptr;
			*mbegin = value;
			return mbegin;
		}

		void		insert(iterator pos, size_type count, const_reference value)
		{
			const difference_type idx = ft::distance(begin(), pos);
			EnsureStorage(RecommendedSize(size() + count));
			iterator mbegin = ft::next(begin(), idx);
			MoveElements(idx, idx + count);
			ft::fill(mbegin, count, value);
			_end_ptr += count;
		}

		template <typename InputIt>
		void		insert(iterator pos, InputIt first, InputIt last)
		{
			const difference_type idx = ft::distance(begin(), pos);
			const typename iterator_traits<InputIt>::difference_type count = ft::distance(first, last);
			EnsureStorage(RecommendedSize(size() + count));
			MoveElements(idx, idx + count);
			ft::move(first, last, ft::next(begin(), idx));
			_end_ptr += count;
		}

		iterator	erase(iterator pos)
		{
			return erase(pos, ft::next(pos));
		}

		iterator	erase(iterator first, iterator last)
		{
			if (size() == 0)
				return end();
			const difference_type distance = ft::distance(first, last);
			DestoryElements(first, last);
			MoveElements(last, end(), first);
			_end_ptr -= distance;
			return last;
		}

		void		push_back(const_reference value)
		{
			insert(end(), value);
		}

		void		pop_back()
		{
			erase(end());
		}

		void		resize(size_type count, T value = T())
		{
			if (count > capacity())
				EnsureStorage(count);
			if (count < size())
				erase(ft::prev(end(), size() - count), end());
			else if (count > size())
			{
				ft::fill(end(), count - size(), value);
				_end_ptr = count + _begin_ptr;
			}
		}

		void		swap(vector& other)
		{
			ft::swap(_begin_ptr, other._begin_ptr);
			ft::swap(_end_ptr, other._end_ptr);
			ft::swap(_end_cap, other._end_cap);
			ft::swap(_cap, other._cap);
			ft::swap(_allocator, other._allocator);
		}

	private:
		size_type	RecommendedSize(size_type n) const
		{
			const size_type cap = capacity();
			const size_type ms = max_size();
			if (cap >= ms / 2)
				return ms;
			return ft::max(2 * cap, n);
		}

		void	Allocate(size_type n, bool allocateWhenOnlyNecessary = false)
		{
			if (allocateWhenOnlyNecessary)
				if (n <= capacity())
					return;
			pointer nptr = _allocator.allocate(n);
			_begin_ptr = _end_ptr = nptr;
			_end_cap = &_begin_ptr[n - 1];
			_cap = n;
		}

		void	EnsureStorage(size_type n)
		{
			const iterator first = begin();
			const iterator last = end();
			const size_type oldcap = capacity();
			if (n > max_size())
				throw std::length_error("size_t n 'n' exceeds max_size");
			Allocate(n, true);
			ft::move(first, last, begin());
			_end_ptr = _begin_ptr + oldcap;
			_allocator.deallocate(first.base(), oldcap);
		}

		void	MoveElements(iterator ibegin, iterator iend, iterator obegin)
		{
			if (ibegin < obegin)
				ft::move_backward(ibegin, iend, obegin);
			else
				ft::move(ibegin, iend, obegin);
		}

		void	MoveElements(size_type from, size_type to)
		{
			MoveElements(
				ft::next(begin(), from),
				end(),
				ft::next(begin(), to)
			);
		}

		void	DestoryElements(iterator first, iterator last)
		{
			while (first != last)
			{
				_allocator.destroy(first.operator->());
				++first;
			}
		}
	};

	template<typename T, typename Allocator>
	bool	operator==(vector<T, Allocator> const& lhs, vector<T, Allocator> const& rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template<typename T, typename Allocator>
	bool	operator!=(vector<T, Allocator> const& lhs, vector<T, Allocator> const& rhs)
	{
		return !(lhs == rhs);
	}

	template<typename T, typename Allocator>
	bool	operator<(vector<T, Allocator> const& lhs, vector<T, Allocator> const& rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template<typename T, typename Allocator>
	bool	operator<=(vector<T, Allocator> const& lhs, vector<T, Allocator> const& rhs)
	{
		return !(rhs < lhs);
	}

	template<typename T, typename Allocator>
	bool	operator>(vector<T, Allocator> const& lhs, vector<T, Allocator> const& rhs)
	{
		return (rhs < lhs);
	}

	template<typename T, typename Allocator>
	bool	operator>=(vector<T, Allocator> const& lhs, vector<T, Allocator> const& rhs)
	{
		return !(lhs < rhs);
	}
}

#endif
