/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 15:27:56 by lnelson           #+#    #+#             */
/*   Updated: 2022/09/07 20:47:20 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.hpp"
#include "vector.hpp"
#include <iostream>
#include <iomanip>
#include <stack>
#include <vector>
#include <map>



/*
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
*/

template <class T>
void	printSize(ft::vector<T> v) { std::cout << v.size(); }

template <class T>
void	printSize(std::vector<T> v) {std::cout << v.size(); }

int main(void)
{
	ft::vector<std::string> fv(10);
	std::vector<std::string> stdv(10);

	

	fv.erase(fv.end() - 1);
	stdv.erase(stdv.end() - 1);

	std::cout << std::endl << "ft_vector: ";
	printSize(fv);

	std::cout << std::endl << "std_vector: ";
	printSize(stdv);

}