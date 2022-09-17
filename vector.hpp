/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 16:52:34 by lnelson           #+#    #+#             */
/*   Updated: 2022/09/13 21:12:37 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <memory>
#include <stdexcept>
#include "iterator.hpp"
#include "enable_if.hpp"
#include "is_integral.hpp"
#include "lexicographical_compare.hpp"

#define OFR_ERR "Out of range error: vector::_M_range_check"

namespace ft
{
	template <class T, class Allocator = std::allocator<T> > class vector
	{
		public:

		typedef	T 														value_type;
		typedef	Allocator 												allocator_type;
		typedef	std::size_t 											size_type;
	

		typedef	typename Allocator::reference							reference;
		typedef typename Allocator::const_reference						const_reference;
		typedef	typename Allocator::pointer								pointer;
		typedef typename Allocator::const_pointer						const_pointer;


		typedef	ft::random_access_iterator<T>							iterator;
		typedef	ft::random_access_iterator<const T>						const_iterator; 
		typedef	ft::reverse_iterator<T>									reverse_iterator;
		typedef ft::reverse_iterator<const T>							const_reverse_iterator; 


		typedef	typename ft::iterator_traits<iterator>::difference_type	difference_type;
		

		private:

		pointer			_begin;
		pointer 		_end;
		size_type		_size;
		size_type		_capacity;
		allocator_type	_allocator;

		public:

		explicit vector(const allocator_type& alloc = allocator_type())
		{
			_allocator = alloc;
			_size = 0;
			_capacity = 16;
			_begin = _allocator.allocate(_capacity, 0);
			_end = _begin;
		}

		explicit vector(size_type n, const T& value = T(), const allocator_type& alloc = allocator_type())
		{
			_allocator = alloc;
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
			for (unsigned int i = 0; i < _size; i++)
				_allocator.construct(_begin + i, x[i]);
		}

		template <class InputIterator>
		vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), 
		typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
		{	
			_allocator = alloc;
			_size = 0;
			_capacity = 16;
			_begin = _allocator.allocate(_capacity, 0);
			_end = _begin + _size;
			while (first != last)
			{
				this->push_back(*first);
				first++;
			}
		}

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
			for (unsigned int i = 0; i < _size; i++)
				_allocator.construct(_begin + i, x[i]);
			return (*this);
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
		
		iterator		begin() 		{ return (iterator(_begin)); }
		const_iterator	begin() const	{ return (const_iterator(_begin)); }
		
		iterator		end() 			{ return (iterator(_end)); }
		const_iterator	end() const		{ return (const_iterator(_end)); }

	
		reverse_iterator		rbegin() 		{ return (reverse_iterator(_end)); }
		const_reverse_iterator	rbegin() const	{ return (const_reverse_iterator(_end)); }
		
		reverse_iterator		rend() 			{ return (reverse_iterator(_begin)); }
		const_reverse_iterator	rend() const	{ return (const_reverse_iterator(_begin)); }




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


		template <class InputIterator>
		void assign( InputIterator first, InputIterator last,
		typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
		{
			erase(begin(), end());
			insert(begin(), first, last);
		}

		void assign(size_type n, const T& u)
		{
			erase(begin(), end());
			insert(begin(), n, u);
		}

		iterator	insert( iterator pos, const T& value)
		{
			while (_size + 1 > _capacity)
				reserve(_capacity * 2);

			if (_size == 0)
			{
				_end++;
				_size++;
				_allocator.construct(_begin, value);
				return (begin());
			}

			iterator tmp = end();
			while (tmp != pos)
			{
				_allocator.construct(&(*tmp), *(tmp - 1));
				_allocator.destroy(&(*tmp) - 1);
				tmp--;
			}
			_allocator.construct(&(*pos), value);
			
			_size++;
			_end++;

			return (pos);
		}

		void		insert( iterator pos, size_type count, const T& value)
		{
			if (count == 1)
			{
				insert(pos, value);
				return ;
			}

			while (_size + count > _capacity)
				reserve(_capacity * 2);

			if (pos == end())
			{
				_end += count;
				_size += count;
				for (pointer tmp = &(*pos); tmp != _end; tmp++)
					_allocator.construct(tmp, value);
				return ;
			}

			pointer tmp = _end + count - 1;
			pointer mirror = _end - 1;
			while (mirror != &(*pos) - 1)
			{
				_allocator.construct(tmp, *mirror);
				_allocator.destroy(mirror);
				tmp--;
				mirror--;
			}
			
			for(size_type i = 0; i < count; i++)
			{
				_allocator.construct(&(*pos), value);
				pos++;
			}

			_end += count;
			_size += count;
		}

		template<class InputIt>
		void		insert( iterator pos, InputIt first, InputIt last,
		typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = NULL)
		{
			difference_type count = last - first;
			while (_size + count > _capacity)
				reserve(_capacity * 2);

			pointer tmp = _end + count - 1;
			pointer mirror = _end - 1;
			while (mirror != &(*pos) - 1)
			{
				_allocator.construct(tmp, *mirror);
				_allocator.destroy(mirror);
				mirror--;
				tmp--;
			}
			
			for(difference_type i = 0; i < count; i++)
			{
				_allocator.construct(&(*pos), *first);
				first++;
				pos++;
			}

			_size += count;
			_end += count;
		}

		iterator erase( iterator pos)
		{
			pointer ptr = &(*pos);
			_allocator.destroy(&(*pos));
			while (ptr + 1 != _end)
			{
				_allocator.construct(ptr, *(ptr + 1));
				ptr++;
			}
			_end--;
			_size--;
			return (pos);
		}

		iterator erase( iterator first, iterator last)
		{
			difference_type	erasedSize = last - first;
			iterator 		NewPastLast = last - erasedSize;
			iterator		tmp = first;

			while (tmp != last)
			{
				_allocator.destroy(&(*first));
				tmp++;
			}
			
			iterator	mirror = first;
			while (&*(tmp) != _end)
			{
				_allocator.construct(&(*mirror), *tmp);
				_allocator.destroy(&(*tmp));
				tmp++;
				mirror++;
			}

			_end -= erasedSize;
			_size -= erasedSize;

			return (NewPastLast);
		}

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
			for (unsigned int i = 0; i < lhs.size(); i++)
				if (lhs[i] != rhs[i]) return (false);
		}

		return (true);
	}

	template<class T, class Allocator>
	bool	operator<(const vector<T,Allocator>& lhs, const vector<T,Allocator>& rhs)
	{
		return(lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
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