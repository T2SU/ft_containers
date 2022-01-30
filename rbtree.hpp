/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 18:54:13 by smun              #+#    #+#             */
/*   Updated: 2022/01/30 20:44:10 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_HPP
# define RBTREE_HPP

# include "iterator.hpp"
# include "utility.hpp"
# include "algorithm.hpp"

namespace ft
{
	enum { NodeColor_Black, NodeColor_Red };

	template<typename Value>
	class Node
	{
	private:
		typedef Node*	NodePtr;

		Value	_value;
		NodePtr	_parent;
		NodePtr	_left;
		NodePtr	_right;
		int		_color;

		Node();
		Node& operator=(Node const&);
		Node(Node const&);

	public:
		Node(Value const& value, NodePtr parent)
			: _value(value)
			, _parent(parent)
			, _left(nullptr)
			, _right(nullptr)
			, _color(NodeColor_Red)
		{}
		virtual ~Node() {}

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
		NodePtr&		getFirstChild() 				{ return _left ? _left : _right; }
		void			setLeftChild(NodePtr const x)	{ if ((_left = x)) _left->setParent(this); }
		void			setRightChild(NodePtr const x)	{ if ((_right = x)) _right->setParent(this); }
		NodePtr			getMinimum()					{ return _left ? _left->getMinimum() : this; }
		NodePtr			getMaximum()					{ return _right ? _right->getMaximum() : this; }
		NodePtr*		getPlace() const				{ return isOnLeft() ? &(_parent->_left) : &(_parent->_right); }

		NodePtr			getPrev()
		{
			NodePtr cur = this;
			if (_left)
				return _left->getMaximum();
			while (cur->isOnLeft())
				cur = cur->_parent;
			return cur->_parent;
		}

		NodePtr			getNext()
		{
			NodePtr cur = this;
			if (_right)
				return _right->getMinimum();
			while (cur->isOnRight())
				cur = cur->_parent;
			return cur->_parent;
		}

		static void		swapColor(NodePtr a, NodePtr b);
		static void		swapNodes(NodePtr n, NodePtr suc);

	private:
		struct Plan
		{
			Node* parent;
			Node* left;
			Node* right;
			int color;
			Node** place;

			Plan(Node const& o)
				: parent(o._parent)
				, left(o._left)
				, right(o._right)
				, color(o._color)
				, place(o.getPlace()) {}
		};
	};

	template<typename NodePtr, typename ValueType, typename DifferenceType>
	class TreeIterator
	{
	private:
		NodePtr	_current;

	public:
		typedef	NodePtr						NodePointer;
		typedef ValueType					value_type;
		typedef DifferenceType				difference_type;
		typedef ValueType*					pointer;
		typedef ValueType&					reference;
		typedef bidirectional_iterator_tag	iterator_category;

		TreeIterator() : _current() {}
		TreeIterator(NodePointer ptr) : _current(ptr) {}
		TreeIterator(TreeIterator const& origin) : _current(origin.base()) {}
		virtual ~TreeIterator() {}

		TreeIterator&	operator=(TreeIterator const& another)
		{
			if (this != & another)
				_current = another.base();
			return *this;
		}

		NodePointer		base() const			{ return _current; }
		reference		operator*() const		{ return _current->getValue(); }
		pointer			operator->() const		{ return &(_current->getValue()); }
		TreeIterator&	operator++()			{ _current = _current->getNext(); return *this; }
		TreeIterator&	operator--()			{ _current = _current->getPrev(); return *this; }

		const TreeIterator	operator++(int)
		{
			TreeIterator const tmp(*this);
			++(*this);
			return tmp;
		}

		const TreeIterator	operator--(int)
		{
			TreeIterator const tmp(*this);
			--(*this);
			return tmp;
		}

		friend bool	operator==(TreeIterator const& lhs, TreeIterator const& rhs)
		{
			return lhs.base() == rhs.base();
		}

		friend bool	operator!=(TreeIterator const& lhs, TreeIterator const& rhs)
		{
			return !(lhs == rhs);
		}
	};

	template<typename NodePtr, typename ValueType, typename DifferenceType>
	class ConstTreeIterator
	{
	public:
		typedef	NodePtr						NodePointer;
		typedef ValueType					value_type;
		typedef DifferenceType				difference_type;
		typedef ValueType*					pointer;
		typedef ValueType&					reference;
		typedef bidirectional_iterator_tag	iterator_category;

	private:
		NodePointer	_current;

	public:
		ConstTreeIterator()
			: _current() {}
		ConstTreeIterator(TreeIterator<NodePtr, ValueType, DifferenceType> treeIter)
			: _current(treeIter.base()) {}
		ConstTreeIterator(NodePointer current)
			: _current(current) {}
		ConstTreeIterator(ConstTreeIterator const& origin)
			: _current(origin._current) {}
		virtual ~ConstTreeIterator() {}

		ConstTreeIterator&	operator=(ConstTreeIterator const& another)
		{
			if (this != & another)
				_current = another._current;
			return *this;
		}

		NodePointer		base() const		{ return _current; }
		reference		operator*() const	{ return _current->getValue(); }
		pointer			operator->() const	{ return &(_current->getValue()); }
		ConstTreeIterator&	operator++()	{ _current = _current->getNext(); return *this; }
		ConstTreeIterator&	operator--()	{ _current = _current->getPrev(); return *this; }

		ConstTreeIterator const	operator++(int)
		{
			ConstTreeIterator const tmp(*this);
			++(*this);
			return tmp;
		}

		ConstTreeIterator const	operator--(int)
		{
			ConstTreeIterator const tmp(*this);
			--(*this);
			return tmp;
		}

		friend bool	operator==(ConstTreeIterator const& lhs, ConstTreeIterator const& rhs)
		{
			return lhs.base() == rhs.base();
		}

		friend bool	operator!=(ConstTreeIterator const& lhs, ConstTreeIterator const& rhs)
		{
			return !(lhs == rhs);
		}
	};

	template<typename Key, typename T, typename Value, typename Compare, typename Allocator>
	class tree
	{
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
		typedef Node<Value>			NodeType;
		typedef NodeType*			NodePointer;
		typedef NodeType&			NodeReference;

		typedef typename Allocator::template rebind<NodeType>::other	NodeAllocatorType;

		Compare				_key_compare;
		allocator_type		_allocator;
		NodeAllocatorType	_node_allocator;
		NodePointer			_root;
		NodePointer			_end_ptr;
		NodePointer			_begin_ptr;
		size_type			_size;

		static int		getColor(NodePointer const n) { return n ? n->getColor() : NodeColor_Black; }

	public:
		explicit tree(Compare const& cmp, Allocator const& alloc = Allocator())
			: _key_compare(cmp)
			, _allocator(alloc)
			, _node_allocator(NodeAllocatorType(_allocator))
			, _root()
			, _end_ptr(createEndNode())
			, _begin_ptr(_end_ptr)
			, _size()
		{}

		tree(tree const& origin)
			: _key_compare(origin._key_compare)
			, _allocator(origin._allocator)
			, _node_allocator(origin._node_allocator)
			, _root()
			, _end_ptr(createEndNode())
			, _begin_ptr(_end_ptr)
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
			, _node_allocator(NodeAllocatorType(_allocator))
			, _root()
			, _end_ptr(createEndNode())
			, _begin_ptr(_end_ptr)
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

		typedef TreeIterator<NodePointer, value_type, difference_type>		iterator;
		typedef ConstTreeIterator<NodePointer, value_type, difference_type>	const_iterator;

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
		size_type	max_size() const
		{
			return ft::min<size_type>(
				_node_allocator.max_size(),
				std::numeric_limits<difference_type>::max()
			);
		}

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

		NodePointer		upper_bound(Key const& key) const;
		NodePointer		lower_bound(Key const& key) const;

		ft::pair<iterator, iterator>				equal_range(Key const& key);
		ft::pair<const_iterator, const_iterator>	equal_range(Key const& key) const;

		T&				operator[](Key const& key);

	private:
		static bool			isDoubleRed(NodePointer const n);
		static NodePointer	getChildByNear(NodePointer sib);
		static NodePointer	getChildByFar(NodePointer sib);
		NodePointer			siblingOf(NodePointer const p, NodePointer const n) const;
		void				transplant(NodePointer n, NodePointer as);
		void				leftRotate(NodePointer n);
		void				rightRotate(NodePointer n);
		NodePointer			findNode(Key const& key) const;
		NodePointer&		findPlace(NodePointer& place, Key const& key, NodePointer& parent);
		NodePointer&		findPlaceWithHint(const_iterator hint, Key const& key, NodePointer& parent);
		bool				insertNodeAt(NodePointer parent, NodePointer& place, const_reference value, bool overwrite);
		void				tryFixDoubleRed(NodePointer n);
		void				destroyNode(NodePointer n);
		void				deleteNode(NodePointer n);
		void				fixDoubleBlack(NodePointer db, NodePointer p);
		NodePointer			createNode(const_reference value, NodePointer parent);
		NodePointer			createEndNode() { return createNode(Value(), nullptr); }
	};

# define TREE tree<Key, T, Value, Compare, Allocator>

	template<typename Value>
	void
	Node<Value>::swapColor(Node<Value> *a, Node<Value> *b)
	{
		if (a != nullptr && b != nullptr)
			ft::swap(a->_color, b->_color);
		else if (a != nullptr)
			a->setColor(NodeColor_Black);
		else if (b != nullptr)
			b->setColor(NodeColor_Black);
	}

	template<typename Value>
	void
	Node<Value>::swapNodes(Node<Value> *n, Node<Value> *suc)
	{
		Plan	new_n(*suc);
		Plan	new_suc(*n);

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
	TREE::isDoubleRed(NodePointer const n)
	{
		return tree::getColor(n) == NodeColor_Red && tree::getColor(n->getParent()) == NodeColor_Red;
	}

	template<typename Key, typename T, typename Value, typename Compare, typename Allocator>
	typename TREE::NodePointer
	TREE::getChildByNear(NodePointer sib)
	{
		bool dbIsOnLeft = !sib->isOnLeft();
		if (dbIsOnLeft)
			return sib->getLeftChild();
		else
			return sib->getRightChild();
	}

	template<typename Key, typename T, typename Value, typename Compare, typename Allocator>
	typename TREE::NodePointer
	TREE::getChildByFar(NodePointer sib)
	{
		bool dbIsOnLeft = !sib->isOnLeft();
		if (dbIsOnLeft)
			return sib->getRightChild();
		else
			return sib->getLeftChild();
	}

	template<typename Key, typename T, typename Value, typename Compare, typename Allocator>
	typename TREE::NodePointer
	TREE::siblingOf(NodePointer const p, NodePointer const n) const
	{
		if (n == _root)
			return nullptr;
		if (p->getLeftChild() == n)
			return p->getRightChild();
		return p->getLeftChild();
	}

	template<typename Key, typename T, typename Value, typename Compare, typename Allocator>
	void
	TREE::transplant(NodePointer n, NodePointer as)
	{
		if (_root == n)
		{
			_end_ptr->setLeftChild(_root = as);
			return;
		}
		NodePointer p = n->getParent();
		if (p->getLeftChild() == n)
			p->setLeftChild(as);
		if (p->getRightChild() == n)
			p->setRightChild(as);
		n->setParent(nullptr);
	}

	template<typename Key, typename T, typename Value, typename Compare, typename Allocator>
	void
	TREE::leftRotate(NodePointer n)
	{
		NodePointer const p = n->getParent();
		NodePointer const x = n->getLeftChild();

		transplant(p, n);
		n->setLeftChild(p);
		p->setRightChild(x);
	}

	template<typename Key, typename T, typename Value, typename Compare, typename Allocator>
	void
	TREE::rightRotate(NodePointer n)
	{
		NodePointer const p = n->getParent();
		NodePointer const x = n->getRightChild();

		transplant(p, n);
		n->setRightChild(p);
		p->setLeftChild(x);
	}

	template<typename Key, typename T, typename Value, typename Compare, typename Allocator>
	typename TREE::NodePointer
	TREE::findNode(Key const& key) const
	{
		NodePointer	current = _root;

		while (current != nullptr)
		{
			if (_key_compare(current->getValue().first, key))
				current = current->getRightChild();
			else if (_key_compare(key, current->getValue().first))
				current = current->getLeftChild();
			else
				break;
		}
		return current;
	}

	template<typename Key, typename T, typename Value, typename Compare, typename Allocator>
	typename TREE::NodePointer&
	TREE::findPlace(NodePointer& place, Key const& key, NodePointer& parent)
	{
		NodePointer	current = place;
		NodePointer*	ret = &place;
		while (current != nullptr)
		{
			parent = current->getParent();
			if (_key_compare(current->getValue().first, key))
			{
				parent = current;
				NodePointer& rc = current->getRightChild();
				ret = &rc;
				current = rc;
			}
			else if (_key_compare(key, current->getValue().first))
			{
				parent = current;
				NodePointer& lc = current->getLeftChild();
				ret = &lc;
				current = lc;
			}
			else
				break;
		}
		return *ret;
	}

	template<typename Key, typename T, typename Value, typename Compare, typename Allocator>
	typename TREE::NodePointer&
	TREE::findPlaceWithHint(const_iterator hint, Key const& key, NodePointer& parent)
	{
		if (hint == end() || _key_compare(key, hint->first)) // key < hint
		{
			const_iterator prev = hint;
			if (prev == begin() || _key_compare((--prev)->first, key)) // --hint < key (*valid hint*)
			{
				if (hint.base() == _end_ptr)
					return _root;
				else if (hint.base()->getLeftChild() == nullptr)
					return (parent = hint.base())->getLeftChild();
				else
					return (parent = prev.base())->getRightChild();
			}
			return findPlace(_root, key, parent); // invalid hint
		}
		else if (_key_compare(hint->first, key)) // hint < key
		{
			const_iterator next = ++hint;
			if (next == end() || _key_compare(key, next->first)) // key < ++hint (*valid hint*)
			{
				if (hint.base()->getRightChild() == nullptr)
					return (parent = hint.base())->getRightChild();
				else
					return (parent = next.base())->getLeftChild();
			}
			return findPlace(_root, key, parent); // invalid hint
		}
		else // hint == key
		{
			parent = hint.base()->getParent();
			if (parent->getLeftChild() == hint.base())
				return parent->getLeftChild();
			else
				return parent->getRightChild();
		}
	}

	template<typename Key, typename T, typename Value, typename Compare, typename Allocator>
	bool
	TREE::insertNodeAt(NodePointer parent, NodePointer& place, const_reference value, bool overwrite)
	{
		if (place != nullptr)
		{
			if (overwrite)
				place->getValue().second = value.second;
			return false;
		}
		else
		{
			place = createNode(value, parent);
			tryFixDoubleRed(place);
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
	TREE::tryFixDoubleRed(NodePointer n)
	{
		if (n == nullptr)
			return;
		if (_root == n)
		{
			if (getColor(n) == NodeColor_Red)
				n->setColor(NodeColor_Black);
			return;
		}

		NodePointer p = n->getParent();
		NodePointer g = p->getParent();
		NodePointer u = siblingOf(g, p);

		if (p == _root || !isDoubleRed(n))
			return;
		if (getColor(u) == NodeColor_Red)
		{
			u->setColor(NodeColor_Black);
			p->setColor(NodeColor_Black);
			g->setColor(NodeColor_Red);
			tryFixDoubleRed(g);
		}
		if (!isDoubleRed(n))
			return;
		if (getColor(u) == NodeColor_Black)
		{
			NodePointer descendant_of_g = p;
			if (p->isOnLeft())
			{
				if (n->isOnRight())
					leftRotate(descendant_of_g = n);
				NodeType::swapColor(descendant_of_g, g);
				rightRotate(descendant_of_g);
			}
			else
			{
				if (n->isOnLeft())
					rightRotate(descendant_of_g = n);
				NodeType::swapColor(descendant_of_g, g);
				leftRotate(descendant_of_g);
			}
		}
	}

	template<typename Key, typename T, typename Value, typename Compare, typename Allocator>
	void
	TREE::destroyNode(NodePointer n)
	{
		if (n == nullptr)
			return;
		destroyNode(n->getLeftChild());
		destroyNode(n->getRightChild());
	}

	// https://medium.com/analytics-vidhya/deletion-in-red-black-rb-tree-92301e1474ea
	template<typename Key, typename T, typename Value, typename Compare, typename Allocator>
	void
	TREE::deleteNode(NodePointer n)
	{
		if (n->getChildCount() == 2)
		{
			NodePointer suc = n->getRightChild()->getMinimum();
			NodeType::swapNodes(n, suc);
			if (_root == n)
				_root = suc;
		}
		NodePointer c = n->getFirstChild();
		NodePointer p = n->getParent();
		transplant(n, c);
		if (getColor(n) == NodeColor_Black)
		{
			if (getColor(c) == NodeColor_Red)
				c->setColor(NodeColor_Black);
			else
				fixDoubleBlack(c, p);
		}
		if (!_key_compare(_begin_ptr->getValue().first, n->getValue().first))
			_begin_ptr = (_root ? _root->getMinimum() : _end_ptr);
		_node_allocator.deallocate(n, 1);
	}

	template<typename Key, typename T, typename Value, typename Compare, typename Allocator>
	void
	TREE::fixDoubleBlack(NodePointer db, NodePointer p)
	{
		if (db == _root) // reached root Node
		{
			if (db != nullptr)
				db->setColor(NodeColor_Black);
			return;
		}

		NodePointer s = siblingOf(p, db);
		if (getColor(s) == NodeColor_Red)
		{
			NodeType::swapColor(db, p);
			if (s->isOnLeft())
				rightRotate(s);
			else
				leftRotate(s);
			fixDoubleBlack(db, p);
			return;
		}

		NodePointer nearChild = getChildByNear(s);
		NodePointer farChild = getChildByFar(s);

		if (getColor(nearChild) == NodeColor_Black && getColor(farChild) == NodeColor_Black)
		{
			s->setColor(NodeColor_Red);
			if (getColor(p) == NodeColor_Red)
				p->setColor(NodeColor_Black);
			else
				fixDoubleBlack(p, p->getParent());
		}
		else if (getColor(farChild) == NodeColor_Black && getColor(nearChild) == NodeColor_Red)
		{
			NodeType::swapColor(nearChild, s);
			if (s->isOnRight())
				rightRotate(nearChild);
			else
				leftRotate(nearChild);
			fixDoubleBlack(db, p);
		}
		else if (getColor(farChild) == NodeColor_Red)
		{
			NodeType::swapColor(p, s);
			if (s->isOnRight())
				leftRotate(s);
			else
				rightRotate(s);
			if (getColor(db) == NodeColor_Red)
				db->setColor(NodeColor_Black);
			farChild->setColor(NodeColor_Black);
		}
	}

	template<typename Key, typename T, typename Value, typename Compare, typename Allocator>
	typename TREE::NodePointer
	TREE::createNode(const_reference value, NodePointer parent)
	{
		NodePointer ptr = _node_allocator.allocate(1);
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
		_begin_ptr = _end_ptr;
	}

	template<typename Key, typename T, typename Value, typename Compare, typename Allocator>
	ft::pair<typename TREE::iterator, bool>
	TREE::insert(const_reference value)
	{
		NodePointer	parent;
		NodePointer&	place = findPlace(_root, value.first, parent);
		bool			inserted = insertNodeAt(parent, place, value, true);

		return ft::make_pair<iterator, bool>(iterator(place), inserted);
	}

	template<typename Key, typename T, typename Value, typename Compare, typename Allocator>
	typename TREE::iterator
	TREE::insert(iterator hint, const_reference value)
	{
		NodePointer	parent;
		NodePointer&	place = findPlaceWithHint(hint, value.first, parent);

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

		NodePointer	place = findNode(key);
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
		NodePointer	place = findNode(key);

		if (place == nullptr)
			return end();
		return iterator(place);
	}

	template<typename Key, typename T, typename Value, typename Compare, typename Allocator>
	typename TREE::const_iterator
	TREE::find(Key const& key) const
	{
		NodePointer	place = findNode(key);

		if (place == nullptr)
			return end();
		return const_iterator(place);
	}

	template<typename Key, typename T, typename Value, typename Compare, typename Allocator>
	typename TREE::NodePointer
	TREE::upper_bound(Key const& key) const
	{
		NodePointer	ret = _end_ptr;
		NodePointer	n	= _root;

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
	typename TREE::NodePointer
	TREE::lower_bound(Key const& key) const
	{
		NodePointer	ret = _end_ptr;
		NodePointer	n	= _root;

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
	ft::pair<typename TREE::iterator, typename TREE::iterator>
	TREE::equal_range(Key const& key)
	{
		return ft::pair<iterator, iterator>(
			lower_bound(key), upper_bound(key)
		);
	}

	template<typename Key, typename T, typename Value, typename Compare, typename Allocator>
	ft::pair<typename TREE::const_iterator, typename TREE::const_iterator>
	TREE::equal_range(Key const& key) const
	{
		return ft::pair<const_iterator, const_iterator>(
			lower_bound(key), upper_bound(key)
		);
	}

	template<typename Key, typename T, typename Value, typename Compare, typename Allocator>
	T&
	TREE::operator[](Key const& key)
	{
		NodePointer	parent = _end_ptr;
		NodePointer&	place = findPlace(_root, key, parent);

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
