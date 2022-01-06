/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 17:14:00 by smun              #+#    #+#             */
/*   Updated: 2022/01/06 17:25:48 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <memory>

namespace ft
{
	template<typename T>
	struct node
	{
		T value;
		node* parent;
		node* left;
		node* right;
		bool black;
		node(bool black,
			node* parent = nullptr,
			node* left = nullptr,
			node* right = nullptr)
			: parent(parent)
			, left(left)
			, right(right)
			, black(black)
			, value()
		{}
	};

	// https://zeddios.tistory.com/237

	template<typename T>
	class tree
	{
	private:
		node<T> root;

		node<T>*	find(T const& value)
		{
			// 중위 탐색
		}

	public:
		tree() {}
		virtual ~tree() {}
		tree(tree const& o);
		tree& operator=(tree const& o);

		void	insert(T const& value)
		{
			// 이진 탐색 트리
			// 연결리스트
			// Restructuring / Recoloring
		}

		bool	erase(T const& value)
		{
			// 삭제 후 Restructuring / Recoloring?
		}

		void	print()
		{
			// 중위 순회
		}

		bool	contains(T const& value)
		{
			// 중위 순회
		}
	};
}

int main()
{
	ft::tree<int> t;

	return 0;
}
