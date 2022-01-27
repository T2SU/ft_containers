/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 18:54:13 by smun              #+#    #+#             */
/*   Updated: 2022/01/27 17:48:50 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_HPP
# define TREE_HPP

# include "iterator.hpp"
# include "utility.hpp"

namespace ft
{
	template<typename Key, typename T, typename Value, typename Compare, typename Allocator>
	class tree
	{
	private:
		enum { BLACK, RED };

		class node
		{
		private:
			typedef node*	NodePtr;

			Value	_value;
			NodePtr	_parent;
			NodePtr	_left;
			NodePtr	_right;
			int		_color;

			node();
			node& operator=(node const&);
			node(node const&);

		public:
			node(Value const& value, NodePtr parent)
				: _value(value)
				, _parent(parent)
				, _left(nullptr)
				, _right(nullptr)
				, _color(RED)
			{}
			virtual ~node() {}

			int				getColor() const				{ return _color; }
			void			setColor(int color)				{ _color = color; }
			Value&			getValue()						{ return _value; }
			NodePtr&		getParent()						{ return _parent; }
			void			setParent(NodePtr p)			{ _parent = p; }
			NodePtr&		getLeftChild()					{ return _left; }
			NodePtr&		getRightChild()					{ return _right; }
			bool			isOnLeft() const				{ return _parent->_left == this; }
			bool			isOnRight() const				{ return _parent->_right == this; }
			int				getChildCount() const			{ return (_left ? 1 : 0) + (_right ? 1 : 0); }
			NodePtr&		getFirstChild()					{ return _left ? _left : _right; }
			void			setLeftChild(NodePtr const x)	{ if ((_left = x)) _left->setParent(this); }
			void			setRightChild(NodePtr const x)	{ if ((_right = x)) _right->setParent(this); }
			NodePtr			getMinimum()					{ return _left ? _left->getMinimum() : this; }
			NodePtr			getMaximum()					{ return _right ? _right->getMaximum() : this; }
			NodePtr*		getPlace()	const				{ return isOnLeft() ? &(_parent->_left) : &(_parent->_right); }

			static void		swapColor(NodePtr a, NodePtr b);
			static void		swapNodes(NodePtr n, NodePtr suc);

		private:
			struct plan
			{
				node* parent;
				node* left;
				node* right;
				int color;
				node** place;

				plan(node const& o)
					: parent(o._parent)
					, left(o._left)
					, right(o._right)
					, color(o._color)
					, place(o.getPlace()) {}
			};
		};

	public:
		typedef Allocator									allocator_type;
		typedef Key											key_type;
		typedef T											mapped_type;
		typedef typename allocator_type::value_type			value_type;
		typedef typename allocator_type::size_type			size_type;
		typedef typename allocator_type::difference_type	difference_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;

	private:
		typedef node		node_type;
		typedef node_type*	node_pointer;
		typedef node_type&	node_reference;

		typedef typename Allocator::template rebind<node_type>::other	node_allocator_type;

		Compare				_key_compare;
		node_pointer		_root;
		node_pointer		_end_ptr;
		node_pointer		_begin_ptr;
		size_type			_size;
		allocator_type		_allocator;
		node_allocator_type	_node_allocator;

		static int		getColor(node const* const n) { return n ? n->getColor() : BLACK; }

	public:
		class TreeIterator
		{
		private:
			tree::node_pointer	current;

		public:
			typedef	tree::node_pointer				node_pointer;
			typedef tree::value_type				value_type;
			typedef tree::difference_type			difference_type;
			typedef tree::value_type*				pointer;
			typedef tree::value_type&				reference;
			typedef bidirectional_iterator_tag		iterator_category;

			TreeIterator() : current() {}
			explicit TreeIterator(node_pointer iter) : current(iter) {}
			TreeIterator(TreeIterator const& origin) : current(origin.base()) {}
			virtual ~TreeIterator() {}

			TreeIterator&	operator=(TreeIterator const& another)
			{
				if (this != & another)
					current = another.base();
				return *this;
			}

			node_pointer	base() const		{ return current; }
			reference		operator*() const	{ return current->getValue(); }
			pointer			operator->() const	{ return &operator*(); }

			TreeIterator&	operator++()
			{
				if (current->getRightChild() != nullptr)
				{
					current = current->getRightChild()->getMinimum();
					return *this;
				}
				while (current->isOnRight())
					current = current->getParent();
				current = current->getParent();
				return *this;
			}

			TreeIterator	operator++(int)
			{
				TreeIterator tmp(*this);
				++(*this);
				return tmp;
			}

			TreeIterator&	operator--()
			{
				if (current->getLeftChild() != nullptr)
				{
					current = current->getLeftChild()->getMaximum();
					return *this;
				}
				while (current->isOnLeft())
					current = current->getParent();
				current = current->getParent();
				return *this;
			}

			TreeIterator	operator--(int)
			{
				TreeIterator tmp(*this);
				--(*this);
				return tmp;
			}

			friend bool	operator==(TreeIterator const& lhs, TreeIterator const& rhs)
			{
				return lhs.base() == rhs.base();
			}

			friend bool	operator!=(TreeIterator const& lhs, TreeIterator const& rhs)
			{
				return lhs.base() != rhs.base();
			}
		};

		template<typename TreeIter>
		class ConstTreeIterator
		{
		private:
			TreeIter treeIter;
			ConstTreeIterator();

		public:
			typedef typename TreeIter::node_pointer		node_pointer;
			typedef typename TreeIter::value_type		value_type;
			typedef typename TreeIter::difference_type	difference_type;
			typedef value_type const*					pointer;
			typedef value_type const&					reference;
			typedef bidirectional_iterator_tag			iterator_category;

			virtual ~ConstTreeIterator() {}
			ConstTreeIterator(TreeIter const& mi) : treeIter(mi) {}
			ConstTreeIterator(ConstTreeIterator const& origin) : treeIter(origin.treeIter) {}

			ConstTreeIterator& operator=(ConstTreeIterator const& another)
			{
				if (this != &another)
					treeIter = another.treeIter;
				return *this;
			}

			node_pointer		base() const 		{ return treeIter.base(); }
			reference			operator*() const	{ return *treeIter; }
			pointer				operator->() const	{ return treeIter.operator->(); }
			ConstTreeIterator&	operator++()		{ ++treeIter; return *this; }
			ConstTreeIterator&	operator++(int)		{ ConstTreeIterator tmp(*this); ++treeIter; return tmp; }
			ConstTreeIterator&	operator--()		{ --treeIter; return *this; }
			ConstTreeIterator&	operator--(int)		{ ConstTreeIterator tmp(*this); --treeIter; return tmp; }

			friend bool	operator==(ConstTreeIterator const& lhs, ConstTreeIterator const& rhs)
			{
				return lhs.base() == rhs.base();
			}

			friend bool	operator!=(ConstTreeIterator const& lhs, ConstTreeIterator const& rhs)
			{
				return lhs.base() == rhs.base();
			}
		};

		explicit tree(Compare const& cmp, Allocator const& alloc = Allocator())
			: _key_compare(cmp)
			, _allocator(alloc)
			, _node_allocator(node_allocator_type(_allocator))
			, _root()
			, _begin_ptr(_end_ptr)
			, _end_ptr(createEndNode())
			, _size()
		{}

		tree(tree const& origin)
			: _key_compare(origin._key_compare)
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
		tree(
			typename ft::enable_if<ft::is_input_iterator<InputIt>::value, InputIt>::type first,
			typename ft::enable_if<ft::is_input_iterator<InputIt>::value, InputIt>::type last,
			Compare const& comp = Compare(),
			Allocator const& alloc = Allocator()
		)
			: _key_compare(comp)
			, _allocator(alloc)
			, _node_allocator(node_allocator_type(_allocator))
			, _root()
			, _begin_ptr(_end_ptr)
			, _end_ptr(createEndNode())
			, _size()
		{
			insert(first, last);
		}

		virtual ~tree()
		{
			clear();
			destroyNode(_end_ptr);
		}

		tree&	operator=(tree const& other)
		{
			clear();
			insert(other.begin(), other.end());
		}

		allocator_type	get_allocator() const { return _allocator; }


		typedef TreeIterator								iterator;
		typedef ConstTreeIterator<iterator>					const_iterator;
		typedef ft::reverse_iterator<iterator>				reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

		iterator					begin()			{ return iterator(_begin_ptr); }
		const_iterator				begin() const	{ return const_iterator(_begin_ptr);}
		iterator					end()			{ return iterator(_end_ptr); }
		const_iterator				end() const		{ return const_iterator(_end_ptr);}
		reverse_iterator			rbegin()		{ return reverse_iterator(end()); }
		const_reverse_iterator		rbegin() const	{ return const_reverse_iterator(end()); }
		reverse_iterator			rend()			{ return reverse_iterator(begin()); }
		const_reverse_iterator		rend() const	{ return const_reverse_iterator(begin()); }

		bool		empty() const		{ return !_size; }
		size_type	size() const		{ return _size; }
		size_type	max_size() const	{ return _allocator.max_size(); }

		void		clear();

		ft::pair<iterator, bool>	insert(const_reference value);
		iterator					insert(iterator hint, const_reference value);

		template<typename InputIt>
		typename ft::enable_if<ft::is_input_iterator<InputIt>::value, void>::type
		insert(InputIt first, InputIt last);

		void			erase(iterator pos);
		void			erase(iterator first, iterator last);
		size_type		erase(Key const& key);
		void			swap(tree& other);

		size_type		count(Key const& key) const;
		iterator		find(Key const& key);
		const_iterator	find(Key const& key) const;

		node_pointer	upper_bound(Key const& key);
		node_pointer	lower_bound(Key const& key);

		T&				operator[](Key const& key);

	private:
		static bool			isDoubleRed(node_pointer const n);
		static node_pointer	getChildByNear(node_pointer sib);
		static node_pointer	getChildByFar(node_pointer sib);
		node_pointer		siblingOf(node_pointer const p, node_pointer const n);
		void				transplant(node_pointer n, node_pointer as);
		void				leftRotate(node_pointer n);
		void				rightRotate(node_pointer n);
		node_pointer		findNode(Key const& key);
		node_pointer&		findPlace(node_pointer& place, Key const& key, node_pointer& parent);
		node_pointer&		findPlaceWithHint(const_iterator hint, Key const& key, node_pointer& parent);
		bool				insertNodeAt(node_pointer parent, node_pointer& place, const_reference value, bool overwrite);
		void				tryFixDoubleRed(node_pointer n);
		void				destroyNode(node_pointer n);
		void				deleteNode(node_pointer n);
		void				fixDoubleBlack(node_pointer db, node_pointer p);
		node_pointer		createNode(const_reference value, node_pointer parent);
		node_pointer		createEndNode() { return createNode(Value(), nullptr); }

	};

# define TREE tree<Key, T, Value, Compare, Allocator>

	template<typename Key, typename T, typename Value, typename Compare, typename Allocator>
	void
	TREE::node::swapColor(TREE::node *a, TREE::node *b)
	{
		if (a != nullptr && b != nullptr)
			ft::swap(a->_color, b->_color);
		else if (a != nullptr)
			a->setColor(BLACK);
		else if (b != nullptr)
			b->setColor(BLACK);
	}

	template<typename Key, typename T, typename Value, typename Compare, typename Allocator>
	void
	TREE::node::swapNodes(TREE::node *n, TREE::node *suc)
	{
		plan	new_n(*suc);
		plan	new_suc(*n);

		if (suc->getParent() == n)
		{
			new_n.parent = n;
			if (suc->isOnLeft())
				new_suc.left = n;
			else
				new_suc.right = n;
			new_n.place = nullptr;
		}
		n->setParent(new_n.parent);
		n->setLeftChild(new_n.left);
		n->setRightChild(new_n.right);
		n->setColor(new_n.color);
		if (new_n.place)
			*new_n.place = n;
		suc->setParent(new_suc.parent);
		suc->setLeftChild(new_suc.left);
		suc->setRightChild(new_suc.right);
		suc->setColor(new_suc.color);
		if (new_suc.place)
			*new_suc.place = suc;
	}

	template<typename Key, typename T, typename Value, typename Compare, typename Allocator>
	bool
	TREE::isDoubleRed(node_pointer const n)
	{
		return tree::getColor(n) == RED && tree::getColor(n->getParent()) == RED;
	}

	template<typename Key, typename T, typename Value, typename Compare, typename Allocator>
	typename TREE::node_pointer
	TREE::getChildByNear(node_pointer sib)
	{
		bool dbIsOnLeft = !sib->isOnLeft();
		if (dbIsOnLeft)
			return sib->getLeftChild();
		else
			return sib->getRightChild();
	}

	template<typename Key, typename T, typename Value, typename Compare, typename Allocator>
	typename TREE::node_pointer
	TREE::getChildByFar(node_pointer sib)
	{
		bool dbIsOnLeft = !sib->isOnLeft();
		if (dbIsOnLeft)
			return sib->getRightChild();
		else
			return sib->getLeftChild();
	}

	template<typename Key, typename T, typename Value, typename Compare, typename Allocator>
	typename TREE::node_pointer
	TREE::siblingOf(node_pointer const p, node_pointer const n)
	{
		if (n == _root)
			return nullptr;
		if (p->getLeftChild() == n)
			return p->getRightChild();
		return p->getLeftChild();
	}

	template<typename Key, typename T, typename Value, typename Compare, typename Allocator>
	void
	TREE::transplant(node_pointer n, node_pointer as)
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

	template<typename Key, typename T, typename Value, typename Compare, typename Allocator>
	void
	TREE::leftRotate(node_pointer n)
	{
		node_pointer const p = n->getParent();
		node_pointer const x = n->getLeftChild();

		transplant(p, n);
		n->setLeftChild(p);
		p->setRightChild(x);
	}

	template<typename Key, typename T, typename Value, typename Compare, typename Allocator>
	void
	TREE::rightRotate(node_pointer n)
	{
		node_pointer const p = n->getParent();
		node_pointer const x = n->getRightChild();

		transplant(p, n);
		n->setRightChild(p);
		p->setLeftChild(x);
	}

	template<typename Key, typename T, typename Value, typename Compare, typename Allocator>
	typename TREE::node_pointer
	TREE::findNode(Key const& key)
	{
		node_pointer	parent;
		node_pointer&	place = findPlace(_root, key, parent);

		return place;
	}

	template<typename Key, typename T, typename Value, typename Compare, typename Allocator>
	typename TREE::node_pointer&
	TREE::findPlace(node_pointer& place, Key const& key, node_pointer& parent)
	{
		node_pointer	current = place;
		node_pointer*	ret = &place;
		while (current != nullptr)
		{
			parent = current->getParent();
			if (_key_compare(current->getValue().first, key))
			{
				parent = current;
				node_pointer& rc = current->getRightChild();
				ret = &rc;
				current = rc;
			}
			else if (_key_compare(key, current->getValue().first))
			{
				parent = current;
				node_pointer& lc = current->getLeftChild();
				ret = &lc;
				current = lc;
			}
			else
				break;
		}
		return *ret;
	}

	template<typename Key, typename T, typename Value, typename Compare, typename Allocator>
	typename TREE::node_pointer&
	TREE::findPlaceWithHint(const_iterator hint, Key const& key, node_pointer& parent)
	{
		if (hint == end() || _key_compare(key, hint->first)) // key < hint
		{
			const_iterator prev = hint;
			if (prev == begin() || _key_compare((--prev)->first, key)) // --hint < key (*valid hint*)
			{
				if (hint->base()->getLeftChild() == nullptr)
					return (parent = hint->base())->getLeftChild();
				else
					return (parent = prev->base())->getRightChild();
			}
			return findPlace(_root, key, parent); // invalid hint
		}
		else if (_key_compare(*hint, key)) // hint < key
		{
			const_iterator next = ++hint;
			if (next == end() || _key_compare(key, next->first)) // key < ++hint (*valid hint*)
			{
				if (hint->base()->getRightChild() == nullptr)
					return (parent = hint->base())->getRightChild();
				else
					return (parent = next->base())->getLeftChild();
			}
			return findPlace(_root, key, parent); // invalid hint
		}
		else // hint == key
		{
			parent = hint->base()->getParent();
			if (parent->getLeftChild() == hint->base())
				return parent->getLeftChild();
			else
				return parent->getRightChild();
		}
	}

	template<typename Key, typename T, typename Value, typename Compare, typename Allocator>
	bool
	TREE::insertNodeAt(node_pointer parent, node_pointer& place, const_reference value, bool overwrite)
	{
		if (place != nullptr)
		{
			if (overwrite)
				place->getValue().second = value.second;
			return false;
		}
		else
		{
			tryFixDoubleRed(place = createNode(value, parent));
			if (place == _root)
				_end_ptr->setLeftChild(place);
			if (_begin_ptr == _end_ptr || _key_compare(value.first, _begin_ptr->getValue().first))
				_begin_ptr = place;
			++_size;
			return true;
		}
	}

	template<typename Key, typename T, typename Value, typename Compare, typename Allocator>
	void
	TREE::tryFixDoubleRed(node_pointer n)
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

	template<typename Key, typename T, typename Value, typename Compare, typename Allocator>
	void
	TREE::destroyNode(node_pointer n)
	{
		if (n == nullptr)
			return;
		destroyNode(n->getLeftChild());
		destroyNode(n->getRightChild());
	}

	// https://medium.com/analytics-vidhya/deletion-in-red-black-rb-tree-92301e1474ea
	template<typename Key, typename T, typename Value, typename Compare, typename Allocator>
	void
	TREE::deleteNode(node_pointer n)
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
		if (!_key_compare(_begin_ptr->getValue().first, n->getValue().first))
			_begin_ptr = (_root ? _root->getMinimum() : _end_ptr);
		_node_allocator.deallocate(n, 1);
	}

	template<typename Key, typename T, typename Value, typename Compare, typename Allocator>
	void
	TREE::fixDoubleBlack(node_pointer db, node_pointer p)
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

	template<typename Key, typename T, typename Value, typename Compare, typename Allocator>
	typename TREE::node_pointer
	TREE::createNode(const_reference value, node_pointer parent)
	{
		node_pointer ptr = _node_allocator.allocate(1);
		_node_allocator.construct(ptr, value, parent);
		return ptr;
	}


	template<typename Key, typename T, typename Value, typename Compare, typename Allocator>
	void
	TREE::clear()
	{
		destroyNode(_root);
		_root = nullptr;
		_size = 0;
		_end_ptr->setLeftChild(nullptr);
	}

	template<typename Key, typename T, typename Value, typename Compare, typename Allocator>
	ft::pair<typename TREE::iterator, bool>
	TREE::insert(const_reference value)
	{
		node_pointer	parent;
		node_pointer&	place = findPlace(_root, value.first, parent);
		bool			inserted = insertNodeAt(parent, place, value, true);

		return ft::make_pair<iterator, bool>(iterator(*place), inserted);
	}

	template<typename Key, typename T, typename Value, typename Compare, typename Allocator>
	typename TREE::iterator
	TREE::insert(iterator hint, const_reference value)
	{
		node_pointer	parent;
		node_pointer&	place = findPlaceWithHint(hint, value.first, parent);

		insertNodeAt(parent, place, value, true);
		return iterator(place);
	}

	template<typename Key, typename T, typename Value, typename Compare, typename Allocator>
	template<typename InputIt>
	typename ft::enable_if<ft::is_input_iterator<InputIt>::value, void>::type
	TREE::insert(InputIt first, InputIt last)
	{
		while (first != last)
			insert(*(first++));
	}

	template<typename Key, typename T, typename Value, typename Compare, typename Allocator>
	void
	TREE::erase(iterator pos)
	{
		deleteNode(pos.base());
		--_size;
	}

	template<typename Key, typename T, typename Value, typename Compare, typename Allocator>
	void
	TREE::erase(iterator first, iterator last)
	{
		while (first != last)
			erase(first++);
	}

	template<typename Key, typename T, typename Value, typename Compare, typename Allocator>
	typename TREE::size_type
	TREE::erase(Key const& key)
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

	template<typename Key, typename T, typename Value, typename Compare, typename Allocator>
	void	TREE::swap(tree& other)
	{
		ft::swap(_key_compare, other._key_compare);
		ft::swap(_root, other._root);
		ft::swap(_begin_ptr, other._begin_ptr);
		ft::swap(_end_ptr, other._end_ptr);
		ft::swap(_size, other._size);
		ft::swap(_allocator, other._allocator);
		ft::swap(_node_allocator, other._node_allocator);
	}

	template<typename Key, typename T, typename Value, typename Compare, typename Allocator>
	typename TREE::size_type
	TREE::count(Key const& key) const
	{
		return findNode(key) ? 1 : 0;
	}

	template<typename Key, typename T, typename Value, typename Compare, typename Allocator>
	typename TREE::iterator
	TREE::find(Key const& key)
	{
		node_pointer	place = findNode(key);

		if (place == nullptr)
			return end();
		return iterator(place);
	}

	template<typename Key, typename T, typename Value, typename Compare, typename Allocator>
	typename TREE::const_iterator
	TREE::find(Key const& key) const
	{
		node_pointer	place = findNode(key);

		if (place == nullptr)
			return end();
		return const_iterator(place);
	}

	template<typename Key, typename T, typename Value, typename Compare, typename Allocator>
	typename TREE::node_pointer
	TREE::upper_bound(Key const& key)
	{
		node_pointer	ret = _root;
		node_pointer	n = _root;

		while (n != nullptr)
		{
			if (_key_compare(key, n->getValue().first))
			{
				ret = n;
				n = n->getLeftChild();
			}
			else
				n = n->getRightChild();
		}
		return ret;
	}

	template<typename Key, typename T, typename Value, typename Compare, typename Allocator>
	typename TREE::node_pointer
	TREE::lower_bound(Key const& key)
	{
		node_pointer	ret = _root;
		node_pointer	n = _root;

		while (n != nullptr)
		{
			if (!_key_compare(n->getValue().first, key))
			{
				ret = n;
				n = n->getLeftChild();
			}
			else
				n = n->getRightChild();
		}
		return ret;
	}

	template<typename Key, typename T, typename Value, typename Compare, typename Allocator>
	T&
	TREE::operator[](Key const& key)
	{
		node_pointer	parent = _end_ptr;
		node_pointer&	place = findPlace(_root, key, parent);

		insertNodeAt(parent, place, value_type(key, T()), false);
		return place->getValue().second;
	}

	template<typename Key, typename T, typename Value, typename Compare, typename Allocator>
	bool	operator==(TREE const& lhs, TREE const& rhs)
	{
		return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}
	template<typename Key, typename T, typename Value, typename Compare, typename Allocator>
	bool	operator<(TREE const& lhs, TREE const& rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template<typename Key, typename T, typename Value, typename Compare, typename Allocator>
	bool	operator!=(TREE const& lhs, TREE const& rhs)
	{
		return !(lhs == rhs);
	}

	template<typename Key, typename T, typename Value, typename Compare, typename Allocator>
	bool	operator>(TREE const& lhs, TREE const& rhs)
	{
		return rhs < lhs;
	}

	template<typename Key, typename T, typename Value, typename Compare, typename Allocator>
	bool	operator>=(TREE const& lhs, TREE const& rhs)
	{
		return !(lhs < rhs);
	}

	template<typename Key, typename T, typename Value, typename Compare, typename Allocator>
	bool	operator<=(TREE const& lhs, TREE const& rhs)
	{
		return !(rhs < lhs);
	}

# undef TREE

}

#endif