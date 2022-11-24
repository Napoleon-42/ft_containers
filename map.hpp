/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 20:01:04 by lnelson           #+#    #+#             */
/*   Updated: 2022/11/25 00:11:03 by lnelson          ###   ########.fr       */
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

		typedef	map_iterator<node<value_type> >			iterator;
		typedef	map_iterator<const node<value_type> >	const_iterator;

		/*
		typedef										reverse_iterator;
		typedef 									const_reverse_iterator;
		*/
		
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

		private:

		//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//
		//_______________________MAP_MEMBERS_______________________//
		//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//

		typedef	typename allocator_type:: template rebind<node<value_type> >::other node_allocator;

		node<value_type>	_null_node;
		key_compare			_keycomp;
		allocator_type		_allocator;
		node_allocator		_node_allocator;
		size_type			_size;
		node<value_type>	*_root;


		//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//
		//______________________PRIVATE_FUNCTIONS__________________//
		//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//

		node<value_type>&	createNode(node<value_type> nNode) 
		{
			node<value_type> *ret = _node_allocator.allocate(1);
			_node_allocator.construct(ret, nNode);
			return (*ret);
		}

		node<value_type>*	search_key(const Key& key) const
		{
			node<value_type>* tmp_node = _root;

			while(tmp_node->_value.first != key && tmp_node != &_null_node)
			{
				if (_keycomp(key, tmp_node->_value.first))
					tmp_node = tmp_node->_left;
				else
					tmp_node = tmp_node->_right;
			}
			
			return (tmp_node);
		}
		
		void	left_rotate(node<value_type> & x)
		{
			node<value_type>& y = *x._right;						// Y is the X->left_node

			y._parent = x._parent;					// Changing Y.parent by X.parent

			if (x._parent == &_null_node)			// Changing parent's child node, depending on where X where
				_root = x._right;
			else if (x == *(x._parent->_right))
				x._parent->_right = &y;
			else
				x._parent->_left = &y;
			
			x._right = y._left;						// Changing X.right, to Y.left

			x._right->_parent = &x;					// Changing X.new_right_parent to X

			y._left = &x;							// Changing Y.left to X

			x._parent = &y;							// Changing X.parent to Y
		}

		void	right_rotate(node<value_type> & x)
		{
			node<value_type>& y = *x._left;						// Y is the X->right_node

			y._parent = x._parent;					// Changing Y.parent by X.parent

			if (x._parent == &_null_node)			// Changing parent's child node, depending on where X where
				_root = x._right;
			else if (x == *(x._parent->_right))
				x._parent->_right = &y;
			else
				x._parent->_left = &y;		
			
			x._left = y._right;						// Changing X.left, to Y.right

			x._left->_parent = &x;					// Changing X.new_left_parent to X

			y._right = &x;							// Changing Y.right to X

			x._parent = &y;							// Changing X.parent to Y
		}


		//						INSERT FIXUP
		void	insertFixUp(node<value_type> * newNode)
		{
			while (newNode->_parent->_red == RED)
			{
				if (newNode->_parent == newNode->_parent->_parent->_right)
				{
						if (newNode->_parent->_parent->_left->_red == RED) // CHANGING THE UNCLE AND PARENT TO BLACK, GP AND NEW TO RED
						{
							newNode->_parent->_parent->_left->changeColor();
							newNode->_parent->changeColor();
							newNode->_parent->_parent->changeColor();
						}
						else										//	PUSHING THE NODE, BY ROTATING AT GRANDPARENT 
						{	
							if (newNode == newNode->_parent->_left)			// ALLING ON THE RIGHT BRANCHING
							{
								newNode = newNode->_parent;
								left_rotate(*newNode);
							}
							newNode->_parent->changeColor();
							newNode->_parent->_parent->changeColor();
							right_rotate(*(newNode->_parent->_parent));
						}
				}
				
				
				// THE ALGO BELLOW IS STRICLY THE SAME, FROM AN OTHER PARENT/GP, POS'S.
				else
				{
						if (newNode->_parent->_parent->_right->_red == RED) // CHANGING THE UNCLE AND PARENT TO BLACK, GP AND NEW TO RED
						{
							newNode->_parent->_parent->_right->changeColor();
							newNode->_parent->changeColor();
							newNode->_parent->_parent->changeColor();
						}
						else										//	PUSHING THE NODE, BY ROTATING AT GRANDPARENT 
						{	
							if (newNode == newNode->_parent->_right)			// ALLING ON THE RIGHT BRANCHING
							{
								newNode = newNode->_parent;
								right_rotate(*newNode);
							}
							newNode->_parent->changeColor();
							newNode->_parent->_parent->changeColor();
							left_rotate(*(newNode->_parent->_parent));
						}
						
				}
			}
			if (_root == newNode)									// SETTING ROOT TO BLACK
				_root->changeColor();
		}


		//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//
		//______________________PUBLIC_FUNCTIONS___________________//
		//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//
		
		public:

		map(const map& other):
		_null_node(createNode(node<value_type>(BLACK))),
		_keycomp(other.get_key()),
		_allocator(other.get_allocator()),
		_node_allocator(other._node_allocator),
		_size(0),
		_root(&_null_node)
		{
			// insert(other.begin(), other.last());
		};
		

		explicit map(const key_compare& comp = key_compare(), const Allocator& alloc = allocator_type()) :
		_null_node(createNode(node<value_type>(BLACK))),
		_keycomp(comp),
		_allocator(alloc),
		_node_allocator(node_allocator()),
		_size(0),
		_root(&_null_node)
		{};
