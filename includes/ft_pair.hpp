/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pair.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 23:05:32 by lnelson           #+#    #+#             */
/*   Updated: 2022/08/31 23:13:29 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PAIR_HPP
# define FT_PAIR_HPP


namespace ft
{

template<class T1, class T2>
struct pair
{

	public:
	
	typedef T1 first_type;
	typedef T2 second_type;
	
	first_type	first;
	second_type	second;

}


};


#endif