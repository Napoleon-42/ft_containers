/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_enable_if.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 16:33:15 by lnelson           #+#    #+#             */
/*   Updated: 2022/09/03 16:47:28 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ENABLE_IF
# define FT_ENABLE_IF

namespace ft
{

template <bool  condition, typename T>
struct enable_if;

template <typename T>
struct enable_if<true, T>
{
	typedef T type;
};


};

#endif 