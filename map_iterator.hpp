/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 19:34:19 by lnelson           #+#    #+#             */
/*   Updated: 2022/11/25 01:06:18 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

#include "map.hpp"
#include "iterator.hpp"

#define RED true
#define BLACK false

namespace ft
{	
	template<class T>	class node
	{

		public:

		typedef	T				value_type;

		value_type				_value;
		node*					_left;
		node*					_right;
		node*					_parent;
		bool					_red;

		node() : _value(), _left(NULL), _right(NULL), _parent(NULL), _red(RED) {}
		node(bool color) : _red(color) {}
		node(value_type val, node* left, node* right, node* parent) : _value(val), _left(left), _right(right), _parent(parent), _red(RED) {}
		node(value_type val, node* left, node* right, node* parent, bool color) : _value(val), _left(left), _right(right), _parent(parent), _red(color) {} 
		node(const node& val) : _value(val._value), _left(val._left), _right(val._right), _parent(val._parent), _red(val._red) {}

		~node() {}

		void	changeColor() { _red = !_red; }
			
		bool	operator==(const node & val)	{return(val._value == this->_value &&
													val._right == this->_right && 
													val._left == this->_left && 
													val._red == this->_red);	}

		};
		
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
			
			pointer _node_ptr;

			void			increment() 
			{
				
			}

			void			decrement() 
			{

			}

		public:
		
			map_iterator() 								: _node_ptr(NULL) {}

			map_iterator(pointer  node_ptr) 			: _node_ptr(node_ptr) {}

			template<class U>
			map_iterator(const map_iterator<U> & it)	{ _node_ptr = it.base(); }

			~map_iterator() {};


			pointer base() const { return (_node_ptr); }


			template<class U>
			map_iterator<T>	operator= (const map_iterator<U> & it) { _node_ptr = it.base(); return (*this); }

			typename value_type::value_type		operator*() const		{ return (_node_ptr->_value); 		}
			typename value_type::value_type*		operator->() const		{ return (&(_node_ptr->_value));	}

			map_iterator<T>&	operator++()		{ increment(); return (*this);	}
			map_iterator<T>&	operator--()		{ decrement(); return (*this);	}
			map_iterator<T>		operator++(int)		{ map_iterator<T> tmp = *this; increment(); return tmp;	}
			map_iterator<T>		operator--(int)		{ map_iterator<T> tmp = *this; decrement(); return tmp;	}
					
	};
};

#endif