/*		
		template<class InputIt>
		map(InputIt first, InputIt last, const Allocator& alloc = Allocator()) : _allocator(alloc)
		{
		}
*/

		// ELEMENT ACCESS		- A REFAIRE

		//mapped_type&		at(const Key& key)			{ return (search_key(key)->value.second); }
		//const mapped_type&	at(const Key& key) const	{ return (search_key(key)->value.second); }
		//mapped_type&		operator[](const Key& key)	{ return (search_key(key)->value.second); }



		//	CAPACITY

		bool		empty() const				{ return (_size == 0); 				}
		size_type	size() const				{ return (_size); 					}
		size_type	max_size() const			{ return (_allocator.max_size());	}



		//	MODIFIERS

		//void						clear();

		ft::pair<iterator, bool> insert(const value_type& value)
		{
			if (search_key(value.first) != &_null_node)
				return	(
					ft::make_pair(
						iterator(search_key(value.first)),
						false)
						);

			//						NEW NODE ALLOCAION AND INSERTION			
			
			node<value_type>* tmp = _root;
			if (_root == &_null_node) 
				{_root = &createNode(node<value_type>(value, &_null_node, &_null_node, tmp, RED)); tmp = _root;}
			else		
				while (1)
				{
					if (_keycomp(value.first, tmp->_value.first))
					{
						if (tmp->_left != &_null_node)
							tmp = tmp->_left;
						else
						{
							tmp->_left = &createNode(node<value_type>(value, &_null_node, &_null_node, tmp, RED));
							tmp = tmp->_left;
							break;
						}
					}
					else
					{
						if (tmp->_right != &_null_node)
							tmp = tmp->_right;
						else
						{
							tmp->_right = &createNode(node<value_type>(value, &_null_node, &_null_node, tmp, RED));
							tmp = tmp->_right;
							break;
						}
					}
				}
			_size++;
			//
			//	create a node with 'createNode' left|right|_root possisions.
			//	also allocate the node, and give it a parent node or _null_node (for first).
			//	node * tmp - point to the newly created node.
			//
			//
													// TEST :
													if (value.first != tmp->_value.first)
														throw std::exception();
			//
			

			insertFixUp(tmp);
			return (ft::make_pair(iterator(tmp), true));
		}

		
		//std::iterator				insert(iterator hint, const value_type& value);
		//void						erase(iterator pos);
		//void						erase(iterator first, iterator last);
		//size_type					erase(const Key& key);
		//void						swap(map& other);



		//	LOOKUP
 
		size_type									count(const Key& key) const	{ return (search_key(key) == &_null_node ? 0 : 1); }

		//iterator									find(const Key& key) const;
		//const_iterator							find(const Key& key) const;

		//ft::pair<iterator, iterator> 			equal_range(const Key& key) const;
		//ft::pair<const_iterator, const_iteratro> equal_range(const Key& key) const;
		
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