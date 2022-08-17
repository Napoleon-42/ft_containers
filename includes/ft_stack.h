/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 17:18:34 by lnelson           #+#    #+#             */
/*   Updated: 2022/08/16 18:01:52 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STACK
# define FT_STACK

#include "ft_containers.h"

namespace ft
{
	template <class T, class Container = std::vector<T> > class stack
	{
		private:

			typedef container_type Container;
			typedef value_type Container::value_type;
			typedef size_type Container::size_type;
			typedef reference Container::reference;
			typedef const_reference Container::const_reference;

			Container<T>	data;
		
		public:

			stack(const container_type& ctnr = container_type);
			~stack();

			bool empty(){
				return (data.empty);
			}

			size_type size(){
				return (data.size());
			}

			T top(){
				return (data.back());
			}

			const	T top() const{
				return (data.back());
			}

			void	push(T& val){
				data.pushback(val);
			}

			void pop(){
				data.pop_back();
			}

			stack<T> & 		operator=(stack<T> const & var){
				
			}
	};

/*	
	template< class T, class Container >
	bool operator==( const stack<T,Container>& lhs, const stack<T,Container>& rhs )
	{
		if (lhs.size() != rhs.size())
			return (false);
		else
	}

	template< class T, class Container >
	bool operator!=( const stack<T,Container>& lhs, const stack<T,Container>& rhs )
	{

	}
*/

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