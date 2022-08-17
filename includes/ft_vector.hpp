/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 16:52:34 by lnelson           #+#    #+#             */
/*   Updated: 2022/08/17 18:22:57 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VECTOR_HPP
# define FT_VECTOR_HPP

#include <memory>
#include <stdexcept>
#define OFR_ERR "Out of range error: vector::_M_range_check"

namespace ft
{
	template <class T, class Allocator = std::allocator<T> > class vector
	{
		public:

		typedef	T 									value_type;
		typedef	Allocator 							allocator_type;
		typedef	std::size_t 						size_type;
		
		// typedef DIFFERENCE_TYPE - LOL

		typedef	value_type& 						reference;
		typedef const value_type& 					const_reference;
		typedef	typename Allocator::pointer			pointer;
		typedef typename Allocator::const_pointer	const_pointer;

		/*
		typedef 									iterator;
		typedef										const_iterator;
		typedef										reverse_iterator;
		typedef 									const_reverse_iterator;
		*/

		private:

		pointer			_begin;
		pointer 		_end;
		size_type		_size;
		size_type		_capacity;
		allocator_type	_allocator;

		public:

		vector();
		~vector();

		// ELEMENT ACCES:

		reference		at(size_type pos) { if (pos < _size) throw (std::out_of_range(OFR_ERR)); return (_begin + pos); }
		const_reference	at(size_type pos) const { if (pos < _size) throw (std::out_of_range(OFR_ERR)); return (_begin + pos); }
		reference		operator[](size_type pos) { if (pos < _size) throw (std::out_of_range(OFR_ERR)); return (_begin + pos); }
		const_reference	operator[](size_type pos) const { if (pos < _size) throw (std::out_of_range(OFR_ERR)); return (_begin + pos); }
		reference		front() { return (*_begin); }
		const_reference	front() const { return (*_begin); }
		reference		back()	{ return (*_end); }
		const_reference	back() const { return (*_end); }
		T*				data() { return (_begin); }
		const T*		data() const { return (_begin); }
		
		// ITERATORS:
		//
		//
		//
		//

		// CAPACITY:

		bool			empty() const { return (_size == 0); }
		size_type		size() const { return (_size); }
		size_type		max_size() const; /////////////////////////////////
		void			reserve(size_type new_cap); ///////////////////////
		size_type		capacity() const { return (_capacity); }

		//	MODIFIERS:

		void			clear();
		// ITERATOR INSERT
		// ITERATOR ERASE
		void			push_back(const T& value);
		void			pop_back();
		void			resize(size_type n, value_type val = value_type());
		void			swap();
	};
};

#endif