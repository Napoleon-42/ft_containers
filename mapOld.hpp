/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapOld.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 20:01:04 by lnelson           #+#    #+#             */
/*   Updated: 2022/12/06 16:05:41 by lnelson          ###   ########.fr       */
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

		key_compare			_keycomp;
		allocator_type		_allocator;
		node_allocator		_node_allocator;
		node<value_type>	_null_node;
		size_type			_size;
		node<value_type>	*_root;


		//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//
		//______________________PUBLIC_FUNCTIONS___________________//
		//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//
		
		public:

		map(const map& other):
		_keycomp(other.get_key()),
		_allocator(other.get_allocator()),
		_node_allocator(other._node_allocator),
		_size(0),
		_root(&_null_node)
		{
			//insert(other.begin(), other.end());
		}
		

		explicit map(const key_compare& comp = key_compare(), const Allocator& alloc = allocator_type()) :
		_keycomp(comp),
		_allocator(alloc),
		_node_allocator(node_allocator()),
		_size(0),
		_root(&_null_node)
		{}
/*		
		template<class InputIt>
		map(InputIt first, InputIt last, const Allocator& alloc = Allocator()) : _allocator(alloc)
		{
		}
*/

		//	ITERATORS

		iterator				begin() 		{ node<value_type>* tmp = _root; while (tmp->_left != &_null_node) {tmp = tmp->_left;} return (iterator(tmp)); }
		const_iterator			begin() const	{ node<value_type>* tmp = _root; while (tmp->_left != &_null_node) {tmp = tmp->_left;} return (iterator(tmp)); }
		//reverse_iterator		rbegin() { return (); }
		//const_reverse_iterator	rbegin() const { return (); } 
		
		iterator				end() 		{ node<value_type>* tmp = _root; while (tmp != &_null_node) {tmp = tmp->_right;} return (iterator(tmp)); }
		const_iterator			end() const	{ node<value_type>* tmp = _root; while (tmp != &_null_node) {tmp = tmp->_right;} return (iterator(tmp)); }
		//reverse_iterator		rend() { return (); }
		//const_reverse_iterator	rend() const { return (); }	

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
			//_null_node._value.first = size();
			return (ft::make_pair(iterator(tmp), true));
		}

		
		//std::iterator				insert(iterator hint, const value_type& value);
		//void						erase(iterator pos);
		//void						erase(iterator first, iterator last);
		//size_type					erase(const Key& key);
		//void						swap(map& other);



		//	OPERATIONS
 
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