/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 20:01:04 by lnelson           #+#    #+#             */
/*   Updated: 2022/09/23 18:10:10 by lnelson          ###   ########.fr       */
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

		class value_compare
		{  																		 // in C++98, it is required to inherit binary_function<value_type,value_type,bool>
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

		/*
		typedef 									iterator;
		typedef										const_iterator;
		typedef										reverse_iterator;
		typedef 									const_reverse_iterator;
		*/

		private:


		class node
		{

			public:

			value_type	_value;
			node*		_left;
			node*		_right;
			node*		_parent;
			bool		_red;

			node() : _value(), _left(NULL), _right(NULL), _parent(NULL), _red(true) {} 
			node(value_type val, node* left, node* right, node* parent) : _value(val), _left(left), _right(right), _parent(parent), _red(true) {} 
			node(const node& val) _value(val._value), _left(val._left), _right(val.right), _parent(val._parent), _red(val.red);
			~node() {}
		};

		node			*_root;
		allocator_type	_allocator;
		size_type		_size;
		node			_null_node = node();

		node&	search_key(const Key& key)
		{
			node* tmp_node = _root;

			while(tmp_node->_value.first != key && tmp_node != NULL)
			{
				if (key_compare(key, tmp_node->value.first))
					tmp_node = tmp_node->_left;
				else
					tmp_node = tmp_node->_right;
			}
			
			return (tmp_node);
		}
		
		/*
				X	
			   / \	
			  Xl  Y
				 / \
				Yl  Yr

		*/

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

			x._left.parent = x;					// Changing X.new_left_parent to X

			y._right = x;							// Changing Y.right to X

			x._parent = y;							// Changing X.parent to Y
		}

		public:

		map(const map& other)
		{
			_root = &_null_node;
			_size = other.get_size();
			_allocator = other.get_allocator();
			//insert(other.begin(), other.first());
		}

		explicit map(const key_comp& comp = key_comp(), const Allocator& alloc = allocator_type()) : _allocator(alloc), size(0) 
		{
			_root = &_null_node;
		}
		
		//template<class InputIt>
		//map(InputIt first, InputIt last, const Allocator& alloc = Allocator());


		// ELEMENT ACCESS

		mapped_type&		at(const Key& key)			{ return (search_key(key)->value.second); }
		const mapped_type&	at(const Key& key) const;	{ return (search_key(key)->value.second); }
		mapped_type&		operator[](const Key& key);	{ return (search_key(key)->value.second); }



		//	CAPACITY

		bool		empty() const				{ return (_size == 0); 				}
		size_type	size() const				{ return (_size); 					}
		size_type	max_size() const			{ return (_allocator.max_size());	}



		//	MODIFIERS

		//void						clear();

		std::pair<iterator, bool> insert(const value_type& value)
		{
			if (count(value.first))
				return (*(search_key(value.first)));

			if (_root == &_null_node)
			{
				_root = _allocator.allocate(1);
				_allocator.construct(node(value, _null_node, _null_node, _null_node, false), _root);
				return (*_root);
			}

			node 	*tmp_node = _root;
			while (key_compare(value.first, tmp_node->value.first))
			{
				if (key_compare(value.first, tmp_node->value.first))
					tmp_node = tmp_node->_left;
				else
					tmp_node = tmp_node->_right;
			}

			///	REAL INSERTION PROCCES AFTER FINDING PLACEMENT

				tmp_node = _allocator.allocate(1);
				//_allocator.construct(tmp_node, ....);

			///


			return (tmp_node);
		}
		
		//std::iterator				insert(iterator hint, const value_type& value);
		//void						erase(iterator pos);
		//void						erase(iterator first, iterator last);
		//size_type					erase(const Key& key);
		//void						swap(map& other);



		//	LOOKUP
 
		size_type									count(const Key& key) const	{ return (search_key(key) == NULL ? 0 : 1); }

		//iterator									find(const Key& key) const;
		//const_iterator							find(const Key& key) const;

		//std::pair<iterator, iterator> 			equal_range(const Key& key) const;
		//std::pair<const_iterator, const_iteratro> equal_range(const Key& key) const;
		
		//iterator									lower_bound(const Key& key) const;
		//const_iterator							lower_bound(const Key& key) const;

		//iterator									upper_bound(const Key& key) const;
		//const_iterator							upper_bound(const Key& key) const;



		//	OBSERVERS

		key_compare			key_comp() const 	{ return (key_compare); 					}
		map::value_compare	value_comp() const 	{ return (value_compare(key_compare())); 	}

		//	ALLOCATOR

		allocator_type		get_allocator() 	{ return (_allocator); 						}



	};
};

#endif