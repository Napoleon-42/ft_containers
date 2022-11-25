/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 15:07:11 by lnelson           #+#    #+#             */
/*   Updated: 2022/11/25 15:38:25 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RED_BLACK_TREE_HPP
# define RED_BLACK_TREE_HPP

#include "map.hpp"
#include "map_iterator.hpp"

namespace ft
{


	//////////////////// /////////////////////////////////////
	//////////////////    ////////////////////////////////////
	//														//
	//			RED BLACK TREE CLASS DEFINITION				//
	//														//
	//	A rb tree is a serf balancing, binairy search tree,	//
	//	It need a different Node class, herited from the 	//
	//	base node class defined in <map.hpp>				//
	//////////////////////////////////////////    ////////////
	/////////////////////////////////////////// //////////////

template<
		class T,
		class key_compare,
		class allocator_type
		> class red_black_tree
	{
		public:
		
		typedef T	value_type;
		typedef 		
	};


	//////////////////// /////////////////////////////////////
	//////////////////    ////////////////////////////////////
	//														//
	//			RED BLACK TREE NODE CLASS DEFINITION		//
	//														//
	//	This node type just add a "bool red;" variable to 	//
	//						the base class					//
	//////////////////////////////////////////    ////////////
	/////////////////////////////////////////// //////////////


	template<
	
};

#endif