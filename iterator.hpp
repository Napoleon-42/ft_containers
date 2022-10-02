/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:02:00 by lnelson           #+#    #+#             */
/*   Updated: 2022/10/02 18:44:07 by lnelson          ###   ########.fr       */
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
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};
	
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
			random_access_iterator(const random_access_iterator<U> & it) { _ptr = it.base(); }
			~random_access_iterator() {}

			pointer	base() const { return (_ptr); }

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
	random_access_iterator<T>		operator+(typename random_access_iterator<T>::difference_type n, random_access_iterator<T> it) { return random_access_iterator<T>(it + n); }
	template <class T>
	random_access_iterator<T>		operator-(typename random_access_iterator<T>::difference_type n, random_access_iterator<T> it) { return random_access_iterator<T>(it - n); }


	template <class T>
	bool	operator==(const random_access_iterator<T> & lit, const random_access_iterator<T> & rit)	{ return (&(*lit) == &(*rit)); }

	template <class T>
	bool	operator!=(const random_access_iterator<T> & lit, const random_access_iterator<T> & rit)	{ return (!(lit == rit)); }

	template <class T>
	bool	operator<(const random_access_iterator<T> & lit, const random_access_iterator<T> & rit)		{ return (lit.base() < rit.base()); }

	template <class T>
	bool	operator>(const random_access_iterator<T> & lit, const random_access_iterator<T> & rit)		{ return (lit.base() > rit.base()); }

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
	bool	operator<(const random_access_iterator<T1> & lit, const random_access_iterator<T2> & rit)	{ return (lit.base() < rit.base());	}

	template <class T1, class T2>
	bool	operator>(const random_access_iterator<T1> & lit, const random_access_iterator<T2> & rit)	{ return (lit.base() < rit.base());	}

	template <class T1, class T2>
	bool	operator>=(const random_access_iterator<T1> & lit, const random_access_iterator<T2> & rit)	{ return !(lit < rit); }

	template <class T1, class T2>
	bool	operator<=(const random_access_iterator<T1> & lit, const random_access_iterator<T2> & rit)	{ return !(lit > rit); }

	template <class T1, class T2>
	typename	random_access_iterator<T1>::difference_type operator-(const random_access_iterator<T1>& lit, const random_access_iterator<T2>& rit)	{ return (lit.base() - rit.base()); }

	template <class T1, class T2>
	typename	random_access_iterator<T1>::difference_type operator+(const random_access_iterator<T1>& lit, const random_access_iterator<T2>& rit)	{ return (lit.base() + rit.base()); }
	

	
	// REVERSE ITERATOR

	
	template<class iter>
	class reverse_iterator
	{
		public:

			typedef typename iter::value_type			value_type;
			typedef typename iter::iterator_category	iterator_type;
			typedef typename iter::difference_type		difference_type;
			typedef typename iter::reference			reference;
			typedef typename iter::pointer				pointer;

		private:

			iter intern_it;
		
		public:

			reverse_iterator() : intern_it (NULL) {}

			explicit reverse_iterator(iter it) : intern_it (it) {}

			template <class U>
			reverse_iterator(const reverse_iterator<U> & it) { intern_it = it.base(); }
			
			~reverse_iterator() {}

			template <class U>
			reverse_iterator&		operator= (const reverse_iterator<U> & it) { intern_it = it.base(); return (*this); }

			iter					base() const { return (intern_it); }

			reference					operator[](difference_type n) 	{ return (*(intern_it + n)); }
			reference 					operator* () const 				{ return (*intern_it); }
			iter						operator->() const 				{ return (intern_it);}



			reverse_iterator&		operator++() 		{ intern_it--; return (*this); }
			reverse_iterator&		operator--()		{ intern_it++; return (*this); }
			reverse_iterator			operator++(int) 	{ reverse_iterator tmp = *this; intern_it--; return (tmp); }
			reverse_iterator			operator--(int) 	{ reverse_iterator tmp = *this; intern_it++; return (tmp); }



			reverse_iterator			operator+(difference_type n) const { reverse_iterator tmp = *this; tmp -= n; return (tmp); }
			reverse_iterator			operator-(difference_type n) const { reverse_iterator tmp = *this; tmp += n; return (tmp); }



			reverse_iterator			operator+=(difference_type n) 		{ intern_it -= n; return (*this); }
			reverse_iterator			operator-=(difference_type n) 		{ intern_it += n; return (*this); }

	};

	template <class T>
	reverse_iterator<T>		operator+(typename reverse_iterator<T>::difference_type n, reverse_iterator<T> it) { return reverse_iterator<T>(it - n); }
	template <class T>
	reverse_iterator<T>		operator-(typename reverse_iterator<T>::difference_type n, reverse_iterator<T> it) { return reverse_iterator<T>(it + n); }


	template <class T>
	bool	operator==(const reverse_iterator<T> & lit, const reverse_iterator<T> & rit)	{ return (&(*lit) == &(*rit)); }

	template <class T>
	bool	operator!=(const reverse_iterator<T> & lit, const reverse_iterator<T> & rit)	{ return (!(lit == rit)); }

	template <class T>
	bool	operator<(const reverse_iterator<T> & lit, const reverse_iterator<T> & rit)		{ return (lit.base() < rit.base()); }

	template <class T>
	bool	operator>(const reverse_iterator<T> & lit, const reverse_iterator<T> & rit)		{ return (lit.base() > rit.base()); }

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



	template<class T>
	class map_iterator : public iterator<bidirectional_iterator_tag, T>
	{
		public:
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::value_type			value_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::iterator_category		iterator_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::difference_type		difference_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::reference				reference;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::pointer				pointer;

		private:
			
			pointer *_node_ptr;

			void			increment() 
			{

			}

			void			decrement() 
			{

			}

		public:
		
			map_iterator() 								: _node_ptr(NULL) {}

			explicit
			map_iterator(pointer  node_ptr) 			: _node_ptr(node_ptr) {}

			template<class U>
			map_iterator(const map_iterator<U> & it)	{ _node_ptr = it.base(); }

			~map_iterator() {};


			pointer base() const { return (_node_ptr); }


			template<class U>
			map_iterator<T>	operator= (const map_iterator<U> & it) { _node_ptr = it.base(); return (*this); }

			reference		operator*() const		{ return (_node_ptr->_value); 		}
			pointer			operator->() const		{ return (&(_node_ptr->_value));	}

			map_iterator<T>&	operator++()		{ increment(); return (*this);	}
			map_iterator<T>&	operator--()		{ decrement(); return (*this);	}
			map_iterator<T>		operator++(int)		{ map_iterator<T> tmp = *this; increment(); return tmp;	}
			map_iterator<T>		operator--(int)		{ map_iterator<T> tmp = *this; decrement(); return tmp;	}
					
	};
};


#endif