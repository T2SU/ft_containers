/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 14:33:40 by smun              #+#    #+#             */
/*   Updated: 2022/01/29 14:47:20 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_MAP_HPP
# define TESTS_MAP_HPP

# include <iostream>
# include <map>
# include "../map.hpp"

namespace ft
{
	template<typename Map>
	class MapTest
	{
	private:
		MapTest(MapTest const&);
		MapTest& operator=(MapTest const&);

		void PrintSize(Map const& map)
		{
			std::cout << "size:" << map.size() << std::endl;
		}

		void PrintElements(Map const& map)
		{
			typename Map::const_iterator it = map.begin();
			typename Map::const_iterator end = map.end();
			for (; it != end; ++it)
				std::cout << (it->first) << "-" << (it->second) << std::endl;
		}

		template<typename V>
		static V	makePairForTest(int k, std::string v)
		{
			return V(k, v);
		}


	public:
		MapTest() {}
		virtual ~MapTest() {}

		typedef typename Map::key_type		key_type;
		typedef typename Map::mapped_type	mapped_type;
		typedef typename Map::value_type	value_type;
		typedef typename Map::size_type		size_type;

		# include "map/basictest1.ipp"
	};
}

#endif
