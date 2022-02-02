/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nullptr_t.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 15:47:51 by smun              #+#    #+#             */
/*   Updated: 2022/02/02 15:55:02 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NULLPTR_T_HPP
# define NULLPTR_T_HPP

# if __cplusplus < 201103L
#  ifndef nullptr
class nullptr_t
{
public:
	template<class T>
	inline operator T*() const
	{
		return 0;
	}

	template<class C, class T>
	inline operator T C::*() const
	{
		return 0;
	}

private:
	void operator&() const;

} nullptr = {};
#  endif
# endif

#endif
