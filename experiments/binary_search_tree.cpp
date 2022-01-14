/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_search_tree.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 22:44:03 by smun              #+#    #+#             */
/*   Updated: 2022/01/14 15:32:23 by smun             ###   ########.fr       */
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
			Compare _comp;

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
				if (_parent->_left == this)
					_parent->setLeftChild(x);
				else if (_parent->_right == this)
					_parent->setRightChild(x);
			}

			void print()
			{
				static int level = 0;

				for (int i = 0; i < level; ++i)
					std::cout << ' ';
				std::cout << _value << std::endl;
				++level;
				if (_left)
				{
					std::cout << "L:";
					_left->print();
					--level;
				}
				if (_right)
				{
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

			node*	find_minimum()
			{
				if (_left == nullptr)
					return this;
				return _left->find_minimum();
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
						return (_left = new node(value, this));
				}
				else
				{
					if (_right)
						return (_right->insert(value));
					else
						return (_right = new node(value, this));
				}
			}

			bool	isChild(node* node)
			{
				return _left == node || _right == node;
			}

			void	leftRotate()
			{
				node *p = _parent;
				node *x = _left;

				p->transplant(this);
				this->setLeftChild(x);
				x->setRightChild(p);
			}

			void	rightRotate()
			{
				node *p = _parent;
				node *x = _right;

				p->transplant(this);
				this->setRightChild(x);
				x->setLeftChild(p);
			}

		public:
			T _value;
			node* _parent;
			node* _left;
			node* _right;

			virtual ~node() {}
			node(T const& value, node* parent)
				: _value(value)
				, _parent(parent)
				, _left(nullptr)
				, _right(nullptr)
				, _comp(Compare())
			{}

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
				_root->insert(value);
			else
				_root = new node(value, nullptr);
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
	};
}

int main()
{
	ft::tree<int> tree;
	std::cout << "hello tree" << std::endl;
	tree.insert(7);
	tree.insert(4);
	tree.insert(3);
	tree.insert(6);
	tree.insert(2);
	tree.insert(11);
	tree.insert(9);
	tree.insert(18);
	tree.insert(14);
	tree.insert(12);
	tree.insert(17);
	tree.insert(19);
	tree.insert(22);
	tree.print();

	std::cout << std::endl;
	std::cout << std::endl;

	ft::tree<int>::node* n = tree.find(11);
	std::cout << n->_value << std::endl;

	return 0;
}
