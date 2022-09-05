# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/17 15:35:32 by lnelson           #+#    #+#              #
#    Updated: 2022/09/05 19:07:20 by lnelson          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= exe

CC			= c++

INCL 		=	${INCL_DIR}containers.hpp \
				${INCL_DIR}enable_if.hpp \
				${INCL_DIR}is_integral.hpp \
				${INCL_DIR}iterator.hpp \
				${INCL_DIR}map.hpp \
				${INCL_DIR}pair.hpp \
				${INCL_DIR}stack.hpp \
				${INCL_DIR}vector.hpp \
				${INCL_DIR}lexicographical_compare.hpp

INCL_DIR	= ./

