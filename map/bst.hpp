#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP

#include <iostream>

namespace ft 
{
    //- Make Data Structure of BST
    template <class T>
    struct node
    {
        T           _data;
        node        *left;
        node        *right;
        node        *parent;
        int         bf;

        node(const T& src_data) : _data(src_data)
        {
        }
    };

    //- Make Binary Search Tree (BST)
    template <class T, class Compare, class Alloc>
    class BST
    {
        public:
            typedef T                                                                               value_type;
            typedef node<T>*                                                                        ptr_node;
            typedef typename Alloc::template rebind<node<value_type> >::other                       allocator_type;
            typedef Compare                                                                         key_compare;
            typedef size_t                                                                          size_type;

        
            BST(const allocator_type& alloc = allocator_type(), const key_compare& comp = key_compare()) : _root(nullptr), _end(nullptr), _alloc(alloc), _cmp(comp), _size(0)
            {
            }
            ptr_node    increment(ptr_node curr)
            {
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
            allocator_type  get_alloc() const
            {
                return allocator_type();
            }
            size_type size() const
            {
                return _size;
            }
            size_type max_size() const
            {
                return (_alloc.max_size());
            }
            void swap (BST& x)
            {
                size_type       s_size = x._size;
                allocator_type  s_alloc = x._alloc;
                ptr_node        s_end = x._end;
                ptr_node        s_root = x._root;
                x._size = _size;
                _size = s_size;
                x._alloc = _alloc;
                _alloc = s_alloc;
                x._end = _end;
                _end = s_end;
                x._root = _root;
                _root = s_root;

            }
            ptr_node    all_clean_tree(ptr_node node)
            {
                if (node != nullptr)
                {
                    all_clean_tree(node->left);
                    all_clean_tree(node->right);
                    _alloc.deallocate(node, 1);
                }
                return nullptr;
            }
            void clear()
            {
                _root = all_clean_tree(_root);
                if (_root == nullptr)
                {
                    _alloc.deallocate(_end, 1);
                    _end = nullptr;
                }
                _size = 0;
            }
            ptr_node    lower_bound(value_type val)
            {
                ptr_node node = get_min();
                while (node != _end)
                {
                    if (!_cmp(node->_data.first, val.first))
                        return node;
                    node = increment(node);
                }
                return _end;
            }
            ptr_node    upper_bound(value_type val)
            {
                ptr_node node = get_min();
                while (node != _end)
                {
                    if (_cmp(val.first, node->_data.first))
                        return node;
                    node = increment(node);
                }
                return _end;
            }
            void    insert_node(value_type data)
            {

                ptr_node new_node = _alloc.allocate(1);
                _alloc.construct(new_node, data);
                new_node->left = nullptr;
                new_node->right = nullptr;
                new_node->parent = nullptr;
                new_node->bf = 0;

                if (_root == nullptr)
                {
                    _end = _alloc.allocate(1);
                    _root = new_node;
                    _root->parent = _end;
                    _end->left = _root;
                    _size++;
                    return ;
                }
                ptr_node tmp = _root;
                ptr_node parent = nullptr;
                while (tmp != nullptr)
                {
                    parent = tmp;
                    if (_cmp(new_node->_data.first, tmp->_data.first))
                        tmp = tmp->left;
                    else if (new_node->_data.first == tmp->_data.first)
                    {
                        tmp->_data.second = new_node->_data.second;
                        _alloc.deallocate(new_node, 1);
                        return ;
                    }
                    else
                        tmp = tmp->right;
                }
                if (_cmp(new_node->_data.first, parent->_data.first))
                {
                    parent->left = new_node;
                    _size++;
                }
                else
                {
                    parent->right = new_node;
                    _size++;
                }
                new_node->parent = parent;
                //NOTE - Calcule bf every node
                insert_balance_factor(new_node);
            }
            ptr_node    get_max() const
            {
                ptr_node tmp = _root;
                if (tmp == nullptr)
                    return nullptr;
                return get_max_helper(tmp);
            }

            ptr_node    get_min() const
            {
                ptr_node tmp = _root;
                if (tmp == nullptr)
                    return nullptr;
                return get_min_helper(tmp);
            }

            ptr_node  search_node(value_type val)
            {
                ptr_node tmp = _root;
                
                if (tmp == nullptr)
                    return (nullptr);
                while (tmp->_data.first != val.first)
                {
                    if (tmp != nullptr)
                    {
                        if (_cmp(val.first, tmp->_data.first))
                            tmp = tmp->left;
                        else
                            tmp = tmp->right;
                    }
                    if (tmp == nullptr)
                        return nullptr;
                }
                return tmp;
                
            }
            
            ptr_node  search_node(value_type val) const
            {
                ptr_node tmp = _root;
                
                if (tmp == nullptr)
                    return (nullptr);
                while (tmp->_data.first != val.first)
                {
                    if (tmp != nullptr)
                    {
                        if (_cmp(val.first, tmp->_data.first))
                            tmp = tmp->left;
                        else
                            tmp = tmp->right;
                    }
                    if (tmp == nullptr)
                        return nullptr;
                }
                return tmp;
                
            }

            void    delete_node(value_type val)
            {
                bool isonechild = false;
                ptr_node node = this->search_node(val);
                ptr_node node_p= this->search_node(val)->parent;
                if (node->left == nullptr || node->right == nullptr)
                    isonechild = true;
                _root = delete_helper(_root, val);
                if (_root == nullptr)
                {
                    _alloc.deallocate(_end, 1);
                    _end = nullptr;
                }
                if (isonechild == true)
                    delete_balance_factor(node_p, val);
            }
            void    print_bst()
            {
                print_bst_preorder(this->_root);
            }

            ptr_node get_end() const {return _end;}

            ~BST()
            {
                _root = all_clean_tree(_root);
                _alloc.deallocate(_end, 1);
            }

        private:
            //- Start Tree
            ptr_node            _root;
            ptr_node            _end;
            allocator_type      _alloc;
            key_compare         _cmp;
            size_type           _size;
            

            ptr_node get_max_helper(ptr_node tmp)
            {
                while (tmp->right != nullptr)
                    tmp = tmp->right;
                return tmp;
            }

            ptr_node get_min_helper(ptr_node tmp) const
            {
                while (tmp->left != nullptr)
                    tmp = tmp->left;
                return tmp;
            }
            ptr_node    delete_helper(ptr_node root, value_type val)
            {
                ptr_node tmp;
                if (root == nullptr)
                    return root;
                else if (_cmp(val.first, root->_data.first))
                    root->left = delete_helper(root->left, val);
                else if (_cmp(root->_data.first, val.first))
                    root->right = delete_helper(root->right, val);
                else
                {
                    if (root->left == nullptr)
                    {
                        ptr_node tmp = root->right;
                        if (tmp != nullptr)
                            tmp->parent = root->parent;
                        _alloc.deallocate(root, 1);
                        _size--;
                        return tmp;
                    }
                    else if (root->right == nullptr)
                    {
                        ptr_node tmp = root->left;
                        if (tmp != nullptr)
                            tmp->parent = root->parent;
                        _alloc.deallocate(root, 1);
                        _size--;
                        return tmp;
                    }
                    else
                    {
                        ptr_node max_val = this->get_max_helper(root->left);
                        value_type vt = max_val->_data;
                        ptr_node node = max_val->parent;
                        root->left = delete_helper(root->left, max_val->_data);
                        tmp = delete_balance_factor(node, vt);
                        _alloc.construct(root, vt);
                        if (tmp != nullptr)
                            root = tmp;
                    }
                }
                return root;
            }

            void    print_bst_preorder(ptr_node root)
            {
                if (root != nullptr)
                {
                    std::cout <<root->_data.first << "\t"<< root->bf << std::endl;
                    print_bst_preorder(root->left);
                    print_bst_preorder(root->right);
                }
            }
            int     max(int a, int b)
            {
                return (a > b ? a : b);
            }
            int     min(int a, int b)
            {
                return (a < b ? a : b);
            }
            ptr_node    right_rotation(ptr_node node)
            {
                ptr_node tmp = node->left;
                node->left = tmp->right;
                if (tmp->right != nullptr)
                    tmp->right->parent = node;
                tmp->parent = node->parent;
                if (node->parent == _end)
                {
                    this->_root = tmp;
                    tmp->parent = _end;
                }
                else if (node == node->parent->right)
                    node->parent->right = tmp;
                else
                    node->parent->left = tmp;
                
                tmp->right = node;
                node->parent = tmp;
                node->bf = node->bf - 1 - max(0, tmp->bf);
                tmp->bf = tmp->bf - 1 - min(0, node->bf);
                return tmp;
            }
            ptr_node    left_rotation(ptr_node node)
            {
                ptr_node    tmp = node->right;
                node->right = tmp->left;
                if (tmp->left != nullptr)
                    tmp->left->parent = node;
                tmp->parent = node->parent;
                if (node->parent == _end)
                {
                    this->_root = tmp;
                    this->_root->parent = _end;
                    _end->left = this->_root;
                }
                else if (node == node->parent->left)
                    node->parent->left = tmp;
                else
                    node->parent->right = tmp;
                
                tmp->left = node;
                node->parent = tmp;
                node->bf = node->bf + 1 - min(0, tmp->bf);
                tmp->bf = tmp->bf + 1 + max(0, node->bf);
                return tmp;
            }
            ptr_node    rebalance(ptr_node node)
            {
                ptr_node tmp = nullptr;

                if (node->bf < 0)
                {
                    if (node->right->bf > 0)
                    {
                        right_rotation(node->right);
                        tmp = left_rotation(node);
                    }
                    else
                        tmp = left_rotation(node);
                }
                else if (node->bf > 0)
                {
                    if (node->left->bf < 0)
                    {
                        left_rotation(node->left);
                        tmp = right_rotation(node);
                    }
                    else
                        tmp = right_rotation(node);

                }
                return tmp;
            }
            void    insert_balance_factor(ptr_node node)
            {
                if (node->bf < -1 || node->bf > 1)
                {
                    rebalance(node);
                    return ;
                }
                if (node->parent != _end)
                {
                    if (node == node->parent->left)
                        node->parent->bf += 1;
                    if (node == node->parent->right)
                        node->parent->bf -= 1;
                    if (node->parent->bf != 0)
                        insert_balance_factor(node->parent);
                }
            }
            ptr_node    delete_balance_factor(ptr_node node, value_type val)
            {
                if (node != _end)
                {
                    if (node->_data.first > val.first)
                        node->bf -= 1;
                    else if (node->_data.first < val.first)
                        node->bf += 1;
                    if (node->bf < -1 || node->bf > 1)
                    {
                        return rebalance(node);
                    }
                    if (node->bf == 0)
                        delete_balance_factor(node->parent, val);
                }
                return nullptr;
            }
    };

}

#endif