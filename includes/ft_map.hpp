/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 20:01:04 by lnelson           #+#    #+#             */
/*   Updated: 2022/09/04 17:34:45 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MAP_HPP
# define FT_MAP_HPP

#include <memory>
#include <functional>
#include <utility>
#include "ft_pair.hpp"


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

		/*
		typedef 									iterator;
		typedef										const_iterator;
		typedef										reverse_iterator;
		typedef 									const_reverse_iterator;
		*/

		private:

		allocator_type	_allocator;

		public:

		map();
		map(const map& other);
		explicit map(const Compare& comp, const Allocator& alloc = Allocator());
		//template<class InputIt>
		//map(InputIt first, InputIt last, const Allocator& alloc = Allocator());

		allocator_type	get_allocator() const;

		// ELEMENT ACCESS

		T&			at(const Key& key);
		const T&	at(const Key& key) const;
		T&			operator[](const Key& key);



		//	CAPACITY

		bool		empty() const;
		size_type	size() const;
		size_type	max_size() const;



		//	MODIFIERS

		void						clear();
		//std::pair<iterator, bool> insert(const value_type& value);
		//std::iterator				insert(iterator hint, const value_type& value);
		//void						erase(iterator pos);
		//void						erase(iterator first, iterator last);
		//size_type					erase(const Key& key);
		void						swap(map& other);



		//	LOOKUP

		size_type									count(const Key& key) const;

		//iterator									find(const Key& key) const;
		//const_iterator							find(const Key& key) const;

		//std::pair<iterator, iterator> 			equal_range(const Key& key);
		//std::pair<const_iterator, const_iteratro> equal_range(const Key& key) const;
		
		//iterator									lower_bound(const Key& key);
		//const_iterator							lower_bound(const Key& key) const;

		//iterator									upper_bound(const Key& key);
		//const_iterator							upper_bound(const Key& key) const;



		//	OBSERVERS

		key_compare			key_comp() const;
		map::value_compare	value_comp() const;

		//	ALLOCATOR

		allocator_type		get_allocator() { return (_allocator); }



	};
};

#endif