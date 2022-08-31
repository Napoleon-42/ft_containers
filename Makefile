# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/17 15:35:32 by lnelson           #+#    #+#              #
#    Updated: 2022/08/31 22:45:09 by lnelson          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= exe

CC			= c++

INCL 		=	${INCL_DIR}ft_containers.hpp \
				${INCL_DIR}ft_enable_if.hpp \
				${INCL_DIR}ft_is_integral.hpp \
				${INCL_DIR}ft_iterator.hpp \
				${INCL_DIR}ft_map.hpp \
				${INCL_DIR}ft_pair.hpp \
				${INCL_DIR}ft_stack.hpp \
				${INCL_DIR}ft_vector.hpp \
				${INCL_DIR}lexicographical_compare.hpp

INCL_DIR	= ./includes/

SRCS_DIR	= ./srcs/


