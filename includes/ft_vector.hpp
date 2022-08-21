/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 16:52:34 by lnelson           #+#    #+#             */
/*   Updated: 2022/08/21 17:48:31 by lnelson          ###   ########.fr       */
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

		typedef	typename Allocator::reference		reference;
		typedef typename Allocator::const_reference	const_reference;
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

		explicit vector(const allocator_type& alloc = allocator_type())
		{
			_size = 0;
			_capacity = 16;
			_begin = _allocator.allocate(_capacity, 0);
			_end = _begin;
		}

		explicit vector(size_type n, const T& value = T(), const allocator_type& alloc = allocator_type())
		{
			_size = n;
			_capacity = n * 2;
			_begin = _allocator.allocate(_capacity, 0);
			_end = _begin + _size;
			for (pointer begin = _begin; begin != _end; begin++)
				_allocator.construct(begin, value);
		}

		vector(const vector<T,Allocator>& x)
		{
			_size = x.size();
			_capacity = x.capacity();
			_begin = _allocator.allocate(_capacity, 0);
			_end = _begin + _size;
			for (int i = 0; i < _size; i++)
				_allocator.construct(_begin + i, x[i]);
		}

		//template <class InputIterator>
		//vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());

		~vector()
		{
			for (pointer begin = _begin; begin != _end; begin++)
				_allocator.destroy(begin);
			_allocator.deallocate(_begin, _capacity);	
		}

		vector&	operator=(const vector x)
		{
			this->clear();
			_allocator.deallocate(_begin, _capacity);

			_size = x.size();
			_capacity = x.capacity();
			_begin = _allocator.allocate(_capacity, 0);
			_end = _begin + _size;
			for (int i = 0; i < _size; i++)
				_allocator.construct(_begin + i, x[i]);
		}

		// ELEMENT ACCES:

		reference		at(size_type pos) 				{ if (pos >= _size) throw (std::out_of_range(OFR_ERR)); return (*(_begin + pos)); }
		const_reference	at(size_type pos) const 		{ if (pos >= _size) throw (std::out_of_range(OFR_ERR)); return (*(_begin + pos)); }
		reference		operator[](size_type pos) 		{ return (*(_begin + pos)); }
		const_reference	operator[](size_type pos) const { return (*(_begin + pos)); }
		reference		front() 						{ return (*_begin); }
		const_reference	front() const 					{ return (*_begin); }
		reference		back()							{ return (*(_end - 1)); }
		const_reference	back() const 					{ return (*(_end - 1)); }
		T*				data() 							{ return (_begin); }
		const T*		data() const 					{ return (_begin); }



		// ITERATORS:
		//
		//
		//
		//



		// CAPACITY:

		bool			empty() const 					{ return (_size == 0); }
		size_type		size() const 					{ return (_size); }
		size_type		capacity() const 				{ return (_capacity); }
		size_type		max_size() const 				{ return (_allocator.max_size()); }
		
		void			reserve(size_type new_cap)
		{
			if (new_cap <= _capacity)
				return;

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

		void			resize(size_type n, value_type val = value_type())
		{
			if (n == _size || n < 0)
				return;

			else if (n < _size)
			{
				for (pointer ptr = _end - 1; _size != n; ptr--, _size--)
					_allocator.destroy(ptr);
			}

			else
			{
				while (n > _capacity)
					reserve(_capacity * 2);
				for (pointer ptr = _end; _size != n; ptr++, _size++)
					_allocator.construct(ptr, val);
			}

			_end = _begin + _size;
		}



		//	MODIFIERS:

		// ITERATOR INSERT

		// ITERATOR ERASE

		void			clear()
		{
			for (pointer begin = _begin; begin != _end; begin++)
				_allocator.destroy(begin);

			_size = 0;
			_end = _begin;
		}

		void			push_back(const T& value)
		{
			if (_size + 1 > _capacity)
				reserve(_capacity * 2);

			_allocator.construct(_begin + _size, value);
			_size++;
			_end++;
		}

		void			pop_back()
		{
			if (_size == 0)
				return ;

			_size--;
			_allocator.destroy(_begin + _size);
			_end--;
		}

		void			swap(vector& x)
		{
			std::swap(_begin, x._begin);
			std::swap(_size, x._size);
			std::swap(_capacity, x._capacity);
			std::swap(_end, x._end);
		}
	};


	//	OPPERATORS

	template<class T, class Allocator>
	bool	operator==(const vector<T,Allocator>& lhs, const vector<T,Allocator>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		else
		{
			for (int i = 0; i < lhs.size(); i++)
				if (lhs[i] != rhs[i]) return (false);
		}

		return (true);
	}

	template<class T, class Allocator>
	bool	operator<(const vector<T,Allocator>& lhs, const vector<T,Allocator>& rhs)
	{
		if (lhs.size() < rhs.size())
			return (true);
		else if (lhs.size() > rhs.size())
			return (false);
		else if (lhs.size() == rhs.size())
		{
			for (int i = 0; i < lhs.size(); i++)
				if (lhs[i] < rhs[i]) return (true);
		}

		return (false);
	}

	template<class T, class Allocator>
	bool	operator!=(const vector<T,Allocator>& lhs, const vector<T,Allocator>& rhs) { return (!(lhs == rhs)); }


	template<class T, class Allocator>
	bool	operator>(const vector<T,Allocator>& lhs, const vector<T,Allocator>& rhs) { return (rhs < lhs); }
	

	template<class T, class Allocator>
	bool	operator<=(const vector<T,Allocator>& lhs, const vector<T,Allocator>& rhs) { return (!(rhs < lhs)); }
	

	template<class T, class Allocator>
	bool	operator>=(const vector<T,Allocator>& lhs, const vector<T,Allocator>& rhs) { return (!(lhs < rhs)); }
	
};


#endif