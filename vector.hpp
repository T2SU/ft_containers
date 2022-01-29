/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 10:56:57 by smun              #+#    #+#             */
/*   Updated: 2022/01/29 19:14:21 by smun             ###   ########.fr       */
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
		vector(
				InputIt first,
				InputIt last,
				const Allocator& alloc = Allocator()
			)
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
			EnsureStorage(size() + count);
			ConstructAtEnd(count, value);
		}

		template <typename InputIt>
		typename ft::enable_if<ft::is_input_iterator<InputIt>::value, void>::type
		assign(InputIt first, InputIt last)
		{
			clear();
			EnsureStorage(size() + ft::distance(first, last));
			while (first != last)
				_allocator.construct((_end_ptr)++, *(first++));
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
			iterator dest = PrepareInsertion(pos, 1);

			_allocator.construct(dest.base(), value);
			++_end_ptr;
			return dest;
		}

		void		insert(iterator pos, size_type count, const_reference value)
		{
			iterator	dest = PrepareInsertion(pos, count);
			pointer		target = dest.base();

			while (count-- > 0)
			{
				_allocator.construct(target++, value);
				++_end_ptr;
			}
		}

		template <typename InputIt>
		typename enable_if<is_input_iterator<InputIt>::value, void>::type
		insert(iterator pos, InputIt first, InputIt last)
		{
			iterator	dest = PrepareInsertion(pos, first, last);
			pointer		target = dest.base();

			while (first != last)
			{
				_allocator.construct(target++, *(first++));
				++_end_ptr;
			}
		}

		iterator	erase(iterator pos)
		{
			return erase(pos, ft::next(pos));
		}

		// 1. 삭제된 요소의 iterator
		// 2. 삭제된 요소(pos)가 마지막 요소일 경우, end()
		// 3. [first, last] 범위가 비어있을 경우, last
		// 4. 삭제 직전에 last == end() 였을 경우, 갱신된 end()

		iterator	erase(iterator first, iterator last)
		{
			pointer delcursor = first.base();
			pointer dellast = last.base();

			// Destroying erasing range
			while (delcursor != dellast)
				_allocator.destroy(delcursor++);

			// Calculating elements number for moving(len) and first~last range size(range)
			const difference_type len = _end_ptr - delcursor;
			const difference_type range = ft::distance(first, last);

			// Move elements to deleted starting position.
			MoveAsForward(delcursor, first.base(), len);

			// Adjusting end pointer by deleted length.
			_end_ptr -= range;

			return first;
		}

		void		push_back(const_reference value)
		{
			const size_type	sz = size();

			if (sz + 1 > capacity())
				EnsureStorage(RecommendedSize(sz + 1));
			ConstructAtEnd(1, value);
		}

		void		pop_back()
		{
			DeconstructFromEnd(1);
		}

		void		resize(size_type count, T value = T())
		{
			if (count > size())
			{
				EnsureStorage(count);
				ConstructAtEnd(count - size(), value);
			}
			else if (count < size())
				DeconstructFromEnd(size() - count);
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

		void	EnsureStorage(size_type n)
		{
			if (n > max_size())
				throw std::length_error("size_t n 'n' exceeds max_size");
			if (n <= capacity())
				return;
			size_type oldcap = capacity();
			pointer nptr = _allocator.allocate(n);
			pointer first = _begin_ptr;
			pointer last = _end_ptr;
			pointer target = nptr;

			// Move elements to new memory
			while (first != last)
				_allocator.construct(target++, *(first++));

			// Deallocate previous memory
			_allocator.deallocate(_begin_ptr, oldcap);

			// Relocate to new memory (and set new capacity)
			_begin_ptr = nptr;
			_end_ptr = target;
			_end_cap = nptr + (_cap = n);
		}

		template <typename InputIt>
		typename enable_if<is_input_iterator<InputIt>::value, iterator>::type
		PrepareInsertion(iterator pos, InputIt first, InputIt last)
		{
			return PrepareInsertion(pos, ft::distance(first, last));
		}

		iterator	PrepareInsertion(iterator pos, difference_type space)
		{
			const size_type			sz = size();
			const difference_type	n = ft::distance(begin(), pos);

			if (sz + space > capacity())
				EnsureStorage(RecommendedSize(sz + space));
			pos = ft::next(begin(), n);
			iterator to = ft::next(pos, space);
			MoveAsBackward(pos.base(), to.base(), sz - n);
			return pos;
		}

		void	MoveAsForward(pointer from, pointer to, difference_type len)
		{
			if (from == to)
				return;
			while (len-- > 0)
				_allocator.construct(to++, *(from++));
		}

		void	MoveAsBackward(pointer from, pointer to, difference_type len)
		{
			if (from == to)
				return;
			from += len;
			to += len;
			while (len-- > 0)
				_allocator.construct(--to, *(--from));
		}

		void	ConstructAtEnd(size_type count, T const& value)
		{
			while (count-- > 0)
				_allocator.construct((_end_ptr)++, value);
		}

		void	DeconstructFromEnd(size_type n)
		{
			while (n-- > 0)
				_allocator.destroy(--(_end_ptr));
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

	template<typename T>
	void	swap(ft::vector<T>& o1, ft::vector<T>& o2)
	{
		o1.swap(o2);
	}
}

#endif
