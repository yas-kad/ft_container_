/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-kad <yait-kad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 15:28:57 by yait-kad          #+#    #+#             */
/*   Updated: 2022/02/22 00:11:23 by yait-kad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

#include <iostream>
#include <iterator_traits.hpp>

namespace ft {
	template < class Iter>
	class Vec_iterator : public iterator<std::random_access_iterator_tag, Iter>
	{
		public:
		
			typedef typename iterator_traits<Iter>::difference_type		difference_type;
			typedef typename iterator_traits<Iter>::pointer				pointer;
			typedef typename iterator_traits<Iter>::reference			reference;
	
		private:
			Iter _ptr;
		public:
									//constructor, destructor, copy constructor, 
			Vec_iterator():_ptr(NULL){};
			explicit Vec_iterator(Iter p): _ptr(p){};
			template<class it>
			Vec_iterator (const Vec_iterator<it>& it) : _ptr(it._ptr){};

			Iter	base(){
				return (this->_ptr);
			}
			
			reference operator*() const{
				return (*this->_ptr);
			}

			Vec_iterator operator+(difference_type n) const
			{
				return Vec_iterator(ptr + n);
			}

			Vec_iterator &operator++()
			{
				this->ptr++;
				return (*this);
			}

			Vec_iterator operator++(int)
			{
				Vec_iterator temp = *this;
				++(*this);
				return temp;
			}

			Vec_iterator &operator+=(difference_type n)
			{
				this->ptr = this->ptr + n;
				return (*this);
			}

			Vec_iterator operator-(difference_type n) const
			{
				return (Vec_iterator(this->ptr - n));
			}

			Vec_iterator &operator--()
			{
				this->ptr--;
				return (*this);
			}

			Vec_iterator operator--(int)
			{
				Vec_iterator temp = *this;
				--(*this);
				return temp;
			}

			Vec_iterator &operator-=(difference_type n)
			{
				this = this - n;
				return (*this);
			}

			pointer operator->() const
			{
				return (&(this->operator*()));
			}

			reference operator[](difference_type n) const
			{
				return (this->base()[n]);
			}
			
	};

	template <class Iterator>
	bool operator==(const Vec_iterator<Iterator> &lhs,
					const Vec_iterator<Iterator> &rhs)
	{
		return (lhs.base() == rhs.base());
	}
	template <class Iterator>
	bool operator!=(const Vec_iterator<Iterator> &lhs,
					const Vec_iterator<Iterator> &rhs)
	{
		return (lhs.base() != rhs.base());
	}
	template <class Iterator>
	bool operator<(const Vec_iterator<Iterator> &lhs,
				   const Vec_iterator<Iterator> &rhs)
	{
		return (lhs.base() < rhs.base());
	}
	template <class Iterator>
	bool operator<=(const Vec_iterator<Iterator> &lhs,
					const Vec_iterator<Iterator> &rhs)
	{
		return (lhs.base() <= rhs.base());
	}
	template <class Iterator>
	bool operator>(const Vec_iterator<Iterator> &lhs,
				   const Vec_iterator<Iterator> &rhs)
	{
		return (lhs.base() > rhs.base());
	}
	template <class Iterator>
	bool operator>=(const Vec_iterator<Iterator> &lhs,
					const Vec_iterator<Iterator> &rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template <class Iterator>
	Vec_iterator<Iterator> operator+(
		typename Vec_iterator<Iterator>::difference_type n,
		const Vec_iterator<Iterator> &iter)
	{
		Vec_iterator<Iterator> tmp = iter + n;
		return (tmp);
	}

	template <class Iterator>
	typename Vec_iterator<Iterator>::difference_type operator-(
		const Vec_iterator<Iterator> &lhs,
		const Vec_iterator<Iterator> &rhs)
	{
		return (lhs.base() - rhs.base());
	}

	
	template < class T, class Alloc = std::allocator<T> >
	class Vector
	{
		public:
			typedef T											value_type;
			typedef Alloc										allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef Vec_iterator<T*>								iterator;
			typedef Vec_iterator<const pointer>					const_iterator;
			typedef ptrdiff_t									difference_type;
			typedef	size_t										size_type;
			
		private:
			allocator_type	_alloc;
			size_type		_capacity;
			size_type		_size;
			pointer			_ar;
		public:
			//--------implement default constructor

			explicit Vector (const allocator_type& alloc = allocator_type()): _alloc(alloc), _capacity(0), _size(0), _ar(NULL);
			//--------implement fill constructor

			explicit Vector (size_type n, const value_type& val = value_type(),
				const allocator_type& alloc = allocator_type()):_alloc(alloc), _capacity(n), _size(n)
			{
				_ar = _alloc.allocate(_capacity);
				for (size_t i = 0; i < _size; i++)
				{
					_ar = val;
				}
			};
			//---------implement range constructor
			
			template <class InputIterator>
         	Vector (InputIterator first, InputIterator last,
                 const allocator_type& alloc = allocator_type()):_alloc(alloc), _size(0), _capacity(0)
			{
				difference_type d = last - first;
				InputIterator it = first;
				while(it != last)
				{
					++_size;
					++_capacity;
					it++;
				}
				_ar = _alloc.allocate(_size);
				int i = 0;
				while (first != last)
				{
					_ar[i] = *first;
					i++;
					first++;
				}
			};
			//--------implement copy constructor
			
			vector (const vector& x)
			{
				*this = x;
			};
			//-------assignement operator

			Vector& operator=(const Vector& x)
			{
				if (_capacity != 0)
					_alloc.deallocate(_ar, _capacity);
				_size = x._size;
				_alloc = x._alloc;
				_capacity = x._capacity;
				if (_capacity != 0)
					_ar = _alloc.allocate(_capacity);
				for (size_t i = 0; i < _size; i++)
				{
					_ar[i] = x._ar[i];
				}
				return (*this);
			}
			// implement begin() method: return iterator pointing to the first element in the vector

			iterator begin()
			{
				return iterator(_ar);
			}
			const_iterator begin() const
			{
				return const_iterator(_ar);
			}
			// implement end() method: Returns an iterator referring to the past-the-end element in the vector container.
			iterator end()
			{
				return iterator(_ar + _size);
			}
			const_iterator end()
			{
				return const_iterator(_ar + _size);
			}
			
			size_type size() const
			{
				return (_size);
			}
			size_type capacity() const
			{
				return (_capacity);
			}
			size_type max_size() const
			{
				return (_alloc.max_size());
			}
			bool empty() const
			{
				return (_size == 0);
			}
	};
}

#endif