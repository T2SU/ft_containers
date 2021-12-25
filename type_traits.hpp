/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 19:42:47 by smun              #+#    #+#             */
/*   Updated: 2021/12/25 19:32:05 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_TRAITS_HPP
# define TYPE_TRAITS_HPP

# include "iterator.hpp"

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

	template <typename T1, typename T2>	struct is_same : public false_type {};
	template <typename T1>				struct is_same<T1, T1> : public true_type {};

	template <typename>
	struct void_t { typedef void type; };

	typedef char (&yes)[1];
	typedef char (&no)[2];

	// `is_base_of` trick idea from boost
	template <typename B, typename D>
	struct _Host
	{
		operator B*() const;
		operator D*();
	};

	template <typename B, typename D>
	struct is_base_of
	{
	private:
		static no check(B*, int);
		template <typename T>
		static yes check(D*, T);
	public:
		static const bool value = sizeof(check(_Host<B, D>(), int())) == sizeof(yes);
	};
	template <typename T>
	struct is_base_of<T, T> : public true_type {};

	template <typename Type>
	struct has_iterator_typedef
	{
	private:
		template <typename What>
		static no check(...);
		template <typename What>
		static yes check(
			typename void_t<typename What::iterator_category>::type* = 0,
			typename void_t<typename What::difference_type>::type* = 0,
			typename void_t<typename What::value_type>::type* = 0,
			typename void_t<typename What::pointer>::type* = 0,
			typename void_t<typename What::reference>::type* = 0
		);
	public:
		static const bool value = sizeof(check<Type>(0, 0, 0, 0, 0)) == sizeof(yes);
	};

	template <typename It, typename B, bool = has_iterator_typedef<It>::value>
	struct is_iterator_and_category_derived_from : public integral_constant<bool, is_base_of<B, typename iterator_traits<It>::iterator_category>::value> {};

	template <typename It, typename B>
	struct is_iterator_and_category_derived_from<It, B, false> : public false_type {};

	template <typename It> struct is_input_iterator
	 : public is_iterator_and_category_derived_from<It, input_iterator_tag> {};
	template <typename It> struct is_output_iterator
	 : public is_iterator_and_category_derived_from<It, output_iterator_tag> {};
	template <typename It> struct is_bidirectional_iterator
	 : public is_iterator_and_category_derived_from<It, bidirectional_iterator_tag> {};
	template <typename It> struct is_random_access_iterator
	 : public is_iterator_and_category_derived_from<It, random_access_iterator_tag> {};

	inline int					convert_to_integral(int val) { return val; }
	inline unsigned				convert_to_integral(unsigned val) { return val; }
	inline long					convert_to_integral(long val) { return val; }
	inline unsigned long		convert_to_integral(unsigned long val) { return val; }
	inline long long			convert_to_integral(long long val) { return val; }
	inline unsigned long long	convert_to_integral(unsigned long long val) { return val; }
}

#endif
