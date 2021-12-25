/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 10:56:57 by smun              #+#    #+#             */
/*   Updated: 2021/12/25 21:00:31 by smun             ###   ########.fr       */
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
				typename ft::enable_if<ft::is_input_iterator<InputIt>::value, InputIt>::type first,
				typename ft::enable_if<ft::is_input_iterator<InputIt>::value, InputIt>::type last,
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
			// TODO
		}

		template <typename InputIt>
		typename ft::enable_if<ft::is_input_iterator<InputIt>::value, void>::type
		assign(InputIt first, InputIt last)
		{
			// TODO
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
			// TODO
			// return inserted iterator
		}

		void		insert(iterator pos, size_type count, const_reference value)
		{
			// TODO
		}

		template <typename InputIt>
		typename enable_if<is_input_iterator<InputIt>::value, void>::type
		insert(iterator pos, InputIt first, InputIt last)
		{

		}

		iterator	erase(iterator pos)
		{
			return erase(pos, ft::next(pos));
		}

		iterator	erase(iterator first, iterator last)
		{
			if (size() == 0)
				return end();
			pointer delfirst = first.base();
			pointer dellast = last.base();
			while (delfirst != dellast)
				_allocator.destroy(delfirst++);
			while (_end_ptr != dellast)
				_allocator.construct(*(--delfirst), *(--_end_ptr));
			return iterator(dellast);
		}

		void		push_back(const_reference value)
		{
			EnsureStorage(RecommendedSize(size() + 1));
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
			while (first != last)
				_allocator.construct(target++, *(first++));
			_allocator.deallocate(_begin_ptr, oldcap);
			_begin_ptr = nptr;
			_end_ptr = target;
			_end_cap = nptr + (_cap = n);
		}

		void	ConstructAtEnd(size_type count, T const& value)
		{
			while (count-- > 0)
				_allocator.construct(_end_ptr++, value);
		}

		void	DeconstructFromEnd(size_type n)
		{
			while (n-- > 0)
				_allocator.destroy(_end_ptr--);
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
