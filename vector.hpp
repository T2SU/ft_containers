/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 10:56:57 by smun              #+#    #+#             */
/*   Updated: 2021/12/22 21:52:12 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <limits>
# include "utility/iterator.hpp"

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
		pointer			begin_ptr;
		pointer			end_ptr;
		pointer			end_cap;
		allocator_type	allocator;

	public:
		/* Constructors */
		vector();
		vector(const vector& other);

		explicit vector(const Allocator& alloc);
		explicit vector(size_type count, const T& value = T(), const Allocator& alloc = Allocator());

		template <typename InputIt>
		vector(InputIt first, InputIt last, const Allocator& alloc = Allocator());


		/* Destructor */
		virtual ~vector();


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
		allocator_type			get_allocator() const { return allocator; }


		/* Accessors */
		reference				at(size_type pos);
		const_reference			at(size_type pos) const;
		reference				operator[](size_type pos);
		const_reference			operator[](size_type pos) const;
		reference				front();
		const_reference			front() const;
		reference				back();
		const_reference			back() const;
		T*						data();
		const T*				data() const;


		/* Iterators */
		iterator				begin();
		const_iterator			begin() const;
		iterator				end();
		const_iterator			end() const;
		reverse_iterator		rbegin();
		const_reverse_iterator	rbegin() const;
		reverse_iterator		rend();
		const_reverse_iterator	rend() const;


		/* Capacity */
		bool					empty() const;
		size_type				size() const;
		size_type				max_size() const;
		void					reserve(size_type new_cap);
		size_type				capacity() const;


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
		void					ExpandStorageForPushBack();
		void					MoveElements(iterator first, iterator last, iterator out);
	};
}

# include "vector/contructor.ipp"
# include "vector/destructor.ipp"
# include "vector/operator.ipp"
# include "vector/replacer.ipp"
# include "vector/accessor.ipp"
# include "vector/iterator.ipp"
# include "vector/capacity.ipp"
# include "vector/modifier.ipp"

#endif
