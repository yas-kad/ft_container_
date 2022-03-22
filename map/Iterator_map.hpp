#ifndef ITERATOR_MAP_HPP
#define ITERATOR_MAP_HPP

#include "../iterator_traits.hpp"

namespace ft
{
    //- define Iterator Tree
    template <class T, class ptr_node>
    class tree_iterator : public iterator<std::bidirectional_iterator_tag, typename iterator_traits<T>::value_type>
    {
        public:
            typedef typename iterator_traits<T>::reference      reference;
            typedef typename iterator_traits<T>::pointer        pointer;
            typedef std::bidirectional_iterator_tag             iterator_category;

            tree_iterator() : curr_node(nullptr)
            {
            }
            explicit tree_iterator(ptr_node ptr) : curr_node(ptr)
            {
            }
            template <class T1, class ptr_node1>
            tree_iterator (const tree_iterator<T1, ptr_node1>& it) : curr_node(it.base()) {}

            ptr_node base() const
            {
                return curr_node;
            }
            reference operator*() const
            {
                return (curr_node->_data);
            }
            pointer operator->() const
            {
                return (&(curr_node->_data));
            }
            tree_iterator&  operator++()
            {
               curr_node = successor();
               return *this;
            }
            tree_iterator   operator++(int)
            {
                tree_iterator itr(*this);
                ++(*this);
                return itr;
            }
            tree_iterator& operator--()
            {
                curr_node = predecessor();
                return *this;
            }
            tree_iterator   operator--(int)
            {
                tree_iterator itr(*this);
                --(*this);
                return (itr);
            }
            template <class t, class node>
            friend  bool  operator==(const tree_iterator<t, node>& x, const tree_iterator<t, node>& y);
            template <class t, class node>
            friend  bool  operator!=(const tree_iterator<t, node>& x, const tree_iterator<t, node>& y);
        private:
            ptr_node    curr_node;
            ptr_node    successor()
            {
                ptr_node curr = curr_node;
                if (curr->right != nullptr)
                {
                    curr = curr->right;
                    while (curr->left != nullptr)
                        curr = curr->left;
                    return curr;
                }
                else
                {
                    ptr_node ptr_parent = curr->parent;
                    while (ptr_parent != nullptr && curr == ptr_parent->right)
                    {
                        curr = ptr_parent;
                        ptr_parent = ptr_parent->parent;
                    }
                    return ptr_parent;
                }
            }
            ptr_node    predecessor()
            {
                ptr_node curr = curr_node;
                if (curr->left != nullptr)
                {
                    curr = curr->left;
                    while (curr->right != nullptr)
                        curr = curr->right;
                    return curr;
                }
                else
                {
                    ptr_node ptr_parent = curr->parent;
                    while (ptr_parent != nullptr && curr == ptr_parent->left)
                    {
                        curr = ptr_parent;
                        ptr_parent = ptr_parent->parent;
                    }
                    return ptr_parent;

                }
            }
    };

    template <class T, class ptr_node>
    bool  operator==(const tree_iterator<T, ptr_node>& x, const tree_iterator<T, ptr_node>& y)
    {
        return (x.curr_node == y.curr_node);
    }
    template <class T, class ptr_node>
    bool  operator!=(const tree_iterator<T, ptr_node>& x, const tree_iterator<T, ptr_node>& y)
    {
        return (x.curr_node != y.curr_node);
    }
}

#endif