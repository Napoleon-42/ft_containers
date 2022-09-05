/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 17:18:34 by lnelson           #+#    #+#             */
/*   Updated: 2022/09/05 19:12:08 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

#include "vector.hpp"

namespace ft
{
	template <class T, class Container = ft::vector<T> > class stack
	{
		protected:

			Container	_data;
		
		public:

			typedef Container container_type;
			typedef typename Container::value_type value_type;
			typedef typename Container::size_type size_type;
			typedef typename Container::reference reference;
			typedef typename Container::const_reference const_reference;

			explicit stack(const container_type& ctnr = container_type()) : _data (ctnr) {}
			~stack() {}
			

			bool		empty() const		{ return (_data.empty()); }
			size_type	size() const		{ return (_data.size()); }
			T 			top() 				{ return (_data.back()); }
			const T		top() const			{ return (_data.back()); }
			void		push(const T& val)	{ _data.push_back(val); }
			void 		pop()				{ _data.pop_back(); }

			
			stack<T> & 		operator=(stack<T> const & var) { this->_data = var._data; return (this); }
			
			template <class U, class ContainerT>
			friend bool operator== (const stack<U,ContainerT>& lhs, const stack<U,ContainerT>& rhs);

			template <class U, class ContainerT>
			friend bool operator!= (const stack<U,ContainerT>& lhs, const stack<U,ContainerT>& rhs);

			template <class U, class ContainerT>
			friend bool operator< (const stack<U,ContainerT>& lhs, const stack<U,ContainerT>& rhs);

			template <class U, class ContainerT>
			friend bool operator<= (const stack<U,ContainerT>& lhs, const stack<U,ContainerT>& rhs);

			template <class U, class ContainerT>
			friend bool operator> (const stack<U,ContainerT>& lhs, const stack<U,ContainerT>& rhs);

			template <class U, class ContainerT>
			friend bool operator>= (const stack<U,ContainerT>& lhs, const stack<U,ContainerT>& rhs);
			
	};


	template< class T, class Container >
	bool operator==( const stack<T,Container>& lhs, const stack<T,Container>& rhs )	{ return (lhs._data == rhs._data); }

	template< class T, class Container >
	bool operator!=( const stack<T,Container>& lhs, const stack<T,Container>& rhs )	{ return (lhs._data != rhs._data); }

	template< class T, class Container >
	bool operator<( const stack<T,Container>& lhs, const stack<T,Container>& rhs ) { return (lhs._data < rhs._data); }

	template< class T, class Container >
	bool operator<=( const stack<T,Container>& lhs, const stack<T,Container>& rhs ) { return (lhs._data <= rhs._data); }

	template< class T, class Container >
	bool operator>( const stack<T,Container>& lhs, const stack<T,Container>& rhs ) { return (lhs._data > rhs._data); }

	template< class T, class Container >
	bool operator>=( const stack<T,Container>& lhs, const stack<T,Container>& rhs ) { return (lhs._data >= rhs._data); }


};

#endif