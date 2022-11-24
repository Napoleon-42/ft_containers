/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 15:27:56 by lnelson           #+#    #+#             */
/*   Updated: 2022/11/25 00:11:28 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "stack.hpp"
#include "vector.hpp"
#include "map.hpp"
#include <iostream>
#include <iomanip>
#include <stack>
#include <vector>
#include <map>
#include <complex>
#include <valarray>
#include <string>

#define TESTED_TYPE int
#include <list>

/*
// --- Class foo
template <typename T>
class foo {
	public:
		typedef T	value_type;

		foo(void) : value(), _verbose(false) { };
		foo(value_type src, const bool verbose = false) : value(src), _verbose(verbose) { };
		foo(foo const &src, const bool verbose = false) : value(src.value), _verbose(verbose) { };
		~foo(void) { if (this->_verbose) std::cout << "~foo::foo()" << std::endl; };
		void m(void) { std::cout << "foo::m called [" << this->value << "]" << std::endl; };
		void m(void) const { std::cout << "foo::m const called [" << this->value << "]" << std::endl; };
		foo &operator=(value_type src) { this->value = src; return *this; };
		foo &operator=(foo const &src) {
			if (this->_verbose || src._verbose)
				std::cout << "foo::operator=(foo) CALLED" << std::endl;
			this->value = src.value;
			return *this;
		};
		value_type	getValue(void) const { return this->value; };
		void		switchVerbose(void) { this->_verbose = !(this->_verbose); };

		operator value_type(void) const {
			return value_type(this->value);
		}
	private:
		value_type	value;
		bool		_verbose;
};

template <typename T>
std::ostream	&operator<<(std::ostream &o, foo<T> const &bar) {
	o << bar.getValue();
	return o;
}
// --- End of class foo

template <typename T>
T	inc(T it, int n)
{
	while (n-- > 0)
		++it;
	return (it);
}

template <typename T>
T	dec(T it, int n)
{
	while (n-- > 0)
		--it;
	return (it);
}
*/

/*
template <class T>
void	printSize(ft::vector<T> v) { std::cout << v.size() << std::endl; }

template <class T>
void	printSize(std::vector<T> v) {std::cout << v.size() << std::endl; }

template <class T>
void	printContent(std::vector<T> v)
{
	std::cout << std::endl;

	std::cout << std::setw(13) << "Content std " << std::endl;
	for(typename std::vector<T>::iterator it = v.begin(); it != v.end(); it++)
	{
		std::cout << std::setw(10) << *it << std::endl;
	}
		std::cout << std::setw(10) << "[end]" << std::endl;
	std::cout << std::endl;
}


template <class T>
void	printContent(ft::vector<T> v)
{
	std::cout << std::endl;

	std::cout << std::setw(13) << "Content ft " << std::endl;
	for(typename ft::vector<T>::iterator it = v.begin(); it != v.end(); it++)
	{
		std::cout << std::setw(10) << *it << std::endl;
	}
		std::cout << std::setw(10) << "[end]" << std::endl;
	std::cout << std::endl;
}

template <typename Ite_1, typename Ite_2>
void ft_eq_ope(const Ite_1 &first, const Ite_2 &second, const bool redo = 1)
{
	std::cout << (first < second) << std::endl;
	std::cout << (first <= second) << std::endl;
	std::cout << (first > second) << std::endl;
	std::cout << (first >= second) << std::endl;
	std::cout << std::endl;
	if (redo)
		ft_eq_ope(second, first, 0);
}

int		main(void)
{
	{
	
	const int size = 5;
	std::vector<TESTED_TYPE> vct(size);
	std::vector<TESTED_TYPE>::reverse_iterator it = vct.rbegin();
	std::vector<TESTED_TYPE>::const_reverse_iterator ite = vct.rbegin();

	for (int i = 0; i < size; ++i)
		it[i] = (size - i) * 5;

	it = it + 5;
	it = 1 + it;
	it = it - 4;
	std::cout << *(it += 2) << std::endl;
	std::cout << *(it -= 1) << std::endl;

	*(it -= 2) = 42;
	*(it += 2) = 21;

	std::cout << "const_ite +=/-=: " << *(ite += 2) << " | " << *(ite -= 2) << std::endl;

	std::cout << "(it == const_it): " << (ite == it) << std::endl;
	std::cout << "(const_ite - it): " << (ite - it) << std::endl;
	std::cout << "(ite + 3 == it): " << (ite + 3 == it) << std::endl;

	}

	std::cout << "FT:" << std::endl;

	{
	
	const int size = 5;
	ft::vector<TESTED_TYPE> vct(size);
	ft::vector<TESTED_TYPE>::reverse_iterator it = vct.rbegin();
	ft::vector<TESTED_TYPE>::const_reverse_iterator ite = vct.rbegin();

	for (int i = 0; i < size; ++i)
		it[i] = (size - i) * 5;

	it = it + 5;
	it = 1 + it;
	it = it - 4;
	std::cout << *(it += 2) << std::endl;
	std::cout << *(it -= 1) << std::endl;

	*(it -= 2) = 42;
	*(it += 2) = 21;

	std::cout << "const_ite +=/-=: " << *(ite += 2) << " | " << *(ite -= 2) << std::endl;

	std::cout << "(it == const_it): " << (ite == it) << std::endl;
	std::cout << "(const_ite - it): " << (ite - it) << std::endl;
	std::cout << "(ite + 3 == it): " << (ite + 3 == it) << std::endl;

	}

	return (0);
}

*/


int main()
{
	//	MAP TEST
	{
		std::map<int, std::string> std_map;
		ft::map<int, std::string> ft_map;

		std::cout << "start sizes: ST: " << std_map.size() << " | FT: " << ft_map.size() << std::endl << std::endl;

		int i = 0;
		while (i < 42)
		{
			std_map.insert(std::make_pair(i, "String."));
			std::cout << "ST:" << std_map.size() << std::endl;
			ft_map.insert(ft::make_pair(i, "String."));
			std::cout << "FT:" << ft_map.size() << std::endl << std::endl;
			i++;
		}
	}

	//	STACK TEST
	/*{
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
	}*/


	// VECTOR TEST
	/*{
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
	}*/
}
