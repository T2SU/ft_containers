/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree_1.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 22:44:03 by smun              #+#    #+#             */
/*   Updated: 2022/01/18 15:23:13 by smun             ###   ########.fr       */
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

			void	replace(node* x)
			{
				transplant(x);
				if (_left != nullptr)
					x->setLeftChild(_left);
				if (_right != nullptr)
					x->setRightChild(_right);
			}

			void print()
			{
				static int level = 0;

				for (int i = 0; i < level; ++i)
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
				// 중위 탐색

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
				return p->getSiblingNode();
			}

			node*	getSiblingNode() // Right
			{
				node* p = _parent;
				if (p == nullptr)
					return nullptr;
				if (p->_left == this)
					return p->_right;
				return p->_left;
			}

			node*	getFirstChild()
			{
				if (_left != nullptr)
					return _left;
				return _right;
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
				if (isRootNode())
					_black = true;
			}

			friend class tree;
		};

	private:
		node* _root;

		tree(tree const& o);
		tree& operator=(tree const& o);

		node*	deleteAsStandardBST(node* n)
		{
			if (n == nullptr)
				return nullptr;
			node* leftChild = n->_left;
			node* rightChild = n->_right;
			node* successor;
			if (leftChild != nullptr && rightChild != nullptr)
			{
				// 1. 계승자 찾기 (삭제할 노드의 오른쪽 서브트리에서, 가장 작은 요소 노드 찾기)
				successor = rightChild->findMinimum();
				// 2. 계승자의 자식을 계승자의 부모에 연결. (계승자 고립)
				successor->transplant(successor->getFirstChild());
				// 3. 계승자를 삭제할 노드의 위치로. (삭제할 노드 고립)
				n->replace(successor);
			}
			else if (leftChild != nullptr || rightChild != nullptr)
			{
				if (leftChild != nullptr)
					n->transplant((successor = leftChild));
				else
					n->transplant((successor = rightChild));
			}
			else
				n->transplant((successor = nullptr));
			delete n;
			return successor;
		}

		void	deleteNode(node* x)
		{
			deleteAsStandardBST(x);
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
	tree.erase(8);
	tree.erase(17);


	tree.print();

	return 0;
}
