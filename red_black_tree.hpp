/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 15:07:11 by lnelson           #+#    #+#             */
/*   Updated: 2023/01/10 19:12:40 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RED_BLACK_TREE_HPP
# define RED_BLACK_TREE_HPP
/*
'ft::pair<
			ft::map_iterator<
							ft::node<
									ft::pair<
											const int, std::basic_string<char>
											> 
									>
							, ft::pair<
										const int, std::basic_string<char>
										>
							>
			, bool
			>
			::first_type '

 'map_iterator<node<ft::pair<const int, std::basic_string<char> > > >'
 'map_iterator<node<ft::pair<const int, std::basic_string<char> > > >'

*/
#define RED true
#define BALCK false
#include "map.hpp"
#include "map_iterator.hpp"

namespace ft
{
	//////////////////// /////////////////////////////////////
	//////////////////    ////////////////////////////////////
	//														//
	//		RED BLACK TREE NODE CLASS DEFINITION			//
	//														//
	//	This is the node class used for RB tree.			//
	//////////////////////////////////////////    ////////////
	/////////////////////////////////////////// //////////////
	
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
		void	changeColor(bool new_color) { _red = new_color; }

		bool	operator==(const node & val)	{return(val._value == this->_value &&
													val._right == this->_right && 
													val._left == this->_left && 
													val._red == this->_red);}
		node&	operator=(const node& Nnode)
		{
			_value = Nnode._value;
			_left = Nnode._left;
			_right = Nnode._right;
			_parent = Nnode._parent;
			_red = Nnode._red;
			return (*this);
		}

	};

	//////////////////// /////////////////////////////////////
	//////////////////    ////////////////////////////////////
	//														//
	//			RED BLACK TREE CLASS DEFINITION				//
	//														//
	//	A rb tree is a serf balancing, binairy search tree,	//
	//	It need a different Node class, herited from the 	//
	//	base node class defined in <map.hpp>				//
	//////////////////////////////////////////    ////////////
	/////////////////////////////////////////// //////////////

template<
		class value_type, // value_type mean's the ft::pair<key_type, mapped_type> provided by the map
		class key_compare,
		class allocator_type
		> class red_black_tree
	{
		//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//
		//_______________________RBT_MEMBERS_______________________//
		//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//
		
		public:

		typedef typename value_type::second_type								mapped_type;
		typedef typename value_type::first_type									key_type;
		typedef node<value_type> 												node_type;
		typedef std::size_t														size_type;
		
		typedef typename allocator_type:: template rebind<node_type>::other		node_allocator;
		
		typedef	map_iterator<node_type>							iterator;
		typedef map_iterator<const node_type>						const_iterator;

		/*
			reverser iterators to be added...
		*/		
		
		private:

		key_compare			_key_comp;
		node_allocator		_node_allocator;
		node_type			_null_node;
		std::size_t			_size;
		node_type*			_root;

		
		//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//
		//____________________COPLEEN_FUNCTIONS____________________//
		//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//

		public:
		
		red_black_tree() :
		_key_comp(key_compare()),
		_node_allocator(node_allocator()),
		_size(0),
		_root(&_null_node)
		{}

		explicit red_black_tree(const red_black_tree & other) :
		_key_comp(other._key_comp),
		_node_allocator(other._node_allocator),
		_size(0),
		_root(&_null_node)
		{
			//insert(other.begin(), other.last());
		}		
				
		red_black_tree<value_type, key_compare, allocator_type> operator=(red_black_tree<value_type, key_compare, allocator_type>  const & other)
		{
			//clear();
			_key_comp = other._key_comp;
			_node_allocator = other._node_allocator;
			_size = 0;
			_root = &_null_node;

			//insert(other.begin(), other.last());
		}
	
		//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//
		//______________________PRIVATE_FUNCTIONS__________________//
		//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//

		private:

		node_type&	createNode(node_type nNode) 
		{
			node_type *ret = _node_allocator.allocate(1);
			_node_allocator.construct(ret, nNode);
			return (*ret);
		}

		node_type*	search_key(const key_type & key) const
		{
			node_type* tmp_node = _root;

			while(tmp_node->_value.first != key && tmp_node != &_null_node)
			{
				if (_key_comp(key, tmp_node->_value.first))
					tmp_node = tmp_node->_left;
				else
					tmp_node = tmp_node->_right;
			}
			
			return (tmp_node);
		}
		
		void	right_rotate(node_type & x)
		{
			node_type& y = *x._right;				// Y is the X->left_node

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

		void	left_rotate(node_type & x)
		{
			node_type& y = *x._left;				// Y is the X->right_node

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
		void	insertFixUp(node_type * newNode)
		{
			if (_root == newNode   )
				{ _root->changeColor(); return ; }
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
		
		//	ITERATORS

		iterator					begin() 		{ node<value_type>* tmp = _root; while (tmp->_left != &_null_node) {tmp = tmp->_left;} return (iterator(tmp));}
		const_iterator				begin() const	{ node<value_type>* tmp = _root; while (tmp->_left != &_null_node) {tmp = tmp->_left;} return (iterator(tmp));}
		
		//reverse_iterator			rbegin() 		{ return (_internal_tree.rbegin());	}
		//const_reverse_iterator	rbegin() const	{ return (_internal_tree.rbegin());	}
		
		iterator					end() 			{ node<value_type>* tmp = _root; while (tmp != &_null_node) {tmp = tmp->_right;} return (iterator(tmp)); }
		const_iterator				end() const		{ node<value_type>* tmp = _root; while (tmp != &_null_node) {tmp = tmp->_right;} return (iterator(tmp)); }
		
		//reverse_iterator			rend()			{ return (_internal_tree.rend());	}
		//const_reverse_iterator	rend() const	{ return (_internal_tree.rend());	}

		// ELEMENT ACCESS		- A REFAIRE, ajouter les exceptions

		//mapped_type&			at(const key_type& key)			{ return (search_key(key)->value.second)); }
		//const mapped_type&	at(const key_type& key) const	{ return (search_key(key)->value.second)); }
		//mapped_type&			operator[](const key_type& key)	{ return (_internal_tree[]); }


		//	CAPACITY

		bool		empty() const				{ return (_size == 0); 				}
		size_type	size() const				{ return (_size); 					}
		size_type	max_size() const			{ return (_node_allocator.max_size());	}



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
				{_root = &createNode(node<value_type>(value, &_null_node, &_null_node, &_null_node, RED)); tmp = _root;}
			else		
				while (1)
				{
					if (_key_comp(value.first, tmp->_value.first))
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
			//	create a node with 'createNode' left|right|_root positions.
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
		//size_type					erase(const key_type& key);
		//void						swap(map& other);



		//	OPERATIONS
 
		size_type									count(const key_type& key) const	{ return (search_key(key) == &_null_node ? 0 : 1); }

		//iterator									find(const key_type& key) const;
		//const_iterator							find(const key_type& key) const;

		//ft::pair<iterator, iterator> 			equal_range(const key_type& key) const;
		//ft::pair<const_iterator, const_iteratro> equal_range(const key_type& key) const;
		
		//iterator									lower_bound(const key_type& key) const;
		//const_iterator							lower_bound(const key_type& key) const;

		//iterator									upper_bound(const key_type& key) const;
		//const_iterator							upper_bound(const key_type& key) const;



		//	OBSERVERS

		key_compare			key_comp() const 	{ return (_key_comp); }

		//	ALLOCATOR

		allocator_type		get_allocator() 	{ return (_node_allocator); }

	};
};

#endif