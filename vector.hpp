/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-kad <yait-kad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 15:28:57 by yait-kad          #+#    #+#             */
/*   Updated: 2022/03/12 15:45:10 by yait-kad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

#include <iostream>
#include "iterator_traits.hpp"
#include "reverse_iterator.hpp"
#include "enable_if.hpp"
#include "is_integral.hpp"

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
			Vec_iterator (const Vec_iterator<it>& iterat) : _ptr(iterat.base()){};

			Iter	base() const {
				return (this->_ptr);
			}
			
			reference operator*() const{
				return (*this->_ptr);
			}

			Vec_iterator operator+(difference_type n) const
			{
				return Vec_iterator(_ptr + n);
			}

			Vec_iterator &operator++()
			{
				this->_ptr++;
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
				this->_ptr = this->_ptr + n;
				return (*this);
			}

			Vec_iterator operator-(difference_type n) const
			{
				return (Vec_iterator(this->_ptr - n));
			}

			Vec_iterator &operator--()
			{
				this->_ptr--;
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
	typename Vec_iterator<Iterator>::difference_type operator-( const Vec_iterator<Iterator> &lhs, const Vec_iterator<Iterator> &rhs)
	{
		return (lhs.base() - rhs.base());
	}

	
	template < class T, class Alloc = std::allocator<T> >
	class vector
	{
		public:
			typedef T											value_type;
			typedef Alloc										allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef Vec_iterator<T*>							iterator;
			typedef Vec_iterator<const_pointer>					const_iterator;
			typedef reverse_iterator<const_iterator>			const_reverse_iterator;
			typedef reverse_iterator<iterator>					reverse_iterator;
			typedef ptrdiff_t									difference_type;
			typedef	size_t										size_type;
			
		private:
			allocator_type	_alloc;
			size_type		_capacity;
			size_type		_size;
			pointer			_ar;
		public:
			//--------implement default constructor

			explicit vector (const allocator_type& alloc = allocator_type()): _alloc(alloc), _capacity(0), _size(0), _ar(NULL){};
			//--------implement fill constructor

			explicit vector (size_type n, const value_type& val = value_type(),
				const allocator_type& alloc = allocator_type()):_alloc(alloc), _capacity(n), _size(n)
			{
				_ar = _alloc.allocate(_capacity);
				for (size_t i = 0; i < _size; i++)
				{
					_alloc.construct(_ar + i, val);
				}
			};
			
			//---------implement range constructor
			
			template <class InputIterator>
         	vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
			 	typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type* = nullptr):_alloc(alloc), _size(0), _capacity(0)
			{
				difference_type d = last - first;
				InputIterator it = first;
				while(it != last)
				{
					++_size;
					++_capacity;
					it++;
				}
				_ar = _alloc.allocate(_capacity);
				size_type i = 0;
				while (first != last)
				{
					_ar[i] = *first;
					i++;
					first++;
				}
			};
			
			//--------implement copy constructor
			
			vector (const vector& x) : _size(0), _capacity(0)
			{
				*this = x;
			};
			//-------assignement operator

			vector& operator=(const vector& x)
			{
				if (this != &x)
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
			const_iterator end() const
			{
				return const_iterator(_ar + _size);
			}
			
			//-----Return reverse iterator to reverse beginning
			reverse_iterator rbegin()
			{
				return reverse_iterator(this->end());
			}
			const_reverse_iterator rbegin() const
			{
				return const_reverse_iterator(this->begin());
			}
			//----Return reverse iterator to reverse end
			reverse_iterator rend()
			{
				return reverse_iterator(this->begin());
			}
			const_reverse_iterator rend() const
			{
				return const_reverse_iterator(_ar);
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
			
			void    resize(size_type n, value_type val = value_type())
        	{
                if (n > _size)
                {
                    for (size_t i = _size; i < n; i++)
                        push_back(val);
                }
                else if(n < _size)
                {
                    size_type tmp = _size;
                    for (size_t i = n; i < tmp; i++)
                        pop_back();
                }
        	}
        	void reserve (size_type n)
        	{
				if (n > capacity())
				{   
					value_type *new_arr;
					if (n > _capacity * 2)
					{
						new_arr = _alloc.allocate(n);
						_capacity = n;
					}
					else
					{
						new_arr = _alloc.allocate(_capacity * 2);
						_capacity *= 2;
					}
					for (size_t i = 0; i < size(); i++)
					{
						new_arr[i] = _ar[i];
					}
					_alloc.deallocate(_ar, _capacity);
					_ar = new_arr;
            	}
        	}

			//-------implement functions the Element access
			reference operator[] (size_type n)
			{
				return (_ar[n]);
			}
			const_reference operator[] (size_type n) const
			{
				return (_ar[n]);
			}
			reference at(size_type n)
			{
				if (n >= _size)
					throw std::out_of_range("vector.");
				return (_ar[n]);
			}
			const_reference at (size_type n) const
			{
				if (n >= _size)
					throw std::out_of_range("vector.");
				return (_ar[n]);
			}
			reference front()
			{
				return (_ar[0]);
			}
			const_reference front() const
			{
				return (_ar[0]);
			}
			reference back()
			{
				return (_ar[_size - 1]);
			}
			const_reference back() const
			{
				return (_ar[_size - 1]);
			}
        //--------implement functions the Modifiers
		template <class InputIterator>
        void assign(InputIterator first, InputIterator last,
                    typename  enable_if<!is_integral<InputIterator>::value, InputIterator>::type* = nullptr)
        {
            difference_type dt = last - first;
            _size = dt;
            _capacity = dt;
            _alloc.deallocate(_ar, _capacity);
            _ar = _alloc.allocate(_capacity);
            for (size_type i = 0; i < _size; i++)
            {
                _ar[i] = *(first + i);
            }
        }
        void assign(size_type n, const value_type& val)
        {
            this->clear();
            for (size_type i = 0; i < n; i++)
                this->push_back(val);
        }
        void push_back(const value_type& val)
        {
            if (_capacity == 0)
            {
                _ar = _alloc.allocate(1);
                _capacity++;
            }
            if (_size == _capacity)
            {
                value_type *new_ptr = _alloc.allocate(_capacity * 2);
                for (size_type i = 0; i < _size; i++)
                {
                    new_ptr[i] = _ar[i];
                }
                _alloc.deallocate(_ar, _capacity);
                _ar = new_ptr;
                _capacity *= 2;

            }
            _ar[_size] = val;
            _size++;
        }
        void pop_back()
        {
            if (_size > 0)
            {
                _alloc.destroy(_ar + (_size - 1));
                _size -= 1;
            }
        }
        iterator insert (iterator position, const value_type& val)
        {   
            size_type pos = position - begin();
            if (_capacity == 0)
            {
                _ar = _alloc.allocate(1);
                _capacity++;
            }
            if (_size == _capacity)
            {
                value_type *new_ptr = _alloc.allocate(_capacity * 2);
                for (size_type i = 0; i < _size; i++)
                {
                    new_ptr[i] = _ar[i];
                }
                _alloc.deallocate(_ar, _capacity);
                _ar = new_ptr;
                _capacity *= 2;

            }
            _ar[_size] = val;
            _size++;
            for (size_type i = _size - 1; i > pos; i--)
            {
                _ar[i] = _ar[i - 1];
            }
            _ar[pos] = val;
            return iterator(_ar + pos);
        }
        void    insert (iterator position, size_type n, const value_type& val)
        {
            size_type pos = position - begin();
            if ((_size + n) > _capacity)
                this->reserve(_size + n);
            for (size_type i = _size; i > pos; i--)
            {
                _ar[i - 1 + n] = _ar[i - 1];
            }
            _size += n;
            while (n--)
            {
                _ar[pos + n] = val;
            }
        }

        template <class InputIterator>
        void    insert(iterator position, InputIterator first, InputIterator last,
                        typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type* = nullptr)
        {
            size_type count = 0;
            size_type pos = position - begin();
            while (first != last)
            {
                count++;
                first++;
            }
            if ((_size + count) > _capacity)
                this->reserve(_size + count);
            for (size_t i = _size; i > pos; i--)
            {
                _ar[i - 1 + count] = _ar[i - 1];
            }
            _size += count;
            while (count--)
            {
                _ar[pos + count] = *(last - 1);
                last--;
            }
            
        }
        iterator erase (iterator position)
        {
            for (iterator it = position; it != end(); ++it)
                *it = *(it + 1);
            pop_back();
            return position;
        }

        iterator	erase(iterator first, iterator last)
        {
            iterator tmp = first;

            while (tmp != last)
            {
                erase(first);
                tmp++;
            }
            return (first);
        }
        void swap (vector& x)
        {
            vector<value_type> tmp;
            tmp = x;
            x = *this;
            *this = tmp;
        }
        void clear()
        {
            size_type tmp = _size;
            for (size_t i = 0; i < tmp; i++)
            {
                _alloc.destroy(_ar + i);
                _size--;
            }
        }
    
        // ----- Allocator:
        allocator_type  get_allocator() const
        {
            return (_alloc);
        }
        
        ~vector()
        {
            if (_capacity != 0)
                _alloc.deallocate(_ar, _capacity);
        }
	};

	//------ Lexicographical less-than comparison
    template <class InputIterator1, class InputIterator2>
    bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
    {
        while (first1!=last1)
        {
            if (first2==last2 || *first2<*first1) return false;
            else if (*first1<*first2) return true;
            ++first1; ++first2;
        }
        return (first2!=last2);
    }
    //------ Test whether the elements in two ranges are equal (equal)
    template <class InputIterator1, class InputIterator2>
    bool equal ( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2 )
    {
        while (first1!=last1)
        {
            if (!(*first1 == *first2))
                return false;
            ++first1; ++first2;
        }
        return true;
    }
	  //------Non-member function overloads
    template <class T, class Alloc>
    bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return (lhs.size() == rhs.size() && equal(lhs.begin(), lhs.end(), rhs.begin()));
    }
    template <class T, class Alloc>
    bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return !(lhs == rhs);
    }
    template <class T, class Alloc>
    bool operator< (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return (lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
    }
    template <class T, class Alloc>
    bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return !(rhs < lhs);
    }
    template <class T, class Alloc>
    bool operator> (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return (rhs < lhs);
    }
    template <class T, class Alloc>
    bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return !(lhs < rhs);
    }

    //-----Exchange contents of vectors
    template <class T, class Alloc>
    void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
    {
        x.swap(y);
    }
}

#endif