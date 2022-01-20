#pragma clang diagnostic push
#pragma ide diagnostic ignored "NotImplementedFunctions"
#pragma ide diagnostic ignored "modernize-use-equals-delete"
#pragma ide diagnostic ignored "modernize-use-equals-default"

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 16:20:46 by smun              #+#    #+#             */
/*   Updated: 2022/01/20 17:22:40 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <memory>
#include <string>

namespace ft
{
	template<typename T, typename Compare = std::less<T> >
	class tree
	{
	private:
		enum { BLACK, RED };
		enum { ALL = -1, PARENT = 0x1, LEFT_CHILD = 0x2, RIGHT_CHILD = 0x4, COLOR = 0x8, VALUE = 0x10 };

		class node
		{
		private:
			T		_value;
			node*	_parent;
			node*	_left;
			node*	_right;
			int		_color;

			node& operator=(node const&);
			node(node const&);
			node();

		public:
			node(T const& value, node* parent)
				: _value(value)
				, _parent(parent)
				, _left(nullptr)
				, _right(nullptr)
				, _color(RED)
				{}
			virtual ~node()
			{
			}

			int		getColor() const		{ return _color; }
			void	setColor(int color)		{ _color = color; }
			T		getValue() const		{ return _value; }
			node*	getParent() const		{ return _parent; }
			void	setParent(node* p)		{ _parent = p; }
			node*	getLeftChild() const	{ return _left; }
			node*	getRightChild() const	{ return _right; }
			bool	isOnLeft() const		{ return _parent->_left == this; }
			bool	isOnRight() const		{ return _parent->_right == this; }
			int		getChildCount() const	{ return (_left != nullptr) + (_right != nullptr); }
			node*	getFirstChild() const	{ return _left != nullptr ? _left : _right; }

			node*	setLeftChild(node* const x)
			{
				if ((_left = x))
					_left->setParent(this);
				return x;
			}

			node*	setRightChild(node* const x)
			{
				if ((_right = x))
					_right->setParent(this);
				return x;
			}

			node*	getMinimum()
			{
				if (_left == nullptr)
					return this;
				return _left->getMinimum();
			}

			node*	find(Compare const& comp, T const& value)
			{
				if (_value == value)
					return this;
				if (comp(value, _value))
				{
					if (_left == nullptr)
						return nullptr;
					return _left->find(comp, value);
				}
				else
				{
					if (_right == nullptr)
						return nullptr;
					return _right->find(comp, value);
				}
			}

			static void	swap(node* a, node* b, int flag)
			{
				if (flag & PARENT)
					std::swap(a->_parent, b->_parent);
				if (flag & LEFT_CHILD)
					std::swap(a->_left, b->_left);
				if (flag & RIGHT_CHILD)
					std::swap(a->_right, b->_right);
				if (flag & COLOR)
				{
					if (a != nullptr && b != nullptr)
						std::swap(a->_color, b->_color);
					else if (a != nullptr && b == nullptr)
						a->setColor(BLACK);
					else if (a == nullptr && b != nullptr)
						b->setColor(BLACK);
				}
				if (flag & VALUE)
					std::swap(a->_value, b->_value);
			}
		};

		node*	_root;
		Compare	_comp;

		tree& operator=(tree const&);
		tree(tree const&);

		static int	getColor(node const* n)
		{
			if (n == nullptr)
				return BLACK;
			return n->getColor();
		}

		static void	print(node const* n, std::string indent, bool last)
		{
			if (n == nullptr)
				return;

			std::cout << indent;
			if (last)
			{
				std::cout << "R----";
				indent += "   ";
			}
			else
			{
				std::cout << "L----";
				indent += "|  ";
			}
			std::string color = getColor(n) == RED ? "RED" : "BLACK";
			std::cout << n->getValue() << "(" << color << ")" << std::endl;
			print(n->getLeftChild(), indent, false);
			print(n->getRightChild(), indent, true);
		}

		static node*	siblingOf(node* const p, node* const n)
		{
			if (p == nullptr)
				return nullptr;
			if (p->getLeftChild() == n)
				return p->getRightChild();
			return p->getLeftChild();
		}

		static node*	getChildByNear(node *sib)
		{
			bool dbIsOnLeft = !sib->isOnLeft();
			if (dbIsOnLeft)
				return sib->getLeftChild();
			else
				return sib->getRightChild();
		}

		static node*	getChildByFar(node *sib)
		{
			bool dbIsOnLeft = !sib->isOnLeft();
			if (dbIsOnLeft)
				return sib->getRightChild();
			else
				return sib->getLeftChild();
		}

		static bool		isDoubleRed(node* const n)
		{
			return getColor(n) == RED && getColor(n->getParent()) == RED;
		}

		void	transplant(node* n, node* as)
		{
			if (_root == n)
			{
				(_root = as)->setParent(nullptr);
				return;
			}
			node* p = n->getParent();
			if (p->getLeftChild() == n)
				p->setLeftChild(as);
			if (p->getRightChild() == n)
				p->setRightChild(as);
			n->setParent(nullptr);
		}

		void	replace(node* n, node* as)
		{
			node* const left = n->getLeftChild();
			node* const right = n->getLeftChild();

			transplant(n, as);
			if (left != nullptr)
				as->setLeftChild(left);
			if (right != nullptr)
				as->setRightChild(right);
		}

		void	leftRotate(node* n)
		{
			node* const p = n->getParent();
			node* const x = n->getLeftChild();

			transplant(p, n);
			n->setLeftChild(p);
			p->setRightChild(x);
		}

		void	rightRotate(node* n)
		{
			node* const p = n->getParent();
			node* const x = n->getRightChild();

			transplant(p, n);
			n->setRightChild(p);
			p->setLeftChild(x);
		}

		node*	insert(node* n, T const& value)
		{
			if (n == nullptr)
				return nullptr;

			T const val = n->getValue();

			if (val == value)
				return nullptr;
			if (_comp(value, val))
			{
				node* const left = n->getLeftChild();

				if (left != nullptr)
					return (insert(left, value));
				else
					return (n->setLeftChild(new node(value, n)));
			}
			else
			{
				node* const right = n->getRightChild();

				if (right != nullptr)
					return (insert(right, value));
				else
					return (n->setRightChild(new node(value, n)));
			}
		}

		void	tryFixDoubleRed(node* n)
		{
			if (n == nullptr)
				return;
			if (_root == n)
			{
				if (getColor(n) == RED)
					n->setColor(BLACK);
				return;
			}

			node* p = n->getParent();
			node* g = p->getParent();
			node* u = siblingOf(g, p);

			if (g == nullptr || !isDoubleRed(n))
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
				T const val_n = n->getValue();
				T const val_g = g->getValue();
				T const val_p = p->getValue();

				if (_comp(val_n, val_g))
					// x, p, g | p, x, g
				{
					node* greater = _comp(val_p, val_n) ? n : p;
					if (greater == n)
						leftRotate(n);
					rightRotate(greater);
					node::swap(greater, g, COLOR);
				}
				else
					// g, x, p | g, p, x
				{
					node* lesser = _comp(val_p, val_n) ? p : n;
					if (lesser == n)
						rightRotate(n);
					leftRotate(lesser);
					node::swap(lesser, g, COLOR);
				}
			}
		}

		// https://medium.com/analytics-vidhya/deletion-in-red-black-rb-tree-92301e1474ea
		void	erase(node* n)
		{
			if (n->getChildCount() == 2)
			{
				node* suc = n->getRightChild()->getMinimum();
				node::swap(n, suc, VALUE);
				n = suc;
			}
			node* c = n->getFirstChild();
			node* p = n->getParent();
			transplant(n, c);
			if (getColor(n) == BLACK)
			{
				if (getColor(c) == RED)
					c->setColor(BLACK);
				else
					fixDoubleBlack(c, p);
			}
			delete n;
		}

		void	fixDoubleBlack(node* db, node* p)
		{
			// case 2. (ROOT에 도달하면, BLACK으로 설정하고 종료.)
			if (p == nullptr)
			{
				db->setColor(BLACK);
				return;
			}

			node* s = siblingOf(p, db);
			// 이진 트리 속성에 의해서 s가 없을 수는 없음.

			// case 3. (s쪽의 BLACK을 하나 줄여서 균형을 맞추기.
			//          p가 블랙이라서 균형 안맞으면 이중블랙 다시 수정.)
			if (getColor(s) == BLACK
				&& getColor(s->getLeftChild()) == BLACK
				&& getColor(s->getRightChild()) == BLACK)
			{
				s->setColor(RED);
				if (getColor(p) == RED) // s와 p의 순서를 맞바꾸는것만으로 문제를 해결할 수 있을 때.
					p->setColor(BLACK);
				else
					fixDoubleBlack(p, p->getParent());
			}

			// case 5.
			else if (getColor(s) == BLACK
					&& getColor(getChildByFar(s)) == BLACK
					&& getColor(getChildByNear(s)) == RED)
			{
				node* nearChild = getChildByNear(s);
				node::swap(nearChild, s, COLOR);
				if (s->isOnRight())
					rightRotate(nearChild);
				else
					leftRotate(nearChild);
				fixDoubleBlack(db, p); // apply case 6
			}

			// case 6.
			else if (getColor(s) == BLACK
					&& getColor(getChildByFar(s)) == RED)
			{
				node* farChild = getChildByFar(s);
				node::swap(p, s, COLOR);
				if (s->isOnRight())
					leftRotate(s);
				else
					rightRotate(s);
				if (getColor(db) == RED)
					db->setColor(BLACK);
				farChild->setColor(BLACK);
			}

			// case 4.
			else if (getColor(s) == RED)
			{
				node::swap(db, p, COLOR);
				if (s->isOnLeft())
					rightRotate(s);
				else
					leftRotate(s);
				fixDoubleBlack(db, p);
			}
		}

	public:
		tree()
			: _root(nullptr)
			, _comp(Compare()) {}
		virtual ~tree() {}

		void	print() const
		{
			print(_root, "", true);
		}

		void	insert(T const& value)
		{
			if (_root == nullptr)
			{
				_root = new node(value, nullptr);
				return;
			}
			tryFixDoubleRed(insert(_root, value));
		}

		void	erase(T const& value)
		{
			if (_root == nullptr)
				return;
			erase(_root->find(_comp, value));
		}
	};
}

int main()
{
	ft::tree<int> tree;

	tree.insert(8);
	tree.insert(18);
	tree.insert(5);
	tree.insert(15);
	tree.insert(17);
	tree.insert(25);
	tree.insert(40);
	tree.insert(80);
	tree.print();

	tree.erase(8);
	tree.print();

	tree.erase(17);
	tree.print();

	tree.erase(5);
	tree.print();

	tree.erase(15);
	tree.print();

	tree.erase(40);
	tree.print();

	return 0;
}

#pragma clang diagnostic pop
