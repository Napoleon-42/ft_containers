/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iteratorOld.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 19:34:19 by lnelson           #+#    #+#             */
/*   Updated: 2022/12/06 15:33:19 by lnelson          ###   ########.fr       */
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

		node() : _value(), _left(NULL), _right(NULL), _parent(NULL), _red(RED) { /*std::cout << "Created new node:\nleft= " << _left << "\nright=" << _right << "\nparent=" << _parent << std::endl; */}
		node(bool color) : _red(color)  {/*std::cout << "Created new node:\nleft= " << _left << "\nright=" << _right << "\nparent=" << _parent << std::endl;*/ }
		node(value_type val, node* left, node* right, node* parent) : _value(val), _left(left), _right(right), _parent(parent), _red(RED)  { /* std::cout << "Created new node:\nleft= " << _left << "\nright=" << _right << "\nparent=" << _parent << std::endl; */ }
		node(value_type val, node* left, node* right, node* parent, bool color) : _value(val), _left(left), _right(right), _parent(parent), _red(color)  { /* std::cout << "Created new node:\nleft= " << _left << "\nright=" << _right << "\nparent=" << _parent << std::endl; */ } 
		node(const node& val) : _value(val._value), _left(val._left), _right(val._right), _parent(val._parent), _red(val._red)  { /* std::cout << "Created new node:\nleft= " << _left << "\nright=" << _right << "\nparent=" << _parent << std::endl; */ }

		~node() {}

		void	changeColor() { _red = !_red; }

		bool	operator==(const node & val)	{return(val._value == this->_value &&
													val._right == this->_right && 
													val._left == this->_left && 
													val._red == this->_red);}
		node&	operator=(const node& Nnode)
		{
			//_value = Nnode._value;
			_left = Nnode._left;
			_right = Nnode._right;
			_parent = Nnode._parent;
			_red = Nnode._red;
			return (*this);
		}

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

			bool			is_null_node(pointer tested)
			{
				if(tested->_left == NULL || tested->_right == NULL || tested->_parent == NULL)
					return (true);
				return (false);
			}

			void			increment() 
			{
				//if (is_null_node(_node_ptr->_right) && is_null_node(_node_ptr->_left) && _node_ptr == _node_ptr->_parent->_right)
				//	_node_ptr = _node_ptr->_right;
				if (!is_null_node(_node_ptr->_right))
				{
					_node_ptr = _node_ptr->_right;
					while (!is_null_node(_node_ptr->_left))
						_node_ptr = _node_ptr->_left;
				}
			 	else
				{
					pointer tmp = _node_ptr;
					_node_ptr = _node_ptr->_parent;
					while (_node_ptr->_left != tmp)
					{
						tmp = _node_ptr;
						_node_ptr = _node_ptr->_parent;
					}
				}
			}

			void			decrement() 
			{
				if (!is_null_node(_node_ptr->_left))
				{
					_node_ptr = _node_ptr->_left;
					while (!is_null_node(_node_ptr->_right))
						_node_ptr = _node_ptr->_right;
				}
				else
				{
					pointer tmp = _node_ptr;
					_node_ptr = _node_ptr->_parent;
					while (_node_ptr->_right != tmp)
					{
						tmp = _node_ptr;
						_node_ptr = _node_ptr->_parent;
					}
				}
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
	
	template <class T>
	map_iterator<T>		operator+(typename map_iterator<T>::difference_type n, map_iterator<T> it) { for(unsigned int i = 0; i < n ; i++) it++; return (it); }
	template <class T>
	map_iterator<T>		operator-(typename map_iterator<T>::difference_type n, map_iterator<T> it) { for(unsigned int i = 0; i < n ; i++) it--; return (it); }

};

#endif