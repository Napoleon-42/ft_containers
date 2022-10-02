/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 20:01:04 by lnelson           #+#    #+#             */
/*   Updated: 2022/10/02 19:26:56 by lnelson          ###   ########.fr       */
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
#include "iterator.hpp"
#include <iostream>

#define RED		true
#define BLACK	false

namespace ft
{
	template<
			class Key, 
			class T, 
			class Compare = std::less<Key>, 
			class Allocator = std::allocator<ft::pair<const Key, T> > 
			> class map
	{
		public:

		typedef Key									key_type;
		typedef T									mapped_type;
		typedef pair<const key_type, mapped_type>	value_type;
		typedef Compare								key_compare;
		typedef Allocator							allocator_type;
		
		typedef std::size_t							size_type;
		typedef	std::ptrdiff_t						difference_type;
		
		typedef	typename Allocator::reference		reference;
		typedef typename Allocator::const_reference	const_reference;
		typedef	typename Allocator::pointer			pointer;
		typedef typename Allocator::const_pointer	const_pointer;


		class value_compare	{  																		 // in C++98, it is required to inherit binary_function<value_type,value_type,bool>
		  	friend class map;
			protected:
				Compare comp;
				value_compare (Compare c) : comp(c) {}  							// constructed with map's comparison object
			public:
				typedef bool			result_type;
				typedef value_type	first_argument_type;
				typedef value_type	second_argument_type;
				bool operator() (const value_type& x, const value_type& y) const	{ return comp(x.first, y.first); }
		};

	
		typedef	map_iterator<value_type>			iterator;
		typedef	map_iterator<const value_type>		const_iterator;

		/*
		typedef										reverse_iterator;
		typedef 									const_reverse_iterator;
		*/

		private:

		//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//
		//_______________________NODE_CLASS________________________//
		//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//

		class node
		{

			public:


			value_type				_value;
			node*					_left;
			node*					_right;
			node*					_parent;
			std::allocator<node>	_node_allocator;
			bool					_red;

			node() : _value(), _left(NULL), _right(NULL), _parent(NULL), _red(RED) {}
			node(bool color) : _red(color) {}
			node(value_type val, node* left, node* right, node* parent) : _value(val), _left(left), _right(right), _parent(parent), _red(RED) {} 
			node(const node& val) : _value(val._value), _left(val._left), _right(val._right), _parent(val._parent), _red(val._red) {}
			~node() {}

			friend class map_iterator<value_type>;
		};


		//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//
		//_______________________MAP_MEMBERS_______________________//
		//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//

		node				*_root;
		key_compare			_keycomp;
		allocator_type		_allocator;
		size_type			_size;
		node				_null_node;


		//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//
		//______________________PRIVATE_FUNCTIONS__________________//
		//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//

		node&	search_key(const Key& key) const
		{
			node* tmp_node = _root;

			while(tmp_node->_value.first != key && tmp_node != &_null_node)
			{
				if (_keycomp(key, tmp_node->_value.first))
					tmp_node = tmp_node->_left;
				else
					tmp_node = tmp_node->_right;
			}
			
			return ((*tmp_node));
		}
		
		void	left_rotate(node & x)
		{
			node& y = x._right;						// Y is the X->left_node

			y._parent = x._parent;					// Changing Y.parent by X.parent

			if (x._parent == _null_node)			// Changing parent's child node, depending on where X where
				_root = &(x._right);
			else if (x == *(x._parent._right))
				x._parent._right = y;
			else
				x._parent._left = y;		
			
			x._right = y._left;						// Changing X.right, to Y.left

			x._right.parent = x;					// Changing X.new_right_parent to X

			y._left = x;							// Changing Y.left to X

			x._parent = y;							// Changing X.parent to Y
		}

		void	right_rotate(node & x)
		{
			node& y = x._left;						// Y is the X->right_node

			y._parent = x._parent;					// Changing Y.parent by X.parent

			if (x._parent == _null_node)			// Changing parent's child node, depending on where X where
				_root = &(x._right);
			else if (x == *(x._parent._right))
				x._parent._right = y;
			else
				x._parent._left = y;		
			
			x._left = y._right;						// Changing X.left, to Y.right

			x._left.parent = x;						// Changing X.new_left_parent to X

			y._right = x;							// Changing Y.right to X

			x._parent = y;							// Changing X.parent to Y
		}


		void	changeColor(node & node) { node._red = !node._red; }

		// we have 3 main cases:
		//	1. ROOT == NULL -> new node become BLACK and root
		//  2. everything is alright, we do nothing
		//  3. new_node and their
		void	insertFixUp(node & newNode)
		{
			node &parent = newNode._parent;
			node &grandParent = parent._parent;
			node &uncle = (parent == grandParent._left ? grandParent._right : grandParent._left);

			if (newNode._red == RED && newNode._parent->_red == RED) // two concecutive red-nodes
			{
				(void) newNode;
			}
		}


		//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//
		//______________________PUBLIC_FUNCTIONS___________________//
		//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//
		public:

		map(const map& other)
		{
			_root = &_null_node;
			_keycomp = other.key_comp();
			_size = other.size();
			_null_node = node();
			_allocator = other.get_allocator();
			//insert(other.begin(), other.first());
			(void) other;
		}

		explicit map(const key_compare& comp = key_compare(), const Allocator& alloc = allocator_type()) :
		_keycomp(comp),
		_allocator(alloc),
		_size(0),
		_null_node(node()) 
		{
			_root = &_null_node;
		}

/*		
		template<class InputIt>
		map(InputIt first, InputIt last, const Allocator& alloc = Allocator()) : _allocator(alloc)
		{
		}
*/

		// ELEMENT ACCESS

		mapped_type&		at(const Key& key)			{ return (search_key(key)->value.second); }
		const mapped_type&	at(const Key& key) const	{ return (search_key(key)->value.second); }
		mapped_type&		operator[](const Key& key)	{ return (search_key(key)->value.second); }



		//	CAPACITY

		bool		empty() const				{ return (_size == 0); 				}
		size_type	size() const				{ return (_size); 					}
		size_type	max_size() const			{ return (_allocator.max_size());	}



		//	MODIFIERS

		//void						clear();

		std::pair<iterator, bool> insert(const value_type& value)
		{
			if (count(value.first))																		//	KEY already exist in the map
				return (*(search_key(value.first)));

			if (_root == &_null_node)																	// The map was empty
			{
				_root = _allocator.allocate(1);
				_allocator.construct(node(value, _null_node, _null_node, _null_node, BLACK), _root);
				return (*_root);
			}

			node 	*x = _root;
			node	*y = &_null_node;
			while (x != _null_node)
			{
				y = x;
				if (key_compare(value.first, x->value.first))
					x = x->_left;
				else
					x = x->_right;
			}
	
			node *tmp_node = _allocator.allocate(1);
			_allocator.construct(node(value, _null_node, _null_node, y, RED));
			if (key_compare(tmp_node->value.first, y->value.first))
				y->_left = tmp_node;
			else
				y->_right = tmp_node;

			return (tmp_node);
		}
		
		//std::iterator				insert(iterator hint, const value_type& value);
		//void						erase(iterator pos);
		//void						erase(iterator first, iterator last);
		//size_type					erase(const Key& key);
		//void						swap(map& other);



		//	LOOKUP
 
		size_type									count(const Key& key) const	{ return (search_key(key) == _null_node ? 0 : 1); }

		//iterator									find(const Key& key) const;
		//const_iterator							find(const Key& key) const;

		//std::pair<iterator, iterator> 			equal_range(const Key& key) const;
		//std::pair<const_iterator, const_iteratro> equal_range(const Key& key) const;
		
		//iterator									lower_bound(const Key& key) const;
		//const_iterator							lower_bound(const Key& key) const;

		//iterator									upper_bound(const Key& key) const;
		//const_iterator							upper_bound(const Key& key) const;



		//	OBSERVERS

		key_compare			key_comp() const 	{ return (_keycomp); 					}
		map::value_compare	value_comp() const 	{ return (value_compare(key_compare())); 	}

		//	ALLOCATOR

		allocator_type		get_allocator() 	{ return (_allocator); 						}


	};
};

#endif