#pragma clang diagnostic push
#pragma ide diagnostic ignored "NotImplementedFunctions"
#pragma ide diagnostic ignored "modernize-use-equals-delete"
#pragma ide diagnostic ignored "modernize-use-equals-default"

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42se/*   Updated: 2022/01/21 11:39:35 by smun             ###   ########.fr       */                   +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 16:20:46 by smun              #+#    #+#             */
/*   Updated: 2022/01/20 17:22:40 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		enum { BLACK, RED };
		enum { ALL = -1, COLOR = 0x8, VALUE = 0x10 };

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
				if (flag & COLOR)
				{
					if (a != nullptr && b != nullptr)
						std::swap(a->_color, b->_color);
					else if (a != nullptr)
						a->setColor(BLACK);
					else if (b != nullptr)
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
				// x, p, g가 직선형태가 되게.
				// 중간이 굽어진 형태라면, x를 g의 반대방향으로 회전.
				// 이후 p또는 x를 g쪽으로 색교체 후 회전.
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

			// case 4. 형제가 RED일 경우,
			//         db방향으로 색교체 회전을 해서 RED도 넘기고, 노드 개수도 하나 옮김.
			//         그러나 여전히 db는 이중블랙. fixDoubleBlack 다시 호출.
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

			// case 3. 형제와 형제의 자식이 모두 BLACK일 경우, 형제쪽에 RED를 넣어 균형을 맞추어야함.
			//         형제를 RED로 설정하고, 대신 p는 BLACK으로.
			if (getColor(nearChild) == BLACK && getColor(farChild) == BLACK)
			{

				s->setColor(RED);
				if (getColor(p) == RED)
					p->setColor(BLACK);

				// p가 원래 BLACK이었다면, p가 이중 블랙 상태가 됨.
				// p에 대해서 fixDoubleBlack 호출.
				else
					fixDoubleBlack(p, p->getParent());
			}

			// case 5. (s와 s의 db와 nearChild를 색교체 후, nearChild를 db와 반대쪽으로 회전.)
			//          1. s가 오른쪽에 있을 경우.
			//             --> db와 가까운 쪽은 s의 왼쪽 자식.
			//             --> s는 p의 왼쪽에 달려있으므로, 우회전.
			//          2. s가 왼쪽에 있을 경우.
			//             --> db와 가까운 쪽은 s의 오른쪽 자식.
			//             --> s는 p의 오른쪽에 달려있으므로, 좌회전.)
			else if (getColor(farChild) == BLACK && getColor(nearChild) == RED)
			{
				node::swap(nearChild, s, COLOR);
				if (s->isOnRight())
					rightRotate(nearChild);
				else
					leftRotate(nearChild);

				// 이 상태에서는 db가 이중 블랙 상태이므로, 균형이 맞지 않음.

				// p색이 RED가 된 상태에서 db와 먼 쪽으로 회전되므로,
				// p는 s의 먼쪽 자식이 됨.
				// 따라서 자연스레 아래 함수는 case 6을 처리함.
				fixDoubleBlack(db, p);
			}

			// case 6. (s의 db에 대한 farChild가 RED)
			//   --> s는 BLACK일 것, farChild의 자식은 모두 BLACK.
			//       이진트리 속성에 의해 nearChild의 색은 무조건 BLACK.
			//   따라서, p와 s를 색교환하고, s를 db쪽으로 회전해서 균형을 맞춤.
			//   이후 farChild, db색을 모두 BLACK으로 칠하면, db의 색에 관계없이 BLACK노드 개수가 균형.
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
