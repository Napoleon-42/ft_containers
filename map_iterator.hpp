/* ************************************************************************** */
/*                                                                    */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 14:22:00 by lnelson           #+#    #+#             */
/*   Updated: 2022/11/25 14:46:09 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

#include "map.hpp"
#include "iterator.hpp"


//////////////////// /////////////////////////////////////
//////////////////    ////////////////////////////////////
//														//
//			MAP_ITERATOR CLASS DEFINITION				//
//														//
//	map_iterator take as template the underlying node, 	//
//	and the value type, no need to change this class to //
//	work with other types of underlying trees for map 	//
//														//
//////////////////////////////////////////    ////////////
/////////////////////////////////////////// //////////////

namespace ft
{
	template<class Node, class T>
	class map_iterator : public iterator<bidirectional_iterator_tag, Node>
	{
		public:
	
		typedef T																				value_type;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, Node>::value_type			node_type;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, Node>::iterator_category  iterator_type;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, Node>::difference_type	difference_type;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, Node>::reference			reference;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, Node>::pointer			pointer;

		protected:

		pointer _node;

		void			increment() 
		{
			if (_node->_right)
			{
				_node = _node->_right;
				while (_node->_left)
					_node = _node->_left;
			}
		 	else
			{
				pointer tmp = _node;
				_node = _node->_parent;
				while (_node->_left != tmp)
				{
					tmp = _node;
					_node = _node->_parent;
				}
			}
		}

		void			decrement() 
		{
			if (_node->_left)
			{
				_node = _node->_left;
				while (_node->_right)
					_node = _node->_right;
			}
			else
			{
				pointer tmp = _node;
				_node = _node->_parent;
				while (_node->_right != tmp)
				{
					tmp = _node;
					_node = _node->_parent;
				}
			}
		}

		public:

		map_iterator() 							: _node(NULL) 		{}
		map_iterator(pointer  node_ptr) 		: _node(node_ptr)	{}
		map_iterator(const map_iterator & it)	: _node(it.base())	{}	
		~map_iterator () {}

		map_iterator&	operator=(const map_iterator & it) { _node = it._node; return (*this); }

		pointer base() const {return (_node); }

		value_type	operator*() const	{ return (_node->value);	}
		value_type*	operator->() const	{ return (&(_node->value));	}

		map_iterator&	operator++()		{ increment(); return (*this);	}
		map_iterator&	operator--()		{ decrement(); return (*this);	}
		map_iterator	operator++(int)		{ map_iterator tmp = *this; increment(); return tmp;	}
		map_iterator	operator--(int)		{ map_iterator tmp = *this; decrement(); return tmp;	}
	};
	
	template <class Node, class T>
	bool	operator==(const map_iterator<Node, T> & lit, const map_iterator<Node, T> & rit)	{ return (lit.base() == rit.base()); }

	template <class Node, class T>
	bool	operator!=(const map_iterator<Node, T> & lit, const map_iterator<Node, T> & rit)	{ return (!(lit == rit)); }

};


#endif