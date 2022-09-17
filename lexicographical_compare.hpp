/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexicographical_compare.hpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 20:37:34 by lnelson           #+#    #+#             */
/*   Updated: 2022/09/13 21:11:12 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXICOGRAPHICAL_COMPARE_HPP
#define LEXICOGRAPHICAL_COMPARE_HPP

namespace ft
{

	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare (	InputIterator1 first1, InputIterator1 last1,
	                                InputIterator2 first2, InputIterator2 last2)
	{
	  while (first1!=last1)
	  {
	    if (first2==last2 || *first2<*first1) return false;
	    else if (*first1<*first2) return true;
	    ++first1; ++first2;
	  }
	  return (first2!=last2);
	}
};

#endif