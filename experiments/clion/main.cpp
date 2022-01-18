/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree_1.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 22:44:03 by smun              #+#    #+#             */
/*   Updated: 2022/01/18 21:50:06 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <memory>
#include <iostream>
#include <string>

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

			static bool	isBlack(node* x)
			{
				return x == nullptr || x->_black;
			}

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

			bool	isOnLeft()
			{
				return _parent->_left == this;
			}

			bool	isOnRight()
			{
				return _parent->_right == this;
			}

			void	transplant(node* x)
			{
				if (_parent == nullptr)
				{
					_tree->_root = x;
					x->_parent = nullptr;
					return;
				}
				if (isOnLeft())
					_parent->setLeftChild(x);
				else if (isOnRight())
					_parent->setRightChild(x);
			}

			void	replace(node* x)
			{
				transplant(x);
				if (_left != nullptr)
					x->setLeftChild(_left);
				if (_right != nullptr)
					x->setRightChild(_right);
			}

			void print(std::string indent, bool last)
			{
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
				std::string color = isBlack(this) ? "BLACK" : "RED";
				std::cout << _value << "(" << color << ")" << std::endl;
				if (_left)
					_left->print(indent, false);
				if (_right)
					_right->print(indent, true);
			}

			node* find(T const& value)
			{
				// 중위 탐색

				if (_value == value)
					return this;
				if (_comp(value, _value) && _left)
					return _left->find(value);
				else if (_right)
					return _right->find(value);
				return nullptr;
			}

			static node*	minimum(node* n)
			{
				if (n->_left == nullptr)
					return n;
				return minimum(n->_left);
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
				return !isBlack(this) && !isBlack(p);
			}

			node*	getUncleNode()
			{
				node* p = _parent;
				if (p == nullptr)
					return nullptr;
				return p->getSiblingNode();
			}

			node*	getSiblingNode() // Right
			{
				node* p = _parent;
				if (p == nullptr)
					return nullptr;
				if (isOnLeft())
					return p->_right;
				return p->_left;
			}

			node*	getFirstChild()
			{
				if (_left != nullptr)
					return _left;
				return _right;
			}

			void	tryFixDoubleRed()
			{
				if (isRootNode())
				{
					if (!isBlack(this))
						setBlack(true);
					return;
				}

				node* p = _parent;
				node* g = _parent->_parent;
				node* u = getUncleNode();

				if (g == nullptr || !isDoubleRed())
					return;
				if (u != nullptr && !isBlack(u))
				{
					u->setBlack(true);
					p->setBlack(true);
					g->setBlack(false);
					g->tryFixDoubleRed();
				}
				if (g == nullptr || !isDoubleRed())
					return;
				if (u == nullptr || isBlack(u))
				{
					if (_comp(this->_value, g->_value))
						// x, p, g | p, x, g
					{
						node* greater = _comp(p->_value, this->_value) ? this : p;
						if (greater == this)
							this->leftRotate();
						greater->rightRotate();
						std::swap(greater->_black, g->_black);
					}
					else
						// g, x, p | g, p, x
					{
						node* lesser = _comp(p->_value, this->_value) ? p : this;
						if (lesser == this)
							this->rightRotate();
						lesser->leftRotate();
						std::swap(lesser->_black, g->_black);
					}
				}
			}

		public:

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
				if (isRootNode())
					_black = true;
			}

			void	setBlack(bool black)
			{
				_black = black;
			}

			friend class tree;
		};

	private:
		node* _root;

		tree(tree const& o);
		tree& operator=(tree const& o);

		void	deleteNode(node* z)
		{
			node* x;
			node* y = z;
			bool y_original_color = y->_black;
			if (z->_left == nullptr)
			{
				x = z->_right;
				z->transplant(z->_right);
			}
			else if (z->_right == nullptr)
			{
				x = z->_left;
				z->transplant(z->_left);
			}
			else
			{
				y = node::minimum(z->_right);
				y_original_color = y->_black;
				x = y->_right;
				if (y->_parent == z)
				{
					if (x != nullptr)
						x->_parent = y;
				}
				else
				{
					y->transplant(y->_right);
					y->setRightChild(z->_right);
				}
				z->transplant(y);
				y->setLeftChild(z->_left);
				y->_black = z->_black;
			}
			delete z;
			if (y_original_color)
				deleteFix(x);
		}

		void deleteFix(node *x)
		{
			node *s;
			while (x != _root && x->_black)
			{
				if (x == x->_parent->_left)
				{
					s = x->_parent->_right;
					if (!s->_black)
					{
						s->_black = true;
						x->_parent->_black = false;
						x->_parent->leftRotate();
						s = x->_parent->_right;
					}

					if (s->_left->_black && s->_right->_black)
					{
						s->_black = false;
						x = x->_parent;
					}
					else
					{
						if (s->_right->_black)
						{
							s->_left->_black = true;
							s->_black = false;
							s->rightRotate();
							s = x->_parent->_right;
						}

						s->_black = x->_parent->_black;
						x->_parent->_black = true;
						s->_right->_black = true;
						x->_parent->leftRotate();
						x = _root;
					}
				}
				else
				{
					s = x->_parent->_left;
					if (!s->_black)
					{
						s->_black = true;
						x->_parent->_black = false;
						x->_parent->rightRotate();
						s = x->_parent->_left;
					}

					if (s->_right->_black && s->_right->_black)
					{
						s->_black = false;
						x = x->_parent;
					}
					else
					{
						if (s->_left->_black)
						{
							s->_right->_black = true;
							s->_black = false;
							s->leftRotate();
							s = x->_parent->_left;
						}

						s->_black = x->_parent->_black;
						x->_parent->_black = true;
						s->_left->_black = true;
						x->_parent->rightRotate();
						x = _root;
					}
				}
			}
			x->_black = true;
		}

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
				inserted->tryFixDoubleRed();
			}
			else
			{
				_root = new node(this, value, nullptr);
			}
		}

		void	print()
		{
			if (_root)
				_root->print("", true);
		}

		node*	find(T const& value)
		{
			if (_root)
				return _root->find(value);
			return nullptr;
		}

		void	erase(T const& value)
		{
			deleteNode(find(value));
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

	tree.erase(8);
	//tree.erase(17);


	tree.print();

	return 0;
}
