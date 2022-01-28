/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 14:33:40 by smun              #+#    #+#             */
/*   Updated: 2022/01/28 15:39:32 by smun             ###   ########.fr       */
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
			for (; it != map.end(); ++it)
				std::cout << "[(" << it->first.first << "," << it->first.second << ")-" << it->second << "]" << std::endl;
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
