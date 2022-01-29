/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 16:38:50 by smun              #+#    #+#             */
/*   Updated: 2022/01/29 17:39:38 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_TYPE_TRAITS_HPP
# define ITERATOR_TYPE_TRAITS_HPP

namespace ft
{
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

	template <typename It, typename B1, typename B2, bool = has_iterator_typedef<It>::value>
	struct is_iterator_and_category_derived_from :
		public integral_constant<
			bool,
				is_base_of<B1, typename iterator_traits<It>::iterator_category>::value ||
				is_base_of<B2, typename iterator_traits<It>::iterator_category>::value
		> {};

	template <typename It, typename B1, typename B2>
	struct is_iterator_and_category_derived_from<It, B1, B2, false> : public false_type {};

	template <typename It> struct is_input_iterator
		: public is_iterator_and_category_derived_from<It, ft::input_iterator_tag, std::input_iterator_tag> {};
	template <typename It> struct is_output_iterator
		: public is_iterator_and_category_derived_from<It, ft::output_iterator_tag, std::output_iterator_tag> {};
	template <typename It> struct is_bidirectional_iterator
		: public is_iterator_and_category_derived_from<It, ft::bidirectional_iterator_tag, std::bidirectional_iterator_tag> {};
	template <typename It> struct is_random_access_iterator
		: public is_iterator_and_category_derived_from<It, ft::random_access_iterator_tag, std::random_access_iterator_tag> {};
}

#endif
