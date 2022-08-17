/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 15:27:56 by lnelson           #+#    #+#             */
/*   Updated: 2022/08/17 17:49:33 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_containers.hpp"
#include "ft_stack.hpp"
#include "ft_vector.hpp"
#include <iostream>
#include <iomanip>

int main()
{
	std::stack<int> stl_stack;
	ft::stack<int> ft_stack;

	for(int i = 0; i < 42 ; i++)
	{
		stl_stack.push(i);
		ft_stack.push(i);
	}

	std::cout << "PRINTING STACKS" << std::endl;
	for(int i = 0; i < 42 ; i++)
	{
		std::cout << "stl_stack " << std::setw(3) << i << " = " << std::setw(5) << stl_stack.top() << " | ";
		std::cout << " ft_stack " << std::setw(3) << i << " = " << std::setw(5) << ft_stack.top() << " | ";
		std::cout << "sizes = " << stl_stack.size() << " | " << ft_stack.size() <<  std::endl;

		stl_stack.pop();
		ft_stack.pop();
	}
}