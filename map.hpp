/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 17:35:17 by smun              #+#    #+#             */
/*   Updated: 2022/01/29 15:54:37 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include <functional>
# include <memory>
# include "tree.hpp"

namespace ft
{
	template<
		typename Key,
		typename T,
		typename Compare = std::less<Key>,
		typename Allocator = std::allocator<ft::pair<const Key, T> >
	>
	class map
	{
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

		class value_compare
			: public std::binary_function<value_type, value_type, bool>
		{
		friend class map;
		private:
			value_compare();
			value_compare(value_compare const&);
			value_compare& operator=(value_compare const&);

		protected:
			key_compare comp;

			value_compare(key_compare c) : comp(c) {}
		public:
			virtual ~value_compare() {}

			bool operator()(const value_type& x, const value_type& y) const
			{
				return comp(x.first, y.first);
			}
		};

	private:
		typedef tree<key_type, mapped_type, value_type, key_compare, allocator_type>	tree_type;

		key_compare	_key_compare;
		tree_type	_tree;

	public:
		typedef typename tree_type::iterator				iterator;
		typedef typename tree_type::const_iterator			const_iterator;
		typedef typename tree_type::reverse_iterator		reverse_iterator;
		typedef typename tree_type::const_reverse_iterator	const_reverse_iterator;

		map()
			: _key_compare(Compare())
			, _tree(key_comp(), Allocator())
		{}

		explicit
		map(Compare const& comp, Allocator const& alloc = Allocator())
			: _key_compare(comp)
			, _tree(key_comp(), alloc)
		{}

		template<typename InputIt>
		map(
			InputIt first,
			InputIt last,
			Compare const& comp = Compare(),
			Allocator const& alloc = Allocator()
		)
			: _key_compare(comp)
			, _tree(key_comp(), alloc)
		{
			insert(first, last);
		}

		virtual ~map()
		{
		}

		map&	operator=(map const& other)
		{
			clear();
			insert(other.begin(), other.end());
		}

		allocator_type	get_allocator() const	{ return _tree.get_allocator(); }
		key_compare		key_comp() const		{ return _key_compare; }
		value_compare	value_comp() const		{ return value_compare(key_comp()); }

		iterator					begin()			{ return _tree.begin(); }
		const_iterator				begin() const	{ return _tree.begin(); }
		iterator					end()			{ return _tree.end(); }
		const_iterator				end() const		{ return _tree.end(); }
		reverse_iterator			rbegin()		{ return _tree.rbegin(); }
		const_reverse_iterator		rbegin() const	{ return _tree.rbegin(); }
		reverse_iterator			rend()			{ return _tree.rend(); }
		const_reverse_iterator		rend() const	{ return _tree.rend(); }

		bool		empty() const		{ return _tree.empty(); }
		size_type	size() const		{ return _tree.size(); }
		size_type	max_size() const	{ return _tree.max_size(); }

		void		clear()						{ _tree.clear(); }
		T&			operator[](Key const& key)	{ return _tree[key]; }

		ft::pair<iterator, bool>	insert(const_reference value)
		{
			return _tree.insert(value);
		}

		iterator	insert(iterator hint, const_reference value)
		{
			return _tree.insert(hint, value);
		}

		template<typename InputIt>
		typename ft::enable_if<ft::is_input_iterator<InputIt>::value, void>::type
		insert(InputIt first, InputIt last)
		{
			_tree.insert(first, last);
		}

		void	erase(iterator pos)
		{
			_tree.erase(pos);
		}

		void	erase(iterator first, iterator last)
		{
			_tree.erase(first, last);
		}

		size_type	erase(Key const& key)
		{
			return _tree.erase(key);
		}

		void	swap(map& other)
		{
			_tree.swap(other._tree);
			ft::swap(_key_compare, other._key_compare);
		}

		T&	at(Key const& key)
		{
			iterator	it = _tree.find(key);

			if (it == end())
				throw std::out_of_range("Key not found");
			return it->second;
		}

		T	const& at(Key const& key) const
		{
			iterator	it = _tree.find(key);

			if (it == end())
				throw std::out_of_range("Key not found");
			return it->second;
		}

		size_type	count(Key const& key) const
		{
			return _tree.count(key);
		}

		iterator	find(Key const& key)
		{
			return _tree.find(key);
		}

		const_iterator	find(Key const& key) const
		{
			return _tree.find(key);
		}

		ft::pair<iterator, iterator>
		equal_range(Key const& key)
		{
			iterator	it = find(key);

			return ft::make_pair(it, it);
		}

		ft::pair<const_iterator, const_iterator>
		equal_range(Key const& key) const
		{
			iterator	it = find(key);

			return ft::make_pair(it, it);
		}

		iterator	lower_bound(Key const& key)
		{
			return _tree.lower_bound(key);
		}

		const_iterator	lower_bound(Key const& key) const
		{
			return _tree.lower_bound(key);
		}

		iterator	upper_bound(Key const& key)
		{
			return _tree.upper_bound(key);
		}

		const_iterator	upper_bound(Key const& key) const
		{
			return _tree.upper_bound(key);
		}

	};
}

#endif
