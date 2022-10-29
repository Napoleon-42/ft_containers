/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 19:34:19 by lnelson           #+#    #+#             */
/*   Updated: 2022/10/29 19:36:04 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

#include "map.hpp"
#include "iterator.hpp"

namespace ft
{
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
			
			node* _node_ptr;

			void			increment() 
			{
				
			}

			void			decrement() 
			{

			}

		public:
		
			map_iterator() 								: _node_ptr(NULL) {}

			explicit
			map_iterator(node*  node_ptr) 			: _node_ptr(node_ptr) {}

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