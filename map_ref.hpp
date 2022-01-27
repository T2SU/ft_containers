/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_ref.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 17:35:17 by smun              #+#    #+#             */
/*   Updated: 2022/01/27 10:54:42 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include <functional>
# include <memory>
# include "utility.hpp"
# include "type_traits.hpp"
# include "iterator.hpp"
# include "tree.hpp"

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

	private:
		enum { BLACK, RED };
		class node;

		typedef node			node_type;
		typedef node_type*		node_pointer;
		typedef node_type&		node_reference;
		typedef tree_type		tree<value_type, value_compare, Allocator>;

		typedef typename Allocator::template rebind<node_type>::other	node_allocator_type;

	public:
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
		Compare			_compare;
		tree_type		_tree;


	public:
		typedef typename tree_type::iterator				iterator;
		typedef typename tree_type::const_iterator			const_iterator;
		typedef typename tree_type::reverse_iterator		reverse_iterator;
		typedef typename tree_type::const_reverse_iterator	const_reverse_iterator;

		/* Constructor */

		map()
			: _compare(Compare())
			, _allocator(Allocator())
			, _node_allocator(node_allocator_type(_allocator))
			, _root()
			, _begin_ptr(_end_ptr)
			, _end_ptr(createEndNode())
			, _size()
		{
		}

		explicit map(Compare const& cmp, Allocator const& alloc = Allocator())
			: _compare(cmp)
			, _allocator(alloc)
			, _node_allocator(node_allocator_type(_allocator))
			, _root()
			, _begin_ptr(_end_ptr)
			, _end_ptr(createEndNode())
			, _size()
		{
		}

		map(map const& origin)
			: _compare(origin._compare)
			, _allocator(origin._allocator)
			, _node_allocator(origin._node_allocator)
			, _root()
			, _begin_ptr(_end_ptr)
			, _end_ptr(createEndNode())
			, _size()
		{
			insert(origin.begin(), origin.end());
		}

		template<typename InputIt>
		map(
			typename ft::enable_if<ft::is_input_iterator<InputIt>::value, InputIt>::type first,
			typename ft::enable_if<ft::is_input_iterator<InputIt>::value, InputIt>::type last,
			Compare const& comp = Compare(),
			Allocator const& alloc = Allocator()
		)
			: _compare(comp)
			, _allocator(alloc)
			, _node_allocator(node_allocator_type(_allocator))
			, _root()
			, _begin_ptr(_end_ptr)
			, _end_ptr(createEndNode())
			, _size()
		{
			insert(first, last);
		}


		/* Destructor */

		virtual ~map()
		{
			clear();
			destroyNode(_end_ptr);
		}


		/* Operators */
		map*	operator=(map const& other)
		{
			clear();
			insert(other.begin(), other.end());
		}


		/* Allocator getter */
		allocator_type	get_allocator() const	{ return _allocator; }


		/* Accessors */
		T&	at(Key const& key)
		{
			node_pointer	place = findNode(key);

			if (place == nullptr)
				throw std::out_of_range("Key not found");
			return place->getValue().second;
		}

		T	const& at(Key const& key) const
		{
			node_pointer	place = findNode(key);

			if (place == nullptr)
				throw std::out_of_range("Key not found");
			return place->getValue().second;
		}

		T&	operator[](Key const& key)
		{
			node_pointer	parent = _end_ptr;
			node_pointer*	place = findPlace(&_root, key, parent);
			value_type		value(key, T());

			insertNodeAt(parent, place, value, false);
			return (*place)->getValue().second;
		}


		/* Iterators */
		iterator					begin()			{ return iterator(_begin_ptr); }
		const_iterator				begin() const	{ return const_iterator(_begin_ptr);}
		iterator					end()			{ return iterator(_end_ptr); }
		const_iterator				end() const		{ return const_iterator(_end_ptr);}
		reverse_iterator			rbegin()		{ return reverse_iterator(end()); }
		const_reverse_iterator		rbegin() const	{ return const_reverse_iterator(end()); }
		reverse_iterator			rend()			{ return reverse_iterator(begin()); }
		const_reverse_iterator		rend() const	{ return const_reverse_iterator(begin()); }


		/* Capacity */
		bool		empty() const		{ return !_size; }
		size_type	size() const		{ return _size; }
		size_type	max_size() const	{ return _allocator.max_size(); }


		/* Modifiers */
		void		clear()
		{
			destroyNode(_root);
			_root = nullptr;
			_size = 0;
			_end_ptr->setLeftChild(nullptr);
		}

		ft::pair<iterator, bool>	insert(const_reference value)
		{
			node_pointer	parent;
			node_pointer*	place = findPlace(&_root, value.first, parent);
			bool			inserted = insertNodeAt(parent, place, value, true);

			return ft::make_pair<iterator, bool>(iterator(*place), inserted);
		}

		iterator	insert(iterator hint, const_reference value)
		{
			node_pointer	parent;
			node_pointer*	place = findPlaceWithHint(hint, value.first, parent);

			insertNodeAt(parent, place, value, true);
			return iterator(place);
		}

		template<typename InputIt>
		typename ft::enable_if<ft::is_input_iterator<InputIt>::value, void>::type
		insert(InputIt first, InputIt last)
		{
			while (first != last)
				insert(*(first++));
		}

		void		erase(iterator pos)
		{
			deleteNode(pos.base());
			--_size;
		}

		void		erase(iterator first, iterator last)
		{
			while (first != last)
				erase(first++);
		}

		size_type	erase(Key const& key)
		{
			if (_root == nullptr)
				return 0;

			node_pointer	place = findNode(key);
			if (place == nullptr)
				return 0;
			deleteNode(place);
			--_size;
			return 1;
		}

		void		swap(map& other)
		{
			ft::swap(_compare, other._compare);
			ft::swap(_root, other._root);
			ft::swap(_begin_ptr, other._begin_ptr);
			ft::swap(_end_ptr, other._end_ptr);
			ft::swap(_size, other._size);
			ft::swap(_allocator, other._allocator);
			ft::swap(_node_allocator, other._node_allocator);
		}


		/* Lookup */

		size_type		count(Key const& key) const
		{
			return findNode(key) ? 1 : 0;
		}

		iterator		find(Key const& key)
		{
			node_pointer	place = findNode(key);

			if (place == nullptr)
				return end();
			return iterator(place);
		}

		const_iterator	find(Key const& key) const
		{
			node_pointer	place = findNode(key);

			if (place == nullptr)
				return end();
			return const_iterator(place);
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
			node_pointer lowerBound = getLowerBound(key);

			if (lowerBound == nullptr)
				return end();
			return iterator(lowerBound);
		}

		const_iterator	lower_bound(Key const& key) const
		{
			node_pointer lowerBound = getLowerBound(key);

			if (lowerBound == nullptr)
				return end();
			return const_iterator(lowerBound);
		}

		iterator	upper_bound(Key const& key)
		{
			node_pointer upperBound = getUpperBound(key);

			if (upperBound == nullptr)
				return end();
			return iterator(upperBound);
		}

		const_iterator	upper_bound(Key const& key) const
		{
			node_pointer upperBound = getUpperBound(key);

			if (upperBound == nullptr)
				return end();
			return const_iterator(upperBound);
		}


		/* Observers */

		key_compare	key_comp() const
		{
			return _compare;
		}

		value_compare	value_comp() const
		{
			return value_compare(key_comp());
		}

	private:
		class node
		{
		private:
			value_type		_value;
			node_pointer	_parent;
			node_pointer	_left;
			node_pointer	_right;
			int				_color;

			node();
			node& operator=(node const&);
			node(node const& o)
					: _value(value_type())
					, _parent(o._parent)
					, _left(o._left)
					, _right(o._right)
					, _color(o._color) {}

		public:
			node(value_type const& value, node_pointer parent)
				: _value(value)
				, _parent(parent)
				, _left(nullptr)
				, _right(nullptr)
				, _color(RED)
			{}
			virtual ~node() {}

			int				getColor() const		{ return _color; }
			void			setColor(int color)		{ _color = color; }
			value_type&		getValue()				{ return _value; }
			node_pointer&	getParent()				{ return _parent; }
			void			setParent(node* p)		{ _parent = p; }
			node_pointer&	getLeftChild()			{ return _left; }
			node_pointer&	getRightChild()			{ return _right; }
			bool			isOnLeft() const		{ return _parent->_left == this; }
			bool			isOnRight() const		{ return _parent->_right == this; }
			int				getChildCount() const	{ return (_left ? 1 : 0) + (_right ? 1 : 0); }
			node_pointer&	getFirstChild()			{ return _left ? _left : _right; }

			node_pointer	setLeftChild(node_pointer const x)
			{
				if ((_left = x))
					_left->setParent(this);
				return x;
			}

			node_pointer	setRightChild(node_pointer const x)
			{
				if ((_right = x))
					_right->setParent(this);
				return x;
			}

			node_pointer	getMinimum()
			{
				if (_left == nullptr)
					return this;
				return _left->getMinimum();
			}

			node_pointer	getMaximum()
			{
				if (_right == nullptr)
					return this;
				return _right->getMaximum();
			}

			static void	swapColor(node_pointer a, node_pointer b)
			{
				if (a != nullptr && b != nullptr)
					ft::swap(a->_color, b->_color);
				else if (a != nullptr)
					a->setColor(BLACK);
				else if (b != nullptr)
					b->setColor(BLACK);
			}

			static void swapNodes(node_pointer n, node_pointer suc)
			{
				node new_n = *suc;
				node** new_n_place = suc->getPlace();
				node new_suc = *n;
				node** new_suc_place = n->getPlace();
				if (suc->getParent() == n)
				{
					new_n._parent = n;
					if (suc->isOnLeft())
						new_suc._left = n;
					else
						new_suc._right = n;
					new_n_place = nullptr;
				}
				n->setParent(new_n.getParent());
				n->setLeftChild(new_n.getLeftChild());
				n->setRightChild(new_n.getRightChild());
				n->setColor(new_n.getColor());
				if (new_n_place)
					*new_n_place = n;
				suc->setParent(new_suc.getParent());
				suc->setLeftChild(new_suc.getLeftChild());
				suc->setRightChild(new_suc.getRightChild());
				suc->setColor(new_suc.getColor());
				if (new_suc_place)
					*new_suc_place = suc;
			}
		};

		static int		getColor(node const* const n) { return n ? n->getColor() : BLACK; }

		static bool		isDoubleRed(node_pointer const n)
		{
			return getColor(n) == RED && getColor(n->getParent()) == RED;
		}

		static node_pointer	getChildByNear(node_pointer sib)
		{
			bool dbIsOnLeft = !sib->isOnLeft();
			if (dbIsOnLeft)
				return sib->getLeftChild();
			else
				return sib->getRightChild();
		}

		static node_pointer	getChildByFar(node_pointer sib)
		{
			bool dbIsOnLeft = !sib->isOnLeft();
			if (dbIsOnLeft)
				return sib->getRightChild();
			else
				return sib->getLeftChild();
		}

		node_pointer	siblingOf(node_pointer const p, node_pointer const n)
		{
			if (n == _root)
				return nullptr;
			if (p->getLeftChild() == n)
				return p->getRightChild();
			return p->getLeftChild();
		}

		node_pointer	createEndNode()
		{
			return createNode(value_type(), nullptr);
		}

		void	transplant(node_pointer n, node_pointer as)
		{
			if (_root == n)
			{
				_end_ptr->setLeftChild(_root = as);
				return;
			}
			node_pointer p = n->getParent();
			if (p->getLeftChild() == n)
				p->setLeftChild(as);
			if (p->getRightChild() == n)
				p->setRightChild(as);
			n->setParent(nullptr);
		}

		void	leftRotate(node_pointer n)
		{
			node_pointer const p = n->getParent();
			node_pointer const x = n->getLeftChild();

			transplant(p, n);
			n->setLeftChild(p);
			p->setRightChild(x);
		}

		void	rightRotate(node_pointer n)
		{
			node_pointer const p = n->getParent();
			node_pointer const x = n->getRightChild();

			transplant(p, n);
			n->setRightChild(p);
			p->setLeftChild(x);
		}

		node_pointer	findNode(Key const& key)
		{
			node_pointer	parent;
			node_pointer*	place = findPlace(&_root, key, parent);

			return *place;
		}

		node_pointer*	findPlace(node_pointer* place, Key const& key, node_pointer& parent)
		{
			while ((*place) != nullptr)
			{
				parent = (*place)->getParent();
				if (_compare((*place)->getValue().first, key))
				{
					parent = *place;
					place = &((*place)->getRightChild());
				}
				else if (_compare(key, (*place)->getValue().first))
				{
					parent = *place;
					place = &((*place)->getLeftChild());
				}
				else
					break;
			}
			return place;
		}

		// Find node by using hint, and return node_pointer place.
		node_pointer*	findPlaceWithHint(const_iterator hint, Key const& key, node_pointer& parent)
		{
			if (hint == end() || _compare(key, hint->first)) // key < hint
			{
				const_iterator prev = hint;
				if (prev == begin() || _compare((--prev)->first, key)) // --hint < key (*valid hint*)
				{
					if (hint->base()->getLeftChild() == nullptr)
						return &((parent = hint->base())->getLeftChild());
					else
						return &((parent = prev->base())->getRightChild());
				}
				return findPlace(&_root, key, parent); // invalid hint
			}
			else if (_compare(hint->first, key)) // hint < key
			{
				const_iterator next = ++hint;
				if (next == end() || _compare(key, next)) // key < ++hint (*valid hint*)
				{
					if (hint->base()->getRightChild() == nullptr)
						return &((parent = hint->base())->getRightChild());
					else
						return &((parent = next->base())->getLeftChild());
				}
				return findPlace(&_root, key, parent); // invalid hint
			}
			else // hint == key
			{
				parent = hint->base()->getParent();
				if (parent->getLeftChild() == hint->base())
					return &(parent->getLeftChild());
				else
					return &(parent->getRightChild());
			}
		}

		bool	insertNodeAt(node_pointer parent, node_pointer* place, const_reference value, bool overwrite)
		{
			if ((*place) != nullptr)
			{
				if (overwrite)
					(*place)->getValue().second = value.second;
				return false;
			}
			else
			{
				tryFixDoubleRed((*place) = createNode(value, parent));
				if ((*place) == _root)
					_end_ptr->setLeftChild((*place));
				if (_begin_ptr == _end_ptr || _compare(value.first, _begin_ptr->getValue().first))
					_begin_ptr = (*place);
				++_size;
				return true;
			}
		}

		void	tryFixDoubleRed(node_pointer n)
		{
			if (n == nullptr)
				return;
			if (_root == n)
			{
				if (getColor(n) == RED)
					n->setColor(BLACK);
				return;
			}

			node_pointer p = n->getParent();
			node_pointer g = p->getParent();
			node_pointer u = siblingOf(g, p);

			if (p == _root || !isDoubleRed(n))
				return;
			if (getColor(u) == RED)
			{
				u->setColor(BLACK);
				p->setColor(BLACK);
				g->setColor(RED);
				tryFixDoubleRed(g);
			}
			if (!isDoubleRed(n))
				return;
			if (getColor(u) == BLACK)
			{
				node_pointer descendant_of_g = p;
				if (p->isOnLeft())
				{
					if (n->isOnRight())
						leftRotate(descendant_of_g = n);
					node::swapColor(descendant_of_g, g);
					rightRotate(descendant_of_g);
				}
				else
				{
					if (n->isOnLeft())
						rightRotate(descendant_of_g = n);
					node::swapColor(descendant_of_g, g);
					leftRotate(descendant_of_g);
				}
			}
		}

		void	destroyNode(node_pointer n)
		{
			if (n == nullptr)
				return;
			destroyNode(n->getLeftChild());
			destroyNode(n->getRightChild());
		}

		// https://medium.com/analytics-vidhya/deletion-in-red-black-rb-tree-92301e1474ea
		void	deleteNode(node_pointer n)
		{
			if (n->getChildCount() == 2)
			{
				node_pointer suc = n->getRightChild()->getMinimum();
				node::swapNodes(n, suc);
				if (_root == n)
					_root = suc;
			}
			node_pointer c = n->getFirstChild();
			node_pointer p = n->getParent();
			transplant(n, c);
			if (getColor(n) == BLACK)
			{
				if (getColor(c) == RED)
					c->setColor(BLACK);
				else
					fixDoubleBlack(c, p);
			}
			if (!_compare(_begin_ptr->getValue().first, n->getValue().first))
				_begin_ptr = (_root ? _root->getMinimum() : _end_ptr);
			_node_allocator.deallocate(n, 1);
		}

		void	fixDoubleBlack(node_pointer db, node_pointer p)
		{
			if (db == _root) // reached root node
			{
				db->setColor(BLACK);
				return;
			}

			node_pointer s = siblingOf(p, db);
			if (getColor(s) == RED)
			{
				node::swapColor(db, p);
				if (s->isOnLeft())
					rightRotate(s);
				else
					leftRotate(s);
				fixDoubleBlack(db, p);
				return;
			}

			node_pointer nearChild = getChildByNear(s);
			node_pointer farChild = getChildByFar(s);

			if (getColor(nearChild) == BLACK && getColor(farChild) == BLACK)
			{
				s->setColor(RED);
				if (getColor(p) == RED)
					p->setColor(BLACK);
				else
					fixDoubleBlack(p, p->getParent());
			}
			else if (getColor(farChild) == BLACK && getColor(nearChild) == RED)
			{
				node::swapColor(nearChild, s);
				if (s->isOnRight())
					rightRotate(nearChild);
				else
					leftRotate(nearChild);
				fixDoubleBlack(db, p);
			}
			else if (getColor(farChild) == RED)
			{
				node::swapColor(p, s);
				if (s->isOnRight())
					leftRotate(s);
				else
					rightRotate(s);
				if (getColor(db) == RED)
					db->setColor(BLACK);
				farChild->setColor(BLACK);
			}
		}

		node_pointer	createNode(const_reference value, node_pointer parent)
		{
			node_pointer ptr = _node_allocator.allocate(1);
			_node_allocator.construct(ptr, value, parent);
			return ptr;
		}

		node_pointer	getLowerBound(Key const& key)
		{
			node_pointer	ret = _root;
			node_pointer	n = _root;

			while (n != nullptr)
			{
				if (!_compare(n->getValue(), key))
				{
					ret = n;
					n = n->getLeftChild();
				}
				else
					n = n->getRightChild();
			}
			return ret;
		}

		node_pointer	getUpperBound(Key const& key)
		{
			node_pointer	ret = _root;
			node_pointer	n = _root;

			while (n != nullptr)
			{
				if (_compare(key, n->getValue()))
				{
					ret = n;
					n = n->getLeftChild();
				}
				else
					n = n->getRightChild();
			}
			return ret;
		}

	};

	/* Non member operators */

	template<typename Key, typename T, typename Compare, typename Alloc>
	bool	operator==(map<Key,T,Compare,Alloc> const& lhs, map<Key,T,Compare,Alloc> const& rhs)
	{
		return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template<typename Key, typename T, typename Compare, typename Alloc>
	bool	operator<(map<Key,T,Compare,Alloc> const& lhs, map<Key,T,Compare,Alloc> const& rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template<typename Key, typename T, typename Compare, typename Alloc>
	bool	operator!=(map<Key,T,Compare,Alloc> const& lhs, map<Key,T,Compare,Alloc> const& rhs)
	{
		return !(lhs == rhs);
	}

	template<typename Key, typename T, typename Compare, typename Alloc>
	bool	operator>(map<Key,T,Compare,Alloc> const& lhs, map<Key,T,Compare,Alloc> const& rhs)
	{
		return rhs < lhs;
	}

	template<typename Key, typename T, typename Compare, typename Alloc>
	bool	operator>=(map<Key,T,Compare,Alloc> const& lhs, map<Key,T,Compare,Alloc> const& rhs)
	{
		return !(lhs < rhs);
	}

	template<typename Key, typename T, typename Compare, typename Alloc>
	bool	operator<=(map<Key,T,Compare,Alloc> const& lhs, map<Key,T,Compare,Alloc> const& rhs)
	{
		return !(rhs < lhs);
	}

	template<typename ValueType, typename NodePtr, typename DiffType>
	class	MapIterator
	{
	private:
		NodePtr	current;

	public:
		typedef NodePtr						node_pointer;
		typedef ValueType					value_type;
		typedef DiffType					difference_type;
		typedef ValueType*					pointer;
		typedef ValueType&					reference;
		typedef bidirectional_iterator_tag	iterator_category;

		MapIterator() : current() {}
		virtual ~MapIterator() {}
		explicit MapIterator(NodePtr iter) : current(iter) {}
		MapIterator(MapIterator const& origin) : current(origin.base()) {}

		MapIterator& operator=(MapIterator const& another)
		{
			if (this != &another)
				current = another.base();
			return *this;
		}

		node_pointer	base() const
		{
			return current;
		}

		reference	operator*() const
		{
			return current->getValue();
		}

		pointer	operator->() const
		{
			return &(operator*());
		}

		MapIterator&	operator++()
		{
			if (current->getRightChild() != nullptr)
				return current = current->getRightChild()->getMinimum();
			while (current->isOnRight())
				current = current->getParent();
			current = current->getParent();
			return *this;
		}

		MapIterator	operator++(int)
		{
			MapIterator tmp(*this);
			++(*this);
			return tmp;
		}

		MapIterator&	operator--()
		{
			if (current->getLeftChild() != nullptr)
				return current = current->getLeftChild()->getMaximum();
			while (current->isOnLeft())
				current = current->getParent();
			current = current->getParent();
			return *this;
		}

		MapIterator	operator--(int)
		{
			MapIterator tmp(*this);
			--(*this);
			return tmp;
		}
	};

	template<typename MapIter>
	class	ConstMapIterator
	{
	private:
		MapIter mapIter;
		ConstMapIterator();

	public:
		typedef typename MapIter::node_pointer		node_pointer;
		typedef typename MapIter::value_type		value_type;
		typedef typename MapIter::difference_type	difference_type;
		typedef value_type const*					pointer;
		typedef value_type const&					reference;
		typedef bidirectional_iterator_tag			iterator_category;

		virtual ~ConstMapIterator() {}
		ConstMapIterator(MapIter const& mi) : mapIter(mi) {}
		ConstMapIterator(ConstMapIterator const& origin) : mapIter(origin.mapIter) {}

		ConstMapIterator& operator=(ConstMapIterator const& another)
		{
			if (this != &another)
				mapIter = another.mapIter;
			return *this;
		}

		node_pointer	base() const 		{ return mapIter.base(); }
		reference operator*() const			{ return *mapIter; }
		pointer	operator->() const			{ return mapIter.operator->(); }
		ConstMapIterator& operator++()		{ ++mapIter; return *this; }
		ConstMapIterator& operator++(int)	{ ConstMapIterator tmp(*this); ++mapIter; return tmp; }
		ConstMapIterator& operator--()		{ --mapIter; return *this; }
		ConstMapIterator& operator--(int)	{ ConstMapIterator tmp(*this); --mapIter; return tmp; }
	};

	template<typename ValueType, typename NodePtr, typename DiffType>
	bool	operator==(MapIterator<ValueType, NodePtr, DiffType> const& lhs, MapIterator<ValueType, NodePtr, DiffType> const& rhs)
	{
		return lhs.base() == rhs.base();
	}

	template<typename ValueType, typename NodePtr, typename DiffType>
	bool	operator!=(MapIterator<ValueType, NodePtr, DiffType> const& lhs, MapIterator<ValueType, NodePtr, DiffType> const& rhs)
	{
		return lhs.base() != rhs.base();
	}

	template<typename MapIter>
	bool	operator==(ConstMapIterator<MapIter> const& lhs, ConstMapIterator<MapIter> const& rhs)
	{
		return lhs.base() == rhs.base();
	}

	template<typename MapIter>
	bool	operator!=(ConstMapIterator<MapIter> const& lhs, ConstMapIterator<MapIter> const& rhs)
	{
		return lhs.base() != rhs.base();
	}
}

#endif
