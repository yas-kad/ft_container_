#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include "Iterator_map.hpp"
#include "Pair.hpp"
#include "Make_pair.hpp"
#include "../reverse_iterator.hpp"
#include "bst.hpp"

namespace ft
{
    template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<pair<const Key,T> > >
    class map
    {
        public:
            //- Member types
            typedef Key                                             key_type;
            typedef T                                               mapped_type;
            typedef pair<const key_type, mapped_type>               value_type;
            typedef Compare                                         key_compare;
            //- Nested function class to compare elements
            class value_compare : std::binary_function<value_type, value_type, bool>
            {
                friend class map;
                protected:
                    Compare comp;
                    value_compare(Compare c) : comp(c)
                    {
                    }
                public:
                    bool operator()(const value_type& x, const value_type& y)
                    {
                        return comp(x.first, y.first);
                    }
            };
            typedef Alloc                                           allocator_type;
            typedef typename allocator_type::reference              reference;
            typedef typename allocator_type::const_reference        const_reference;
            typedef typename allocator_type::pointer                pointer;
            typedef typename allocator_type::const_pointer          const_pointer;
            typedef BST<value_type, key_compare, Alloc>             tree;
            typedef typename tree::ptr_node                         ptr_node;
            typedef tree_iterator<pointer, ptr_node>                iterator;
            typedef tree_iterator<const_pointer, ptr_node>          const_iterator;
            typedef reverse_iterator<const_iterator>                const_reverse_iterator;
            typedef reverse_iterator<iterator>                      reverse_iterator;
            typedef ptrdiff_t                                       difference_type;
            typedef size_t                                          size_type;

