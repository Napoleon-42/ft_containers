/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pair.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 23:05:32 by lnelson           #+#    #+#             */
/*   Updated: 2022/09/03 19:27:06 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PAIR_HPP
# define FT_PAIR_HPP


namespace ft
{

template<class T1, class T2>
struct pair
{

	public:
	
	typedef T1 first_type;
	typedef T2 second_type;
	
	first_type	first;
	second_type	second;

	pair() : first(), second() {};

	template <class T, class U>
	pair(const pair<T,U>& pr)
	{
		first = pr.first;
		second = pr.second;
	}

	pair(const first_type& v1, const second_type& v2)
	{
		first = v1;
		second = v2;
	}

	~pair() {};

	pair&	operator=(const pair& pr)
	{
		first = pr.first;
		second = pr.second;
	}

};

template <class T1, class T2>
pair<T1,T2>	make_pair (T1 x, T2 y) { return (pair<T1,T2>(x,y)); }

template <class T1, class T2>
bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
{ return lhs.first==rhs.first && lhs.second==rhs.second; }

template <class T1, class T2>
bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
{ return !(lhs==rhs); }

template <class T1, class T2>
bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
{ return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second); }

template <class T1, class T2>
bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
{ return !(rhs<lhs); }

template <class T1, class T2>
bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
{ return rhs<lhs; }

template <class T1, class T2>
bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
{ return !(lhs<rhs); }

};


#endif