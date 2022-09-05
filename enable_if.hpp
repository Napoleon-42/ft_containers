/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_enable_if.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 16:33:15 by lnelson           #+#    #+#             */
/*   Updated: 2022/09/05 18:47:59 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENABLE_IF
# define ENABLE_IF

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