/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-kad <yait-kad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 16:03:06 by yait-kad          #+#    #+#             */
/*   Updated: 2022/02/24 16:08:52 by yait-kad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft 
{

//TODO - Reverse iterator
template <class Iterator>
class reverse_iterator : public iterator< typename iterator_traits<Iterator>::iterator_category,
                                            typename iterator_traits<Iterator>::value_type,
                                            typename iterator_traits<Iterator>::difference_type,
                                            typename iterator_traits<Iterator>::pointer,
                                            typename iterator_traits<Iterator>::reference>
{
    public:
        typedef Iterator iterator_type;
        typedef typename iterator_traits<Iterator>::difference_type     difference_type;
        typedef typename iterator_traits<Iterator>::pointer             pointer;
        typedef typename iterator_traits<Iterator>::reference           reference;

        //TODO - Constructor Default
        reverse_iterator() : _itr(nullptr) {}

        //TODO - initialization
        explicit reverse_iterator (iterator_type it) : _itr(it) {}

        //TODO - copy
        template <class Iter>
        reverse_iterator (const reverse_iterator<Iter>& rev_it) : _itr(rev_it._itr) {}
        
        //TODO - Return base iterator
        iterator_type base() const
        {
            return _itr;
        }

        //TODO - Dereference iterator
        reference operator*() const
        {
            return (*(--this->base()));
        }

        //TODO - Addition operator
        reverse_iterator operator+ (difference_type n) const
        {
            return reverse_iterator(_itr - n);
        }

        //TODO - Increment iterator position
        reverse_iterator& operator++()
        {
            --_itr;
            return (*this);
        }
        reverse_iterator  operator++(int)
        {
            reverse_iterator tmp = *this;
            --_itr;
            return tmp;
        }
        reverse_iterator& operator+= (difference_type n)
        {
            this->_itr -= n;
            return (*this);
        }
        reverse_iterator operator- (difference_type n) const
        {
            return reverse_iterator(this->_itr + n);
        }
        reverse_iterator& operator--()
        {
            ++_itr;
            return (*this);
        }
        reverse_iterator  operator--(int)
        {
            reverse_iterator tmp = *this;
            ++_itr;
            return (tmp);
        }
        reverse_iterator& operator-= (difference_type n)
        {
            _itr += n;
            return (*this);
        }
        pointer operator->() const
        {
            return &(operator*());
        }
        reference operator[] (difference_type n) const
        {
            return (*(_itr - n));
        }
    private:
        iterator_type _itr;
};

template <class Iterator>
bool operator== (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
{
    return (rhs.base() == lhs.base());
}
template <class Iterator>
bool operator!= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
{
    return (rhs.base() != lhs.base());
}
template <class Iterator>
bool operator< (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
{
    return (rhs.base() < lhs.base());
}
template <class Iterator>
bool operator<= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
{
    return (rhs.base() <= lhs.base());
}
template <class Iterator>
bool operator> (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
{
    return (rhs.base() > lhs.base());
}
template <class Iterator>
bool operator>= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
{
    return (rhs.base() >= lhs.base());
}
template <class Iterator>
reverse_iterator<Iterator> operator+ (typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it)
{
    return (*(rev_it.base() - n));
}
template <class Iterator>
typename reverse_iterator<Iterator>::difference_type operator- (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
{
    return (lhs.base() - rhs.base());
}

}
#endif