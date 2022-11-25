/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 13:58:21 by lnelson           #+#    #+#             */
/*   Updated: 2022/11/25 15:18:56 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

#include <memory>
#include <functional>
#include <utility>
#include <stdexcept>
#include <exception>
#include "pair.hpp"
#include "map_iterator.hpp"
#include <iostream>

namespace ft
{

	//////////////////// /////////////////////////////////////
	//////////////////    ////////////////////////////////////
	//														//
	//					MAP CLASS DEFINITION				//
	//														//
	//	Map is use an <_tree_type> (line 79) class to work	//
	//	Map::iterator and ::reverse_iterator are using 		//
	//	map_iterator templated with _tree_type::node_type & //
	//	value_type 											//
	//////////////////////////////////////////    ////////////
	/////////////////////////////////////////// //////////////
	
	template<
			class Key, 
			class T, 
			class Compare = std::less<Key>, 
			class Allocator = std::allocator<ft::pair<const Key, T> > 
			> class map
	{
        //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//
		//_______________________MEMBER_TYPES______________________//
		//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//

		public:

		typedef Key										key_type;
		typedef T										mapped_type;
		typedef pair<const key_type, mapped_type>		value_type;
		typedef Compare									key_compare;
		typedef Allocator								allocator_type;
		
		typedef std::size_t								size_type;
		typedef	std::ptrdiff_t							difference_type;
		
		typedef	typename Allocator::reference			reference;
		typedef typename Allocator::const_reference		const_reference;
		typedef	typename Allocator::pointer				pointer;
		typedef typename Allocator::const_pointer		const_pointer;
		
		class value_compare	{  										 // in C++98, it is required to inherit binary_function<value_type,value_type,bool>
		  	friend class map;
			protected:
				Compare comp;
				value_compare (Compare c) : comp(c) {}  			// constructed with map's comparison object
			public:
				typedef bool			result_type;
				typedef value_type	first_argument_type;
				typedef value_type	second_argument_type;
				bool operator() (const value_type& x, const value_type& y) const	{ return comp(x.first, y.first); }
		};
        
		protected:

		//typedef	red_black_tree<value_type, key_compare, allocator_type>			_tree_type;

		public:

		/*
		typedef	map_iterator<_tree_type::node_type, value_type>			iterator;
		typedef	map_iterator<const _tree_type::node_type, value_type>	const_iterator;
		
		typedef	//////////<_tree_type::node_type, value_type>	reverse_iterator;
		typedef //////////<_tree_type::node_type, value_type>	const_reverse_iterator;
		*/
		
		//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//
		//_______________________MAP_MEMBERS_______________________//
		//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//

        protected:

        //red_black_tree    _internal_tree;
        
		//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//
		//______________________PUBLIC_FUNCTIONS___________________//
		//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//
		
		public:
        
		//	ITERATORS

		//iterator				begin() 		{ return (_internal_tree.begin());	}
		//const_iterator			begin() const	{ return (_internal_tree.begin());	}
		//reverse_iterator		rbegin() 		{ return (_internal_tree.rbegin());	}
		//const_reverse_iterator	rbegin() const	{ return (_internal_tree.rbegin());	}
		
		//iterator				end() 			{ return (_internal_tree.end());	}
		//const_iterator			end() const		{ return (_internal_tree.end());	}
		//reverse_iterator		rend() 			{ return (_internal_tree.rend());	}
		//const_reverse_iterator	rend() const	{ return (_internal_tree.rend());	}	

		// ELEMENT ACCESS

		//mapped_type&			at(const Key& key)			{ return (search_key(key)->value.second); }
		//const mapped_type&	at(const Key& key) const	{ return (search_key(key)->value.second); }
		//mapped_type&			operator[](const Key& key)	{ return (search_key(key)->value.second); }



		//	CAPACITY

		bool		empty() const				{ return (_internal_tree.empty());		}
		size_type	size() const				{ return (_internal_tree.size());		}
		size_type	max_size() const			{ return (_internal_tree.max_size());	}



		//	MODIFIERS

		//void						clear();
		//ft::pair<iterator, bool> insert(const value_type& value);
		//std::iterator				insert(iterator hint, const value_type& value);
		//void						erase(iterator pos);
		//void						erase(iterator first, iterator last);
		//size_type					erase(const Key& key);
		//void						swap(map& other);


		// ELEMENT ACCESS		- A REFAIRE

		//mapped_type&		at(const Key& key)			{ return (search_key(key)->value.second); }
		//const mapped_type&	at(const Key& key) const	{ return (search_key(key)->value.second); }
		//mapped_type&		operator[](const Key& key)	{ return (search_key(key)->value.second); }

		
		//	OPERATIONS
 
		//size_type									count(const Key& key) const	{ };

		//iterator									find(const Key& key) const;
		//const_iterator							find(const Key& key) const;

		//ft::pair<iterator, iterator> 			equal_range(const Key& key) const;
		//ft::pair<const_iterator, const_iteratro> equal_range(const Key& key) const;
		
		//iterator									lower_bound(const Key& key) const;
		//const_iterator							lower_bound(const Key& key) const;

		//iterator									upper_bound(const Key& key) const;
		//const_iterator							upper_bound(const Key& key) const;

		//	OBSERVERS

		key_compare			key_comp() const 	{ return (_internal_tree.key_comp());		}
		map::value_compare	value_comp() const 	{ return (_internal_tree.value_comp());		}

		//	ALLOCATOR

		allocator_type		get_allocator() 	{ return (_internal_tree.get_allocator());	}
    };


	//////////////////// /////////////////////////////////////
	//////////////////    ////////////////////////////////////
	//														//
	//					NODE CLASS DEFINITION				//
	//														//
	//	Node class is a base class for all other nodes, 	//
	//	needed to implement different data structure types  //
	//														//
	//////////////////////////////////////////    ////////////
	/////////////////////////////////////////// //////////////
	
	template<class T>	class node
	{
		public:
		
		typedef T	value_type;

		protected:

		value_type	_value;
		node*		_left;
		node*		_right;
		node*		_parent;

		public:

		node() : _value(), _left(NULL), _right(NULL), _parent(NULL) {}
		node(value_type val, node* left, node* right, node* parent) : _value(val), _left(left), _right(right), _parent(parent) {}
		node(const node& other) : _value(other._value), _left(other._left), _right(other._right) {}
		
		~node() {}

		node&	operator=(const node& other)
		{
			_value = other._value;
			_left = other._left;
			_right = other._right;
			_parent = other._parent;
		}
		
		bool	operator==(const node & other)
		{
			return(other._value == this->_value &&
			other._right == this->_right && 
			other._left == this->_left);
		}

		bool	operator!=(const node & other) { return (!(*this == other)); }
	}
};


#endif