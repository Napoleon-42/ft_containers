/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 15:27:56 by lnelson           #+#    #+#             */
/*   Updated: 2022/08/21 12:19:37 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_containers.hpp"
#include "ft_stack.hpp"
#include "ft_vector.hpp"
#include <iostream>
#include <iomanip>

int main()
{
	if (1 > 2)
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

	{
		std::vector<int> stl_vector;
		ft::vector<int> ft_vector;
	
		for (int i = 0; i < 42 ; i++)
		{
			stl_vector.push_back(i);
			ft_vector.push_back(i);
		}

		std::cout << "PRINTING VECTORS" << std::endl;
		for(int i = 0; i < 42 ; i++)
		{
			std::cout << "stl_vector " << std::setw(3) << i << " = " << std::setw(5) << stl_vector[i] << " | ";
			std::cout << " ft_vector " << std::setw(3) << i << " = " << std::setw(5) << ft_vector[i] << " | ";
			std::cout << "sizes = " << stl_vector.size() << " , " << stl_vector.capacity() << " | " << ft_vector.size() << " , " << ft_vector.capacity() << std::endl;

			stl_vector.pop_back();
			ft_vector.pop_back();
		}
	}
}