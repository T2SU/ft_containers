/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree_1.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 22:44:03 by smun              #+#    #+#             */
/*   Updated: 2022/01/18 15:04:49 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <memory>
#include <iostream>

namespace ft
{
	template<typename T, typename Compare = std::less<T> >
	class tree
	{
	public:
		class node
		{
		private:
			Compare	_comp;
			tree*	_tree;

			node();
			node(node const& o);
			node& operator=(node const& o);

			void	setLeftChild(node* x)
			{
				if ((_left = x))
					_left->_parent = this;
			}

			void	setRightChild(node* x)
			{
				if ((_right = x))
					_right->_parent = this;
			}

			void	transplant(node* x)
			{
				if (_parent == nullptr)
				{
					_tree->_root = x;
					x->_parent = nullptr;
					return;
				}
				if (_parent->_left == this)
					_parent->setLeftChild(x);
				else if (_parent->_right == this)
					_parent->setRightChild(x);
			}

			void print()
			{
				static int level = 0;

				for (int i = 0; i < level - 1; ++i)
					std::cout << '-';
				if (level == 0)
					std::cout << "*:";
				std::cout << _value << ' ';
				if (_black)
					std::cout << "(B)" << std::endl;
				else
					std::cout << "(R)" << std::endl;
				if (_left)
				{
					++level;
					std::cout << "L:";
					_left->print();
					--level;
				}
				if (_right)
				{
					++level;
					std::cout << "R:";
					_right->print();
					--level;
				}
			}

			node* find(T const& value)
			{
				// ?????? ??????

				if (_value == value)
					return this;
				if (_comp(value, _value) && _left)
					return _left->find(value);
				else if (_right)
					return _right->find(value);
				return nullptr;
			}

			node*	findMinimum()
			{
				if (_left == nullptr)
					return this;
				return _left->findMinimum();
			}

			node*	insert(T const& value)
			{
				if (value == _value)
					return nullptr;
				if (_comp(value, _value))
				{
					if (_left)
						return (_left->insert(value));
					else
						return (_left = new node(_tree, value, this));
				}
				else
				{
					if (_right)
						return (_right->insert(value));
					else
						return (_right = new node(_tree, value, this));
				}
			}

			bool	isDoubleRed()
			{
				node* p = _parent;
				if (p == nullptr)
					return false;
				return !isBlack() && !p->isBlack();
			}

			node*	getUncleNode()
			{
				node* p = _parent;
				if (p == nullptr)
					return nullptr;
				node* grandp = p->_parent;
				if (grandp == nullptr)
					return nullptr;
				if (grandp->_left == p)
					return grandp->_right;
				else
					return grandp->_left;
			}

			void	tryRecolouring()
			{
				if (isRootNode())
				{
					if (!isBlack())
						_black = true;
					return;
				}

				node* p = _parent;
				node* g = _parent->_parent;
				node* u = getUncleNode();

				if (g == nullptr || !isDoubleRed())
					return;
				if (u == nullptr || u->isBlack())
					return;

				u->_black = true;
				p->_black = true;
				g->_black = false;
				g->tryRecolouring();
				g->tryRestructuring();
			}

			void	tryRestructuring()
			{
				if (isRootNode())
					return;

				node* p = _parent;
				node* g = _parent->_parent;
				node* u = getUncleNode();

				if (g == nullptr || !isDoubleRed())
					return;
				if (u != nullptr && !u->isBlack())
					return;

				if (_comp(this->_value, g->_value))
				{
					node* greater = _comp(p->_value, this->_value) ? this : p;
					if (greater == this)
						this->leftRotate();
					greater->rightRotate();
					std::swap(greater->_black, g->_black);
				}
				else
				{
					node* lesser = _comp(p->_value, this->_value) ? p : this;
					if (lesser == this)
						this->rightRotate();
					lesser->leftRotate();
					std::swap(lesser->_black, g->_black);
				}
			}

		public:

			bool	isChild(node* node)
			{
				return _left == node || _right == node;
			}

			bool	isBlack()
			{
				return _black;
			}

			bool	isRootNode()
			{
				return _parent == nullptr;
			}

			void	leftRotate()
			{
				node *p = _parent;
				node *x = _left;

				p->transplant(this);
				this->setLeftChild(p);
				p->setRightChild(x);
			}

			void	rightRotate()
			{
				node *p = _parent;
				node *x = _right;

				p->transplant(this);
				this->setRightChild(p);
				p->setLeftChild(x);
			}

		public:
			T		_value;
			node*	_parent;
			node*	_left;
			node*	_right;
			bool	_black;

			virtual ~node() {}
			node(tree* tree, T const& value, node* parent)
				: _value(value)
				, _parent(parent)
				, _left(nullptr)
				, _right(nullptr)
				, _black(false)
				, _comp(Compare())
				, _tree(tree)
			{
				if (parent == nullptr)
					_black = true;
			}

			friend class tree;
		};

	private:
		node* _root;

		tree(tree const& o);
		tree& operator=(tree const& o);

	public:
		tree() : _root(nullptr) {}
		virtual ~tree() {}

		void	insert(T const& value)
		{
			if (_root)
			{
				node* inserted = _root->insert(value);
				if (inserted == nullptr) // already inserted
					return;
				inserted->tryRecolouring();
				inserted->tryRestructuring();
			}
			else
			{
				_root = new node(this, value, nullptr);
			}
		}

		void	print()
		{
			if (_root)
				_root->print();
		}

		node*	find(T const& value)
		{
			if (_root)
				return _root->find(value);
			return nullptr;
		}

		node*	erase(node* n)
		{
			if (n == nullptr)
				return nullptr;
			node* lchild = n->_left;
			node* rchild = n->_right;
			if (lchild != nullptr && rchild != nullptr)
			{

			}
			else if (lchild != nullptr || rchild != nullptr)
			{

			}
		}

		node*	erase(T const& value)
		{
			return erase(find(value));
		}
	};
}

int main()
{
	ft::tree<int> tree;
	std::cout << "hello tree" << std::endl;

	tree.insert(8);
	tree.insert(18);
	tree.insert(5);
	tree.insert(15);
	tree.insert(17);
	tree.insert(25);
	tree.insert(40);
	tree.insert(80);


	tree.print();

	return 0;
}