            //- Default Constructor
            explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : 
                            _tree(), _cmp(comp), _alloc(alloc)
            {
            }
            //- Range Constructor
            template <class InputIterator>
            map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :
                _tree(), _cmp(comp), _alloc(alloc)
            {
                while (first != last)
                {
                    _tree.insert_node(*first);
                    first++;
                }
                
            }
            //- copy constructor
            map (const map& x) : _cmp(x._cmp), _alloc(x._alloc)
            {
                insert(x.begin(), x.end());
            }
            //- Copy container content
            map& operator= (const map& x)
            {
                if (x.size() == 0)
                {
                    this->clear();
                    return *this;
                }
                if (this != &x)
                {
                    this->clear();
                    insert(x.begin(), x.end());
                }
                return *this;
            }
            //- Map destructor
            ~map()
            {
            }
            //- Access element
            mapped_type& operator[] (const key_type& k)
            {
                ptr_node node = _tree.search_node(ft::make_pair(k, mapped_type()));
                if (node == nullptr)
                    _tree.insert_node(ft::make_pair(k, mapped_type()));
                node = _tree.search_node(ft::make_pair(k, mapped_type()));
                return (node->_data.second);
            }
            //- size_type size() const
            size_type size() const
            {
                return _tree.size();
            }
            //- Test whether container is empty
            bool empty() const
            {
                return(_tree.size() == 0);
            }
            //- Return maximum size
            size_type max_size() const
            {
                return (_tree.max_size());
            }
            //- Insert elements
            pair<iterator,bool> insert(const value_type& val)
            {
                ptr_node node = _tree.search_node(val);
                if (node != nullptr)
                    return ft::pair<iterator, bool>(iterator(node), false);
                _tree.insert_node(val);
                node = _tree.search_node(val);
                return (ft::pair<iterator, bool>(iterator(node), true));
            }
            iterator    insert(iterator position, const value_type& val)
            {
                static_cast<void>(position);
                ptr_node node = _tree.search_node(val);
                if (node != nullptr)
                    return iterator(node);
                _tree.insert_node(val);
                node = _tree.search_node(val);
                return (iterator(node));
            }
            template <class InputIterator>
            void insert (InputIterator first, InputIterator last)
            {
                while (first != last)
                {
                    _tree.insert_node(*first);
                    first++;
                }
            }
            //- Erase elements
            void    erase(iterator position)
            {
                if (position != iterator(nullptr))
                    _tree.delete_node(ft::make_pair(position->first, position->second));
            }
            size_type   erase(const key_type& k)
            {
                ptr_node node = _tree.search_node(ft::make_pair(k, mapped_type()));
                if (node != nullptr)
                {
                    _tree.delete_node(ft::make_pair(k, mapped_type()));
                    return 1;
                }
                else
                    return 0;
            }
            void    erase(iterator first, iterator last)
            {
                iterator tmp;
                while (first != last)
                {
                    if (first == iterator(_tree.get_end()))
                        return ;
                    tmp = first;
                    first++;
                    this->erase(tmp);
                }
            }
            //- Swap content
            void swap (map& x)
            {
                _tree.swap(x._tree);
            }
            //- Clear content
            void clear()
            {
                _tree.clear();
            }
            //- Return key comparison object
            key_compare key_comp() const
            {
                return key_compare();
            }
            //- Return value comparison object
            value_compare value_comp() const
            {
                return value_compare(_cmp);
            }
            //- Get iterator to element
            iterator    find(const key_type& k)
            {
                ptr_node node = _tree.search_node(ft::make_pair(k, mapped_type()));
                if (node == nullptr)
                    return iterator(_tree.get_end());
                return iterator(node);
            }
            const_iterator  find(const key_type& k) const
            {
                ptr_node node = _tree.search_node(ft::make_pair(k, mapped_type()));
                if (node == nullptr)
                    return const_iterator(_tree.get_end());
                return const_iterator(node);
            }
            //- Count elements with a specific key
            size_type count(const key_type& k) const
            {
                return (_tree.search_node(ft::make_pair(k, mapped_type())) == nullptr ? 0 : 1);
            }
            //- Return iterator to lower bound
            iterator    lower_bound(const key_type& k)
            {
                return iterator(_tree.lower_bound(ft::make_pair(k, mapped_type())));
            }
            const_iterator  lower_bound(const key_type& k) const
            {
                return const_iterator(_tree.lower_bound(ft::make_pair(k, mapped_type())));
            }
            //- Return iterator to upper bound
            iterator    upper_bound(const key_type& k)
            {
                return iterator(_tree.upper_bound(ft::make_pair(k, mapped_type())));
            }
            const_iterator  upper_bound(const key_type& k) const
            {
                return const_iterator(_tree.upper_bound(ft::make_pair(k, mapped_type())));
            }
            //- Get range of equal elements
            pair<iterator,iterator> equal_range(const key_type& k)
            {
                return (ft::make_pair(lower_bound(k), upper_bound(k)));
            }
            pair<const_iterator,const_iterator> equal_range(const key_type& k) const
            {
                 return (ft::make_pair(lower_bound(k), upper_bound(k)));
            }
            //- Get allocator
            allocator_type  get_allocator() const
            {
                return (_tree.get_alloc());
            }
            //- Return iterator to beginning
            iterator begin()
            {
                return iterator(_tree.get_min());
            }
            const_iterator begin() const
            {
                return const_iterator(_tree.get_min());
            }
            //- Return iterator to end
            iterator end()
            {
                return iterator(_tree.get_end());
            }
            const_iterator end() const
            {
                return const_iterator(_tree.get_end());
            }
            //- Return reverse iterator to reverse beginning
            reverse_iterator rbegin()
            {
                return reverse_iterator(this->end());
            }
            const_reverse_iterator rbegin() const
            {
                return const_reverse_iterator(this->end());
            }
            //- Return reverse iterator to reverse end
            reverse_iterator rend()
            {
                return reverse_iterator(this->begin());
            }
            const_reverse_iterator rend() const
            {
                return const_reverse_iterator(this->begin());
            }
        private:
            tree    _tree;
            key_compare _cmp;
            allocator_type _alloc;
    };
}

#endif