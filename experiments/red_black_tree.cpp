/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 17:14:00 by smun              #+#    #+#             */
/*   Updated: 2022/01/08 19:05:13 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <memory>
#include <iostream>

/*
** 1. 루트 노트의 색깔은 Black 이다.
** 2. 모든 External 노드들은 Black 이다.
** 3. 빨강 Node 의 자식은 Black 이다. (= No Double Red. 빨강이 연속일 수 없음.)
** 4. 모든 리프 노드에서 Black Depth는 같다. (= 리프노드에서 루트노드까지 가는 경로에서 만나는 블랙노드의 개수는 같다.)
*/

namespace ft
{
	int _level = 0;

	template<typename T, typename Compare>
	struct node
	{
		Compare _compare = Compare();
		T _value;
		node* _parent;
		node* _left;
		node* _right;
		bool _black;
		node(bool black,
			T const& value,
			node* parent = nullptr,
			node* left = nullptr,
			node* right = nullptr)
			: _parent(parent)
			, _left(left)
			, _right(right)
			, _black(black)
			, _value(value)
		{}

		void print()
		{
			for (int i = 0; i < _level; ++i)
				std::cout < ' ';
			std::cout << _value;
			++_level;
			if (_left)
			{
				_left->print();
				--_level;
			}
			if (_right)
			{
				_right->print();
				--_level;
			}
		}

		node<T>*	find(T const& value)
		{
			// 중위 탐색

			if (_value == value)
				return this;
			if (_compare(value, _value) && _left)
				return _left->find(value);
			else if (_right)
				return _right->find(value);
			return nullptr;
		}

		node<T, Compare>*	insert(T const& value)
		{
			// 이진 탐색 트리 insert

			if (value == _value)
				return nullptr;
			if (_compare(value, _value))
			{
				if (_left)
					return (_left->insert(value));
				else
					return (_left = new node<T, Compare>(false, value, this));
			}
			else
			{
				if (_right)
					return (_right->insert(value));
				else
					return (_right = new node<T, Compare>(false, value, this));
			}
		}
	};

	// https://zeddios.tistory.com/237

	template<typename T, typename Compare = std::less<T> >
	class tree
	{
	private:
		typedef Compare compare_type;
		node<T, Compare>* root;

		tree(tree const& o);
		tree& operator=(tree const& o);

		node<T, Compare>*	find(T const& value)
		{
			if (root)
				return root->find(value);
			return nullptr;
		}

	public:
		tree() : root(nullptr) {}
		virtual ~tree() {}

		void	insert(T const& value)
		{
			node<T, Compare>* inserted;
			if (root == nullptr)
				inserted = (root = new node<T, Compare>(true, value));
			else
				inserted = root->insert(value);

			if (inserted == nullptr) // 이미 해당 요소가 있는 경우
				return;

			// 이진 탐색 트리
			// 연결리스트
			// Restructuring / Recoloring
		}

		bool	erase(T const& value)
		{
			// 삭제 후 Restructuring / Recoloring?
			node<T, Compare>* elem = find(value);
			if (elem == nullptr)
				return false;
			// 어떻게..?
		}

		void	print()
		{
			// 중위 순회
			if (root)
				root->print();
		}

		// w가 black이라면 restructuring
		// -> z(나), v(부모), 부모의 부모.
		//    1. 셋을 오름차순 정렬.
		//    2. 가운데에 있는게 부모가 됨. (부모로 올라간걸 black)
		//    3. 왼쪽은 작은거, 오른쪽은 큰거. (자식은 red행)
		//    4. 원래 자식이었던건 같이 딸려감.

		// w가 red라면 recoloring
		//    1. v(부모), w(부모의 형제)를 black으로.
		//    2. z(나)와 부모의 부모는 red로.

		// -> 부모의 부모의 부모가 존재하고, 그것이 red일 경우
		//    1. 부모의 부모를 다시 recoloring 또는 restructing.


	};
}

int main()
{
	ft::tree<int> t;

	return 0;
}
