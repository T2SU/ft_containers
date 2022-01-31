/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 14:12:03 by smun              #+#    #+#             */
/*   Updated: 2022/01/31 15:11:14 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
# define SET_HPP

# include <memory>
# include <functional>
# include "rbtree.hpp"

namespace ft
{
	template<
		typename Key,
		typename Compare = std::less<Key>,
		typename Allocator = std::allocator<Key>
	>
	class set
	{
	public:
		typedef Key											key_type;
		typedef Key											value_type;
		typedef Allocator									allocator_type;
		typedef typename allocator_type::size_type			size_type;
		typedef typename allocator_type::difference_type	difference_type;
		typedef Compare										key_compare;
		typedef Compare										value_compare;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;

	private:
		template<typename KeyType>
		class set_value_creator
			: private std::unary_function<KeyType, KeyType>
		{
		private:
			set_value_creator(set_value_creator const&);
			set_value_creator& operator=(set_value_creator const&);
		public:
			set_value_creator() {}
			virtual ~set_value_creator() {}
			KeyType	operator()(KeyType const& key) const
			{
				return KeyType(key);
			}
			void	swap(set_value_creator const&, set_value_creator const&)
			{
			}
		};

		typedef	set_value_creator<key_type>	value_creator_type;
		typedef tree<key_type, value_type, Compare, value_creator_type, allocator_type>	tree_type;

		typedef typename tree_type::iterator	tree_iterator_type;

		key_compare	_key_compare;
		tree_type	_tree;

	public:
		typedef typename tree_type::const_iterator			iterator;
		typedef typename tree_type::const_iterator			const_iterator;
		typedef typename tree_type::const_reverse_iterator	reverse_iterator;
		typedef typename tree_type::const_reverse_iterator	const_reverse_iterator;

		set()
			: _key_compare(Compare())
			, _tree(key_comp(), Allocator())
		{}

		explicit
		set(Compare const& comp, Allocator const& alloc = Allocator())
			: _key_compare(comp)
			, _tree(key_comp(), alloc)
		{}

		template<typename InputIt>
		set(
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

		set(set const& other)
			: _key_compare(other._key_compare)
			, _tree(other._tree)
		{
		}

		virtual ~set()
		{
		}

		set&	operator=(set const& other)
		{
			if (this == &other)
				return *this;
			clear();
			insert(other.begin(), other.end());
			return *this;
		}

		allocator_type	get_allocator() const	{ return _tree.get_allocator(); }
		key_compare		key_comp() const		{ return _key_compare; }
		value_compare	value_comp() const		{ return _key_compare; }

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

		ft::pair<iterator, bool>	insert(const_reference value)
		{
			ft::pair<tree_iterator_type, bool> p = _tree.insert(value);

			return ft::pair<iterator, bool>(iterator(p.first), p.second);
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

		void		erase(iterator pos)
		{
			tree_iterator_type t_pos(pos.base());

			_tree.erase(t_pos);
		}

		void		erase(iterator first, iterator last)
		{
			tree_iterator_type t_first(first.base());
			tree_iterator_type t_last(last.base());

			_tree.erase(t_first, t_last);
		}

		size_type	erase(Key const& key)					{ return _tree.erase(key); }

		void		swap(set& other)
		{
			_tree.swap(other._tree);
			ft::swap(_key_compare, other._key_compare);
		}

		size_type		count(Key const& key) const	{ return _tree.count(key); }
		iterator		find(Key const& key)		{ return _tree.find(key); }
		const_iterator	find(Key const& key) const	{ return _tree.find(key); }

		ft::pair<iterator, iterator>
		equal_range(Key const& key)
		{
			return static_cast<set const&>(*this)._tree.equal_range(key);
		}

		ft::pair<const_iterator, const_iterator>
		equal_range(Key const& key) const
		{
			return _tree.equal_range(key);
		}

		const_iterator	lower_bound(Key const& key) const
		{
			return const_iterator(_tree.lower_bound(key));
		}

		iterator	lower_bound(Key const& key)
		{
			return iterator(
				static_cast<set const&>(*this)._tree.lower_bound(key)
			);
		}

		const_iterator	upper_bound(Key const& key) const
		{
			return const_iterator(_tree.upper_bound(key));
		}

		iterator	upper_bound(Key const& key)
		{
			return iterator(
				static_cast<set const&>(*this)._tree.upper_bound(key)
			);
		}

		friend bool	operator==(set const& lhs, set const& rhs)
		{
			return lhs._tree == rhs._tree;
		}

		friend bool	operator!=(set const& lhs, set const& rhs)
		{
			return !(lhs == rhs);
		}

		friend bool	operator<(set const& lhs, set const& rhs)
		{
			return lhs._tree < rhs._tree;
		}

		friend bool	operator>(set const& lhs, set const& rhs)
		{
			return rhs._tree < lhs._tree;
		}

		friend bool	operator>=(set const& lhs, set const& rhs)
		{
			return !(lhs < rhs);
		}

		friend bool	operator<=(set const& lhs, set const& rhs)
		{
			return !(rhs < lhs);
		}
	};

	template<typename Key, typename Compare, typename Allocator>
	void	swap(set<Key, Compare, Allocator>& o1, set<Key, Compare, Allocator>& o2)
	{
		o1.swap(o2);
	}
}

#endif
