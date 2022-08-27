/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterator.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:02:00 by lnelson           #+#    #+#             */
/*   Updated: 2022/08/27 19:49:45 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ITERATOR_HPP
# define FT_ITERATOR_HPP

#include <cstddef>

namespace ft
{

	struct output_iterator_tag {};
	struct input_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag {};
	struct biderectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public biderectional_iterator_tag {};
	

	template <class Iter>
	struct iterator_traits
	{
		typedef	difference_type		Iter::difference_type;
		typedef	value_type			Iter::value_type;
		typedef	pointer				Iter::pointer;
		typedef	reference			Iter::reference;
		typedef	iterator_category	Iter::iterator_category;
	};

	template <class T>
	struct iterator_traits<T*>
	{	
		typedef difference_type		std::ptrdiff_t;
		typedef value_type			T;
		typedef pointer				T*;
		typedef reference			T&;
		typedef iterator_category	std::random_access_iterator_tag;	
	};

	template <class T>
	struct iterator_traits<const T*>
	{	
		typedef difference_type		std::ptrdiff_t;
		typedef value_type			T;
		typedef pointer				const T*;
		typedef reference			const T&;
		typedef iterator_category	std::random_access_iterator_tag;	
	};

	//	RANDOM ACCES ITERATOR


	template<class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct iterator
	{
		pubic:
			
			typedef iterator_category 	Category;
			typedef value_type			T;
			typedef difference_type 	Distance;
			typedef pointer 			Pointer;
			typedef reference 			Reference;
	};

	template<class T>
	class random_access_iterator : public iterator<random_access_iterator_tag, T>
	{
		private:

			Pointer _ptr;
		
		public:

			random_access_iterator() : _ptr = NULL;
			explicit random_access_iterator(Pointer ptr) : _ptr = ptr ;
			random_access_iterator(const random_access_iterator & it) : this = it;
			~random_access_iterator();

			reference 					operator= (const random_access_iterator & it) { _ptr = &(*it); return (*this); }



			Reference					operator[](difference_type n) 	{ return (*(_ptr + n)); }
			reference 					operator* () const 				{ return (*_ptr); }
			pointer						operator->() const 				{ return (_ptr);}



			random_access_iterator<T>&	operator++() 		{ _ptr++; return (*this); }
			random_access_iterator<T>&	operator--()		{ _ptr--; return (*this); }
			random_access_iterator<T>	operator++(int) 	{ random_access_iterator tmp = *this; _ptr++; return (tmp); }
			random_access_iterator<T>	operator--(int) 	{ random_access_iterator tmp = *this; _ptr--; return (tmp); }



			random_access_iterator		operator+(difference_type n) const { random_access_iterator tmp = *this; tmp += n; return (tmp); }
			random_access_iterator		operator-(difference_type n) const { random_access_iterator tmp = *this; tmp -= n; return (tmp); }



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

	
	// REVERSE ITERATOR

	
	template<class T>
	class reverse_iterator : public iterator<random_access_iterator_tag, T>
	{
		private:

			Pointer _ptr;
		
		public:

			reverse_iterator() : _ptr = NULL;
			reverse_iterator(const reverse_iterator & it) : this = it;
			~reverse_iterator();

			reference 					operator= (const reverse_iterator & it) { _ptr = &(*it); return (*this); }



			Reference					operator[](difference_type n) 	{ return (*(_ptr + n)); }
			reference 					operator* () const 				{ return (*_ptr); }
			pointer						operator->() const 				{ return (_ptr);}



			reverse_iterator<T>&	operator++() 		{ _ptr++; return (*this); }
			reverse_iterator<T>&	operator--()		{ _ptr--; return (*this); }
			reverse_iterator<T>	operator++(int) 	{ reverse_iterator tmp = *this; _ptr++; return (tmp); }
			reverse_iterator<T>	operator--(int) 	{ reverse_iterator tmp = *this; _ptr--; return (tmp); }



			reverse_iterator		operator+(difference_type n) const { reverse_iterator tmp = *this; tmp += n; return (tmp); }
			reverse_iterator		operator-(difference_type n) const { reverse_iterator tmp = *this; tmp -= n; return (tmp); }



			reverse_iterator		operator+=(difference_type n) 		{ _ptr += n; return (*this); }
			reverse_iterator		operator-=(difference_type n) 		{ _ptr -= n; return (*this); }

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

};


#endif