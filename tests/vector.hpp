/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 19:59:27 by smun              #+#    #+#             */
/*   Updated: 2021/12/25 14:24:04 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_VECTOR_HPP
# define TESTS_VECTOR_HPP

# include <iostream>
# include <vector>
# include "../vector.hpp"

namespace ft
{
	template<typename Vector>
	class VectorTest
	{
	private:
		VectorTest(VectorTest const&);
		VectorTest& operator=(VectorTest const&);

		void PrintSizeAndCapacity(Vector const& vec)
		{
			std::cout << "size:" << vec.size() << ", capacity: " << vec.capacity() << std::endl;
		}

		void PrintElements(Vector const& vec)
		{
			typename Vector::const_iterator it = vec.begin();
			for (; it != vec.end(); ++it)
				std::cout << *it << std::endl;
		}

	public:
		VectorTest() {}
		virtual ~VectorTest() {}

		typedef typename Vector::value_type	value_type;
		typedef typename Vector::size_type	size_type;

		# include "vector/basictest1.ipp"
		# include "vector/basictest2.ipp"
		# include "vector/resize.ipp"
		# include "vector/assign.ipp"
	};

}

#endif
