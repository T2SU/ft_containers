/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zzzzzzzzzzz.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 17:36:20 by smun              #+#    #+#             */
/*   Updated: 2022/01/30 15:35:16 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma clang diagnostic push
#pragma ide diagnostic ignored "NotImplementedFunctions"
#pragma ide diagnostic ignored "modernize-use-equals-delete"
#pragma ide diagnostic ignored "modernize-use-equals-default"

#include <iostream>
#include <memory>
#include <string>
#include <utility>

namespace ft
{
	template<typename T, typename Compare = std::less<T> >
	class tree
	{
	private:
		enum { BLACK, RED, END_NODE };
		enum { ALL = -1, COLOR = 0x8, VALUE = 0x10 };

		class node
		{
		private:
			node& operator=(node const&);
			node(node const& o)
				: _value(T())
				, _parent(o._parent)
				, _left(o._left)
				, _right(o._right)
				, _color(o._color) {}

		public:
			T		_value;
			node*	_parent;
			node*	_left;
			node*	_right;
			int		_color;

			node(T const& value, node* parent, int color)
				: _value(value)
				, _parent(parent)
				, _left(nullptr)
				, _right(nullptr)
				, _color(color)
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
			bool	isEndNode() const		{ return _color == END_NODE; }

			node**	getPlace()
			{
				if (isOnLeft())
					return &(_parent->_left);
				else
					return &(_parent->_right);
			}

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
				if (flag & COLOR)
				{
					if (a != nullptr && b != nullptr)
						std::swap(a->_color, b->_color);
					else if (a != nullptr)
						a->setColor(BLACK);
					else if (b != nullptr)
						b->setColor(BLACK);
				}
			}

			static void	swapNodes(node* n, node* suc, node** rr)
			{
				node* new_p_parent = suc->_parent;
				node* new_p_left = suc->_left;
				node* new_p_right = suc->_right;
				node** new_p_link = rr;
				if (suc->_parent)
				    new_p_link = suc->_parent->_left == suc ? &suc->_parent->_left : &suc->_parent->_right;

				node* new_q_parent = n->_parent;
				node* new_q_left = n->_left;
				node* new_q_right = n->_right;
				node** new_q_link = rr;
				if (n->_parent)
				    new_q_link = n->_parent->_left == n ? &n->_parent->_left : &n->_parent->_right;

				if (suc->_parent == n)
			    {
				    new_p_parent = suc;
				    new_p_link = nullptr;
				    if (n->_left == suc)
				        new_q_left = n;
				    else
				        new_q_right = n;
			    }
				else if (n->_parent == suc)
			    {
				    new_q_parent = n;
				    new_q_link = nullptr;
				    if (suc->_left == n)
				        new_p_left = suc;
				    else
				        new_p_right = suc;
			    }

				n->_parent = new_p_parent;
				n->_left = new_p_left;
				if (n->_left)
				    n->_left->_parent = n;
				n->_right = new_p_right;
				if (n->_right)
				    n->_right->_parent = n;
				if (new_p_link)
				    *new_p_link = n;

				suc->_parent = new_q_parent;
				suc->_left = new_q_left;
				if (suc->_left)
				    suc->_left->_parent = suc;
				suc->_right = new_q_right;
				if (suc->_right)
				    suc->_right->_parent = suc;
				if (new_q_link)
				    *new_q_link = suc;

				std::swap(n->_color, suc->_color);
				/*node new_n = *suc;
				node** new_n_place = suc->getPlace();

				node new_suc = *n;
				node** new_suc_place = n->getPlace();

				if (suc->getParent() == n)
				{
					new_suc._parent = n;
					if (n->isOnLeft())
						new_n._left = suc;
					else
						new_n._right = suc;
					new_suc_place = nullptr;
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
					*new_suc_place = suc;*/
			}
		};

		node*	_end;
		node*	_root;
		Compare	_comp;

		tree& operator=(tree const&);
		tree(tree const&);

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

		static int	getColor(node const* n)
		{
			if (n == nullptr)
				return BLACK;
			return n->getColor();
		}

		node*	siblingOf(node* const p, node* const n) const
		{
			if (n == _root)
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
				_end->setLeftChild(_root = as);
				return;
			}
			node* p = n->getParent();
			if (p->getLeftChild() == n)
				p->setLeftChild(as);
			if (p->getRightChild() == n)
				p->setRightChild(as);
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
					return (n->setLeftChild(new node(value, n, RED)));
			}
			else
			{
				node* const right = n->getRightChild();

				if (right != nullptr)
					return (insert(right, value));
				else
					return (n->setRightChild(new node(value, n, RED)));
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
				// x, p, g??? ??????????????? ??????.
				// ????????? ????????? ????????????, x??? g??? ?????????????????? ??????.
				// ?????? p?????? x??? g????????? ????????? ??? ??????.
				node* child_of_g = p;
				if (p->isOnLeft())
				{
					if (n->isOnRight())
						leftRotate(child_of_g = n);
					node::swap(child_of_g, g, COLOR);
					rightRotate(child_of_g);
				}
				else
				{
					if (n->isOnLeft())
						rightRotate(child_of_g = n);
					node::swap(child_of_g, g, COLOR);
					leftRotate(child_of_g);
				}
			}
		}

		// https://medium.com/analytics-vidhya/deletion-in-red-black-rb-tree-92301e1474ea
		void	erase(node* n)
		{
			if (n->getChildCount() == 2)
			{
				node* suc = n->getRightChild()->getMinimum();

				//node::swap(n, suc, VALUE);
				//n = suc;

				node::swapNodes(n, suc, &_root);
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
			// case 2. (ROOT??? ????????????, BLACK?????? ???????????? ??????.)
			if (db == _root)
			{
				db->setColor(BLACK);
				return;
			}

			node* s = siblingOf(p, db);
			// ?????? ?????? ????????? ????????? s??? ?????? ?????? ??????.

			// case 4. ????????? RED??? ??????,
			//         db???????????? ????????? ????????? ?????? RED??? ?????????, ?????? ????????? ?????? ??????.
			//         ????????? ????????? db??? ????????????. fixDoubleBlack ?????? ??????.
			if (getColor(s) == RED)
			{
				node::swap(db, p, COLOR);
				if (s->isOnLeft())
					rightRotate(s);
				else
					leftRotate(s);
				fixDoubleBlack(db, p);
				return;
			}

			node* nearChild = getChildByNear(s);
			node* farChild = getChildByFar(s);

			// case 3. ????????? ????????? ????????? ?????? BLACK??? ??????, ???????????? RED??? ?????? ????????? ???????????????.
			//         ????????? RED??? ????????????, ?????? p??? BLACK??????.
			if (getColor(nearChild) == BLACK && getColor(farChild) == BLACK)
			{

				s->setColor(RED);
				if (getColor(p) == RED)
					p->setColor(BLACK);

				// p??? ?????? BLACK????????????, p??? ?????? ?????? ????????? ???.
				// p??? ????????? fixDoubleBlack ??????.
				else
					fixDoubleBlack(p, p->getParent());
			}

			// case 5. (s??? s??? db??? nearChild??? ????????? ???, nearChild??? db??? ??????????????? ??????.)
			//          1. s??? ???????????? ?????? ??????.
			//             --> db??? ????????? ?????? s??? ?????? ??????.
			//             --> s??? p??? ????????? ??????????????????, ?????????.
			//          2. s??? ????????? ?????? ??????.
			//             --> db??? ????????? ?????? s??? ????????? ??????.
			//             --> s??? p??? ???????????? ??????????????????, ?????????.)
			else if (getColor(farChild) == BLACK && getColor(nearChild) == RED)
			{
				node::swap(nearChild, s, COLOR);
				if (s->isOnRight())
					rightRotate(nearChild);
				else
					leftRotate(nearChild);

				// ??? ??????????????? db??? ?????? ?????? ???????????????, ????????? ?????? ??????.

				// p?????? RED??? ??? ???????????? db??? ??? ????????? ???????????????,
				// p??? s??? ?????? ????????? ???.
				// ????????? ???????????? ?????? ????????? case 6??? ?????????.
				fixDoubleBlack(db, p);
			}

			// case 6. (s??? db??? ?????? farChild??? RED)
			//   --> s??? BLACK??? ???, farChild??? ????????? ?????? BLACK.
			//       ???????????? ????????? ?????? nearChild??? ?????? ????????? BLACK.
			//   ?????????, p??? s??? ???????????????, s??? db????????? ???????????? ????????? ??????.
			//   ?????? farChild, db?????? ?????? BLACK?????? ?????????, db??? ?????? ???????????? BLACK?????? ????????? ??????.
			else if (getColor(farChild) == RED)
			{
				node::swap(p, s, COLOR);
				if (s->isOnRight())
					leftRotate(s);
				else
					rightRotate(s);
				if (getColor(db) == RED)
					db->setColor(BLACK);
				farChild->setColor(BLACK);
			}
		}

	public:
		tree()
			: _root(nullptr)
			, _end(new node(T(), nullptr, END_NODE))
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
				_end->setLeftChild(_root = new node(value, _end, BLACK));
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
	ft::tree<const int> tree;

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
