/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 17:35:17 by smun              #+#    #+#             */
/*   Updated: 2022/01/06 10:54:51 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include <functional>
# include <memory>
# include "utility.hpp"
# include "type_traits.hpp"
# include "iterator.hpp"

namespace ft
{
	template
	<
		typename Key,
		typename T,
		typename Compare = std::less<Key>,
		typename Allocator = std::allocator<ft::pair<const Key, T> >
	>
	class map
	{
	private:
	public:
		typedef Key											key_type;
		typedef T											mapped_type;
		typedef Allocator									allocator_type;
		typedef typename allocator_type::value_type			value_type;
		typedef typename allocator_type::size_type			size_type;
		typedef typename allocator_type::difference_type	difference_type;
		typedef Compare										key_compare;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef ft::IteratorWrapper<pointer>				iterator;
		typedef ft::IteratorWrapper<const_pointer>			const_iterator;
		typedef ft::reverse_iterator<iterator>				reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

		class value_compare
			: public std::binary_function<value_type, value_type, bool>
		{
		protected:
			key_compare comp;

			value_compare(key_compare c);
		public:
			bool operator()(const value_type& x, const value_type& y) const;
		};


		/* Constructor */

		map();
		explicit map(Compare const& cmp, Allocator const& alloc = Allocator());
		map(map const& origin);

		template<typename InputIt>
		map(
			ft::enable_if<ft::is_input_iterator<InputIt>::value, InputIt>::type first,
			ft::enable_if<ft::is_input_iterator<InputIt>::value, InputIt>::type last,
			Compare const& comp = Compare(),
			Allocator const& alloc = Allocator()
		);


		/* Destructor */

		virtual ~map();


		/* Operators */
		map*	operator=(map const& other);


		/* Allocator getter */
		allocator_type	get_allocator() const;


		/* Accessors */
		T&	at(Key const& key);
		T	const& at(Key const& key) const;
		T&	operator[](Key const& key);


		/* Iterators */
		iterator					begin();
		const_iterator				begin() const;
		iterator					end();
		const_iterator				end() const;
		reverse_iterator			rbegin();
		const_reverse_iterator		rbegin() const;
		reverse_iterator			rend();
		const_reverse_iterator		rend() const;


		/* Capacity */
		bool		empty() const;
		size_type	size() const;
		size_type	max_size() const;


		/* Modifiers */
		void		clear()
		{

		}

		ft::pair<iterator, bool>	insert(value_type const& value)
		{

		}

		iterator	insert(iterator hint, value_type const& value)
		{

		}

		template<typename InputIt>
		typename ft::enable_if<ft::is_input_iterator<InputIt>::value, void>::type
		insert(InputIt first, InputIt last)
		{

		}

		void		erase(iterator pos)
		{

		}

		void		erase(iterator first, iterator last)
		{

		}

		size_type	erase(Key const& key)
		{

		}

		void		swap(map& other)
		{

		}


		/* Lookup */

		size_type		count(Key const& key) const
		{

		}

		iterator		find(Key const& key)
		{

		}

		const_iterator	find(Key const& key) const
		{

		}

		ft::pair<iterator, iterator>
		equal_range(Key const& key)
		{

		}

		ft::pair<const_iterator, const_iterator>
		equal_range(Key const& key) const
		{

		}

		iterator	lower_bound(Key const& key)
		{

		}

		const_iterator	lower_Bound(Key const& key) const
		{

		}

		iterator	upper_bound(Key const& key)
		{

		}

		const_iterator	upper_bound(Key const& key) const
		{

		}


		/* Observers */

		key_compare	key_comp() const
		{

		}

		value_compare	value_comp() const
		{

		}
	};

	/* Non member operators */

	template<typename Key, typename T, typename Compare, typename Alloc>
	bool	operator==(map<Key,T,Compare,Alloc> const& lhs, map<Key,T,Compare,Alloc> const& rhs)
	{
	}

	template<typename Key, typename T, typename Compare, typename Alloc>
	bool	operator!=(map<Key,T,Compare,Alloc> const& lhs, map<Key,T,Compare,Alloc> const& rhs)
	{
	}

	template<typename Key, typename T, typename Compare, typename Alloc>
	bool	operator<(map<Key,T,Compare,Alloc> const& lhs, map<Key,T,Compare,Alloc> const& rhs)
	{
	}

	template<typename Key, typename T, typename Compare, typename Alloc>
	bool	operator<=(map<Key,T,Compare,Alloc> const& lhs, map<Key,T,Compare,Alloc> const& rhs)
	{
	}

	template<typename Key, typename T, typename Compare, typename Alloc>
	bool	operator>(map<Key,T,Compare,Alloc> const& lhs, map<Key,T,Compare,Alloc> const& rhs)
	{
	}

	template<typename Key, typename T, typename Compare, typename Alloc>
	bool	operator>=(map<Key,T,Compare,Alloc> const& lhs, map<Key,T,Compare,Alloc> const& rhs)
	{
	}
}

#endif
