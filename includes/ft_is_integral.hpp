/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_integral.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 12:46:26 by lnelson           #+#    #+#             */
/*   Updated: 2022/09/04 12:46:49 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_IS_INTEGRAL
#define FT_IS_INTEGRAL

namespace ft
{

template<class T, T v>
struct integral_constant
{
	static const T value = v;
	typedef T value_type;
	typedef integral_constant<T, v> type;
	operator value_type() const { return value; };
};

typedef integral_constant<bool, true> true_type;
typedef integral_constant<bool, false> false_type;

template <class T> struct is_integral : public false_type {};
template <class T> struct is_integral<const T> : public is_integral<T> {};
template <class T> struct is_integral<volatile const T> : public is_integral<T>{};
template <class T> struct is_integral<volatile T> : public is_integral<T>{};

template<> struct is_integral<unsigned char> : public true_type {};
template<> struct is_integral<unsigned short> : public true_type{};
template<> struct is_integral<unsigned int> : public true_type{};
template<> struct is_integral<unsigned long> : public true_type{};

template<> struct is_integral<signed char> : public true_type{};
template<> struct is_integral<short> : public true_type{};
template<> struct is_integral<int> : public true_type{};
template<> struct is_integral<long> : public true_type{};
template<> struct is_integral<char> : public true_type{};
template<> struct is_integral<bool> : public true_type{};

};

#endif