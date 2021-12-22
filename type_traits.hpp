/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 19:42:47 by smun              #+#    #+#             */
/*   Updated: 2021/12/22 20:09:02 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_TRAITS_HPP
# define TYPE_TRAITS_HPP

namespace ft
{
	template<typename Type, Type val>
	struct integral_constant
	{
		static const Type			value = val;
		typedef Type				value_type;
		typedef integral_constant	type;
	};

	typedef integral_constant<bool, true>	true_type;
	typedef integral_constant<bool, false>	false_type;

	template <bool, typename Type = void>
	struct enable_if
	{
	};

	template <typename Type>
	struct enable_if<true, Type>
	{
		typedef Type type;
	};

	template <typename Type>	struct is_integral						: public false_type {};
	template <>					struct is_integral<bool>				: public true_type {};
	template <>					struct is_integral<char>				: public true_type {};
	template <>					struct is_integral<signed char>			: public true_type {};
	template <>					struct is_integral<unsigned char>		: public true_type {};
	template <>					struct is_integral<wchar_t>				: public true_type {};
	template <>					struct is_integral<short>				: public true_type {};
	template <>					struct is_integral<unsigned short>		: public true_type {};
	template <>					struct is_integral<int>					: public true_type {};
	template <>					struct is_integral<unsigned int>		: public true_type {};
	template <>					struct is_integral<long>				: public true_type {};
	template <>					struct is_integral<unsigned long>		: public true_type {};
	template <>					struct is_integral<long long>			: public true_type {};
	template <>					struct is_integral<unsigned long long>	: public true_type {};

}

#endif
