/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 17:14:00 by smun              #+#    #+#             */
/*   Updated: 2022/01/11 14:21:38 by smun             ###   ########.fr       */
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

	private:
		node* getUncleNode()
		{
			if (_parent == nullptr)
				return nullptr;
			if (_parent->_parent == nullptr)
				return nullptr;
			if (_parent->_left == _parent)
				return _parent->_right;
			else
				return _parent->_left;
		}

		void setLeftChild(node* target)
		{
			target->_parent = this;
			_left = target;
		}

		void setRightChild(node* target)
		{
			target->_parent = this;
			_right = target;
		}

		// w가 black이라면 restructuring
		// -> z(나), v(부모), 부모의 부모.
		//    1. 셋을 오름차순 정렬.
		//    2. 가운데에 있는게 부모가 됨. (부모로 올라간걸 black)
		//    3. 왼쪽은 작은거, 오른쪽은 큰거. (자식은 red행)
		//    4. 원래 자식이었던건 같이 딸려감.

		void restructure()
		{
			node* nodes[] = { getUncleNode(), _parent, this };
			//for (int i = 0; i < 2; i++)
			//	for (int j = 0; j < 2 - i; j++)
			//		if (nodes[j] > nodes[j + 1])
			//			std::swap(&nodes[j], &nodes[j + 1]);

			// 버블 소트 정렬의 간략화
			if (_compare(*(nodes[1]), *(nodes[0])))
				std::swap(&nodes[1], &nodes[0]);
			if (_compare(*(nodes[2]), *(nodes[1])))
				std::swap(&nodes[2], &nodes[1]);
			if (_compare(*(nodes[1]), *(nodes[0])))
				std::swap(&nodes[1], &nodes[0]);

			node* grandparent = _parent->_parent;
			nodes[1]->_black = true;
			nodes[0]->_black = false;
			nodes[2]->_black = false;
			unlink(nodes[0], nodes[1], nodes[2]);
			unlink(nodes[2], nodes[0], nodes[1]);
			nodes[1]->setLeftChild(nodes[0]);
			nodes[1]->setRightChild(nodes[2]);
		}

		static void unlink(node* node, node* target1, node* target2)
		{
			if (node->_left == target1 || node->_left == target2)
				node->_left = nullptr;
			if (node->_right == target1 || node->_right == target2)
				node->_right = nullptr;
		}

		// w가 red라면 recoloring
		//    1. v(부모), w(부모의 형제)를 black으로.
		//    2. z(나)와 부모의 부모는 red로.

		// -> 부모의 부모의 부모가 존재하고, 그것이 red일 경우
		//    1. 부모의 부모를 다시 recoloring 또는 restructing.

		void recolor()
		{
			node* uncle = getUncleNode();
			node* grandparent = _parent->_parent;

			_parent->black = true;
			uncle->black = true;
			this->black = false;
			grandparent->black = false;
			if (grandparent->_parent == nullptr)
				return;
			if (grandparent->_parent->_black)
				return;
			grandparent->adjust();
		}

	public:
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

		node*	find(T const& value)
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

		node*	insert(T const& value)
		{
			// 이진 탐색 트리 insert

			if (value == _value)
				return nullptr;
			if (_compare(value, _value))
			{
				if (_left)
					return (_left->insert(value));
				else
					return (_left = new node(false, value, this));
			}
			else
			{
				if (_right)
					return (_right->insert(value));
				else
					return (_right = new node(false, value, this));
			}
		}

		void	adjust()
		{
			node* uncleNode = getUncleNode();
			if (uncleNode == nullptr)
				return;

			// w가 black이라면 restructuring
			if (uncleNode->_black)
				restructure();

			// w가 red라면 recoloring
			else
				recolor();
		}
	};

	// https://zeddios.tistory.com/237
	// https://ratsgo.github.io/data%20structure&algorithm/2017/10/22/bst/
	// https://lemonlemon.tistory.com/135

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
			// 이진 탐색 트리로 삽입
			node<T, Compare>* inserted;
			if (root == nullptr)
				inserted = (root = new node<T, Compare>(true, value));
			else
				inserted = root->insert(value);

			if (inserted == nullptr) // 이미 해당 요소가 있는 경우
				return;

			// Restructuring / Recoloring
			inserted->adjust();
		}

		bool	erase(T const& value)
		{
			// 삭제 후 Restructuring / Recoloring?
			node<T, Compare>* elem = find(value);
			if (elem == nullptr)
				return false;

			// 요약
			//  이진 탐색 트리에 맞게 삭제


			// 어떻게..?

			// https://www.programiz.com/dsa/deletion-from-a-red-black-tree
			// 1. 삭제할 노드의 색깔 저장.

			// CASE 1: 삭제할 노드의 왼쪽 자식이 NULL일 경우
			//   1. 삭제할 노드의 오른쪽 자식을 x 변수에 저장
			//   2. 삭제할 노드의 위치에 x 로 대체.

			// CASE 2: 삭제할 노드의 오른쪽 자식이 NULL일 경우
			//   1. 삭제할 노드의 왼쪽 자식을 x 변수에 저장.
			//   2. 삭제할 노드의 위치에 x 로 대체.

			// CASE 3: 나머지 경우
			//   1. 삭제할 노드의 오른쪽 서브트리를 y 변수에 저장.
			//   2. y의 색깔을 저장.
			//   3. y의 오른쪽 자식 노드를 x 변수에 저장.
			//   4. y가 삭제할 노드의 자식이라면, x의 부모를 y로 설정.
			//      아니라면, y를 y의 오른쪽 자식 노드로 대체.
			//   5. 삭제할 노드를 y로 대체.
			//   6. y의 색을 2에서 저장한 색깔로 대체.
			//   7. 6에서 설정된 색이 BLACK이라면 추가 작업 필요.

			// -------------- 추가 작업 --------------

			//



			// case1. 삭제할 노드에 자식 노드가 없는 경우
			// --> 노드를 삭제 후 부모에서 연결 끊기.

			// case2. 삭제할 노드에 자식 하나가 있는 경우.
			// --> 노드를 삭제 후, 하나 뿐인 자식을 부모와 연결.

			// case3. 삭제할 노드에 자식 두개가 있는 경우.
			// --> 1. 삭제 대상 노드의 오른쪽 서브트리를 찾는다.
			//     2. 계승자 (1에서 찾은 서브트리의 최소 값) 노드를 찾는다.
			//     3. 2 에서 찾은 계승자의 값을 삭제 대상 노드에 복사한다.
			//     4. 계승자 노드를 삭제한다.

			// ----- 레드 블랙 트리 삭제 -----
			// case1. 삭제 Node 가 RED인 경우, 더 이상 아무 작업도 필요하지 않음.


			// case2. 삭제 Node 가 BLACK인 경우.
			//    --> 상황에 따라 문제 해결.
			//  ****
			//    [1] 자식이 없었을 경우
			//      1. 그냥 해당 노드를 삭제.
			//
			//    [2] 자식 노드가 RED일 경우.
			//      1. 이진탐색트리에 따라 삭제.
			//      2. 자식 노드의 색깔들을 모두 BLACK으로.
			//
			//    [3] 삭제 노드와 자식이 모두 BLACK일 경우.
			//      1. 형제를 BLACK으로.
			//      2. 자신과 형제의 부모를 RED로.
			//      3.
			//
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
