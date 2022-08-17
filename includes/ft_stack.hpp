/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 17:18:34 by lnelson           #+#    #+#             */
/*   Updated: 2022/08/17 16:29:28 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STACK_HPP
# define FT_STACK_HPP

#include "ft_containers.hpp"

namespace ft
{
	template <class T, class Container = std::vector<T> > class stack
	{
		protected:

			Container	data;
		
		public:

			typedef Container container_type;
			typedef typename Container::value_type value_type;
			typedef typename Container::size_type size_type;
			typedef typename Container::reference reference;
			typedef typename Container::const_reference const_reference;

			explicit stack(const container_type& ctnr = container_type()) {};
			

			bool		empty() const		{ return (data.empty); }
			size_type	size() const		{ return (data.size()); }
			T 			top() 				{ return (data.back()); }
			const T		top() const			{ return (data.back()); }
			void		push(T& val)		{ data.push_back(val); }
			void 		pop()				{ data.pop_back(); }

			/*
			stack<T> & 		operator=(stack<T> const & var){
				
			}
			*/
	};


	template< class T, class Container >
	bool operator==( const stack<T,Container>& lhs, const stack<T,Container>& rhs )
	{
		if (lhs.size() != rhs.size())
			return (false);
		else		
		{	
			typename Container::iterator lite = lhs.end();
			typename Container::iterator lit = lhs.begin();

			typename Container::iterator rite = rhs.end();
			typename Container::iterator rit = rhs.begin();

			while ((lhs.size() > rhs.size() ? (lit != lite) : (rit != rite) ))
			{
				if (*rit != *lit)
					return (false);				
				lit++;
				rit++;
			}
		}
		return (true);
	}

	template< class T, class Container >
	bool operator!=( const stack<T,Container>& lhs, const stack<T,Container>& rhs )
	{
		if (lhs.size() != rhs.size())
			return (true);
		else
		{
			
			typename Container::iterator lite = lhs.end();
			typename Container::iterator lit = lhs.begin();

			typename Container::iterator rite = rhs.end();
			typename Container::iterator rit = rhs.begin();

			while (rit != rite)
			{
				if (*rit != *lit)
					return (true);
				lit++;
				rit++;
			}
		}
		return (false);
	}


	template< class T, class Container >
	bool operator<( const stack<T,Container>& lhs, const stack<T,Container>& rhs )
	{
		if (lhs.size() < rhs.size())
			return (true);
		return (false);
	}

	template< class T, class Container >
	bool operator<=( const stack<T,Container>& lhs, const stack<T,Container>& rhs )
	{
		if (lhs.size() <= rhs.size())
			return (true);
		return (false);
	}

	template< class T, class Container >
	bool operator>( const stack<T,Container>& lhs, const stack<T,Container>& rhs )
	{
		if (lhs.size() > rhs.size())
			return (true);
		return (false);
	}

	template< class T, class Container >
	bool operator>=( const stack<T,Container>& lhs, const stack<T,Container>& rhs )
	{
		if (lhs.size() >= rhs.size())
			return (true);
		return (false);
	}


};

#endif