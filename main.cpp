/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 15:27:56 by lnelson           #+#    #+#             */
/*   Updated: 2022/09/04 17:18:50 by lnelson          ###   ########.fr       */
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
			stl_vector.push_back(i * 10);
			ft_vector.push_back(i * 10);
		}

		std::cout << "PRINTING VECTORS" << std::endl;
		
		int i = 0;
		
		std::vector<int>::iterator it = stl_vector.begin();
		std::vector<int>::iterator ite = stl_vector.end();

		ft::vector<int>::iterator fit = ft_vector.begin();
		ft::vector<int>::iterator fite = ft_vector.end();
		std::cout << "I :  |" << std::setw(10) << "STL:" << "|" << std::setw(10) << "FT:" << "|" << std::setw(10) << "SIZE:" << "|" << std::setw(10) << "CAPACITY:" << std::endl;
		std::cout << "_____________________________________________________" << std::endl;

		while(it != ite && fit != fite)
		{
			std::cout << std::setw(5) << i << "|" <<  std::setw(10) << *it << " | " << std::setw(10) << *fit << "|" << std::endl;

			i++;
			it++;
			fit++;

		}

		ft::vector<int>::const_iterator cfit = fit;
	}
}