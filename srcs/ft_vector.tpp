/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.tpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 18:35:07 by lnelson           #+#    #+#             */
/*   Updated: 2022/08/19 23:02:42 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VECTOR_TPP
# define FT_VECTOR_TPP

#include "ft_vector.hpp"

using namespace ft;

//	CAPACITY

template <class T>
vector<T>::size_type	vector<T>::max_size() const
{

}

template <class T>
void					vector<T>::reserve(vector<T>::size_type new_cap)
{
	if (new_cap <= _capacity)
		return();
	
	pointer new_begin = _allocator.allocate(new_cap, _begin);
	{
		pointer oldVptr = _begin;
		pointer newVptr = new_begin;
	
		while (oldVptr != _end)
		{
			_allocator.construct(newVptr, *oldVptr);
			oldVptr++;
			newVptr++;
		}
	
		for (pointer begin = _begin; begin != _end; begin++)
			_allocator.destroy(begin);
		_allocator.deallocate(_begin, _capacity);
	}

	_begin = new_begin;
	_end = _begin + _size;
	_capacity = new_cap;

}

template <class T>
void	vector<T>::resize(vector<T>::size_type n, value_type val = value_type())
{
	if (n == _size || n < 0)
		return();

	else if (n < _size)
	{
		for (pointer ptr = _end - 1; _size != n; ptr--, _size--)
			_allocator.destroy(ptr);
		_end = begin + _size;
	}

	else (n > _size)
	{
		while (n > _capacity)
			reserve(_capacity * 2);
		for (pointer ptr = _end; _size != n; ptr++, _size++)
			_allocator.construct(ptr, val);
		_end = begin + _size;		
	}
}


//	MODIFIERS

template <class T>
void	vector<T>::clear()
{
	for (pointer begin = _begin; begin != _end; begin++)
		_allocator.destroy(begin);

	_size = 0;
	_end = _begin;
}

template <class T>
void	vector<T>::push_back(const T& value)
{
	if (_size + 1 > _capacity)
		reserve(_capacity * 2);

	_allocator.construct(_begin + _size, value);
	_size++;
	_end++;
}

template <class T>
void	vector<T>::pop_back()
{
	if (_size == 0)
		return ();

	_size--;
	_allocator.destroy(_begin + _size);
	_end--;
}


template <class T>
void	vector<T>::swap(vector<T>& x)
{
	
}

#endif