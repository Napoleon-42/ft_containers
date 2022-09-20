/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:02:00 by lnelson           #+#    #+#             */
/*   Updated: 2022/09/20 21:08:17 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

#include <cstddef>

namespace ft
{

	//	BASE ITERATOR CLASS

	template<class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct iterator
	{
		public:
			
			typedef Category	iterator_category;
			typedef T			value_type;
			typedef Distance	difference_type;
			typedef Pointer		pointer;
			typedef Reference	reference;
	};

	//	ITERATOR TAGS

	struct output_iterator_tag {};
	struct input_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag {};
	struct biderectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public biderectional_iterator_tag {};
	
	//	ITERATOR TRAITS

	template <class Iter>
	struct iterator_traits
	{
		typedef	typename Iter::difference_type			difference_type;
		typedef	typename Iter::value_type				value_type;
		typedef	typename Iter::pointer					pointer;
		typedef	typename Iter::reference				reference;
		typedef	typename Iter::iterator_category		iterator_category;
	};

	template <class T>
	struct iterator_traits<T*>
	{	
		typedef std::ptrdiff_t						difference_type;
		typedef	T									value_type;
		typedef T*									pointer;
		typedef T&									reference;
		typedef	std::random_access_iterator_tag		iterator_category;
	};

	template <class T>
	struct iterator_traits<const T*>
	{	
		typedef typename std::ptrdiff_t						difference_type;
		typedef T											value_type;
		typedef	T*											pointer;
		typedef T&											reference;
		typedef	typename std::random_access_iterator_tag	iterator_category;	
	};

	//	RANDOM ACCES ITERATOR

	template<class T>
	class random_access_iterator : public iterator<random_access_iterator_tag, T>
	{
		public:

			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type			value_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category		iterator_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type		difference_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::reference				reference;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::pointer				pointer;

		private:

			pointer _ptr;
		
		public:

			random_access_iterator() : _ptr (NULL) {}
			explicit random_access_iterator(pointer ptr) : _ptr (ptr) {}
			template<class U>
			random_access_iterator(const random_access_iterator<U> & it) { _ptr = &(*it); }
			~random_access_iterator() {}

			pointer	base() { return (_ptr); }

			template<class U>
			random_access_iterator<T>&	operator= (const random_access_iterator<U> & it) { _ptr = &(*it); return (*this); }



			reference					operator[](difference_type n) 	{ return (*(_ptr + n)); }
			reference 					operator* () const 				{ return (*_ptr); }
			pointer						operator->() const 				{ return (_ptr);}



			random_access_iterator<T>&	operator++() 		{ _ptr++; return (*this); }
			random_access_iterator<T>&	operator--()		{ _ptr--; return (*this); }
			random_access_iterator<T>	operator++(int) 	{ random_access_iterator tmp = *this; _ptr++; return (tmp); }
			random_access_iterator<T>	operator--(int) 	{ random_access_iterator tmp = *this; _ptr--; return (tmp); }



			random_access_iterator		operator+(difference_type n) const { return random_access_iterator(_ptr + n); }
			random_access_iterator		operator-(difference_type n) const { return random_access_iterator(_ptr - n); }



			random_access_iterator		operator+=(difference_type n) 		{ _ptr += n; return (*this); }
			random_access_iterator		operator-=(difference_type n) 		{ _ptr -= n; return (*this); }

	};

	template <class T>
	bool	operator==(const random_access_iterator<T> & lit, const random_access_iterator<T> & rit)	{ return (&(*lit) == &(*rit)); }

	template <class T>
	bool	operator!=(const random_access_iterator<T> & lit, const random_access_iterator<T> & rit)	{ return (!(lit == rit)); }

	template <class T>
	bool	operator<(const random_access_iterator<T> & lit, const random_access_iterator<T> & rit)		{ return ( lit < rit ? true : false ); }

	template <class T>
	bool	operator>(const random_access_iterator<T> & lit, const random_access_iterator<T> & rit)		{ return !(lit > rit ? true : false ); }

	template <class T>
	bool	operator>=(const random_access_iterator<T> & lit, const random_access_iterator<T> & rit)	{ return !(lit < rit); }

	template <class T>
	bool	operator<=(const random_access_iterator<T> & lit, const random_access_iterator<T> & rit)	{ return !(lit > rit); }
	
	template <class T>
	typename	random_access_iterator<T>::difference_type operator-(const random_access_iterator<T>& lit, const random_access_iterator<T>& rit)	{ return (&(*lit) - &(*rit)); }

	template <class T>
	typename	random_access_iterator<T>::difference_type operator+(const random_access_iterator<T>& lit, const random_access_iterator<T>& rit)	{ return (&(*lit) + &(*rit)); }
	

	template <class T1, class T2>
	bool	operator==(const random_access_iterator<T1> & lit, const random_access_iterator<T2> & rit)	{ return (&(*lit) == &(*rit)); }

	template <class T1, class T2>
	bool	operator!=(const random_access_iterator<T1> & lit, const random_access_iterator<T2> & rit)	{ return (!(lit == rit)); }

	template <class T1, class T2>
	bool	operator<(const random_access_iterator<T1> & lit, const random_access_iterator<T2> & rit)	{ return ( lit < rit ? true : false ); }

	template <class T1, class T2>
	bool	operator>(const random_access_iterator<T1> & lit, const random_access_iterator<T2> & rit)	{ return !(lit > rit ? true : false ); }

	template <class T1, class T2>
	bool	operator>=(const random_access_iterator<T1> & lit, const random_access_iterator<T2> & rit)	{ return !(lit < rit); }

	template <class T1, class T2>
	bool	operator<=(const random_access_iterator<T1> & lit, const random_access_iterator<T2> & rit)	{ return !(lit > rit); }

	template <class T1, class T2>
	typename	random_access_iterator<T1>::difference_type operator-(const random_access_iterator<T1>& lit, const random_access_iterator<T2>& rit)	{ return (&(*lit) - &(*rit)); }

	template <class T1, class T2>
	typename	random_access_iterator<T1>::difference_type operator+(const random_access_iterator<T1>& lit, const random_access_iterator<T2>& rit)	{ return (&(*lit) + &(*rit)); }
	

	
	// REVERSE ITERATOR

	
	template<class T>
	class reverse_iterator : public iterator<random_access_iterator_tag, T>
	{
		public:

			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type			value_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category		iterator_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type		difference_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::reference				reference;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::pointer				pointer;

		private:

			pointer _ptr;
		
		public:

			reverse_iterator() : _ptr (NULL) {}
			explicit reverse_iterator(pointer ptr) : _ptr (ptr) {}
			template <class U>
			reverse_iterator(const reverse_iterator<U> & it) { _ptr = &(*it); }
			~reverse_iterator() {}

			template <class U>
			reverse_iterator<T>&		operator= (const reverse_iterator<U> & it) { _ptr = &(*it); return (*this); }

			value_type					base() { return (_ptr); }

			reference					operator[](difference_type n) 	{ return (*(_ptr + n)); }
			reference 					operator* () const 				{ return (*_ptr); }
			pointer						operator->() const 				{ return (_ptr);}



			reverse_iterator<T>&		operator++() 		{ _ptr++; return (*this); }
			reverse_iterator<T>&		operator--()		{ _ptr--; return (*this); }
			reverse_iterator<T>			operator++(int) 	{ reverse_iterator tmp = *this; _ptr++; return (tmp); }
			reverse_iterator<T>			operator--(int) 	{ reverse_iterator tmp = *this; _ptr--; return (tmp); }



			reverse_iterator			operator+(difference_type n) const { reverse_iterator tmp = *this; tmp += n; return (tmp); }
			reverse_iterator			operator-(difference_type n) const { reverse_iterator tmp = *this; tmp -= n; return (tmp); }



			reverse_iterator			operator+=(difference_type n) 		{ _ptr += n; return (*this); }
			reverse_iterator			operator-=(difference_type n) 		{ _ptr -= n; return (*this); }

	};

	template <class T>
	bool	operator==(const reverse_iterator<T> & lit, const reverse_iterator<T> & rit)	{ return (&(*lit) == &(*rit)); }

	template <class T>
	bool	operator!=(const reverse_iterator<T> & lit, const reverse_iterator<T> & rit)	{ return (!(lit == rit)); }

	template <class T>
	bool	operator<(const reverse_iterator<T> & lit, const reverse_iterator<T> & rit)		{ return ( lit < rit ? true : false ); }

	template <class T>
	bool	operator>(const reverse_iterator<T> & lit, const reverse_iterator<T> & rit)		{ return !(lit > rit ? true : false ); }

	template <class T>
	bool	operator>=(const reverse_iterator<T> & lit, const reverse_iterator<T> & rit)	{ return !(lit < rit); }

	template <class T>
	bool	operator<=(const reverse_iterator<T> & lit, const reverse_iterator<T> & rit)	{ return !(lit > rit); }

	template <class T>
	typename	reverse_iterator<T>::difference_type operator-(const reverse_iterator<T>& lit, const reverse_iterator<T>& rit)	{ return (&(*lit) - &(*rit)); }

	template <class T>
	typename	reverse_iterator<T>::difference_type operator+(const reverse_iterator<T>& lit, const reverse_iterator<T>& rit)	{ return (&(*lit) + &(*rit)); }
	

	template <class T1, class T2>
	bool	operator==(const reverse_iterator<T1> & lit, const reverse_iterator<T2> & rit)	{ return (&(*lit) == &(*rit)); }

	template <class T1, class T2>
	bool	operator!=(const reverse_iterator<T1> & lit, const reverse_iterator<T2> & rit)	{ return (!(lit == rit)); }

	template <class T1, class T2>
	bool	operator<(const reverse_iterator<T1> & lit, const reverse_iterator<T2> & rit)	{ return ( lit < rit ? true : false ); }

	template <class T1, class T2>
	bool	operator>(const reverse_iterator<T1> & lit, const reverse_iterator<T2> & rit)	{ return !(lit > rit ? true : false ); }

	template <class T1, class T2>
	bool	operator>=(const reverse_iterator<T1> & lit, const reverse_iterator<T2> & rit)	{ return !(lit < rit); }

	template <class T1, class T2>
	bool	operator<=(const reverse_iterator<T1> & lit, const reverse_iterator<T2> & rit)	{ return !(lit > rit); }

	template <class T1, class T2>
	typename	reverse_iterator<T1>::difference_type operator-(const reverse_iterator<T1>& lit, const reverse_iterator<T2>& rit)	{ return (&(*lit) - &(*rit)); }

	template <class T1, class T2>
	typename	reverse_iterator<T1>::difference_type operator+(const reverse_iterator<T1>& lit, const reverse_iterator<T2>& rit)	{ return (&(*lit) + &(*rit)); }
};


#endif