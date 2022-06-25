#ifndef INDEXAVLTREE_INCLUDED
#include "IndexAvlTreeNode.hpp"
class IdxNotExistException : public exception
{   public:
        int idx = 0;
        IdxNotExistException(int i):idx(i){}
        const char * what () const throw ()
        {
            return "idx not in TreeVector Exception" ;
        }
};


template <typename T>
class IndexTree{
    public:
        IndexTree(){};
        ~IndexTree();
        IndexTree(const IndexTree &);
        IndexTree(IndexTree &&);
        IndexTree<T>& operator=(IndexTree<T>&&);
        IndexTree slice(int ,int );
        T addressing(int);
        T pop(int);
        void clear();
        void insert(int,const T&);
        void modify(int,const T&);
        int const size() const;
    private:
        IndexAvlTreeNode<T> *root = nullptr;
        IndexAvlTreeNode<T>* copy_tree_helper(const IndexAvlTreeNode<T>*,IndexAvlTreeNode<T>**);
};

template <typename T>
IndexTree<T>& IndexTree<T>::operator=(IndexTree<T>&& other){
        clear();
        root = other.root;
        other.root = nullptr;
}

template <typename T>
IndexAvlTreeNode<T>* IndexTree<T>::copy_tree_helper(const IndexAvlTreeNode<T>* node, IndexAvlTreeNode<T>** array){
    IndexAvlTreeNode<T>* father = new IndexAvlTreeNode<T>(*node);
    
    if(node->left != nullptr){
        IndexAvlTreeNode<T>* left = copy_tree_helper(node->left,array);
        array[node->left->idx()] = left;
        left->father = father;
        father->left = left;
    }

    if(node->right != nullptr){
        IndexAvlTreeNode<T>* right = copy_tree_helper(node->right,array + (node->idx() + 1));
        array[node->idx() + node->right->idx() + 1] = right;
        right->father = father;
        father->right = right;
    }

    return father;
}

template <typename T>
IndexTree<T>::IndexTree(const IndexTree & other){
    if(other.size() == 0)
        return;
    IndexAvlTreeNode<T>** array = new IndexAvlTreeNode<T> *[other.size()];
    root = copy_tree_helper(other.root,array);
    array[other.root->idx()] = root;

    IndexAvlTreeNode<T>* prev_node = array[0];
    for(int i=1;i<root->nb_node;++i){
        IndexAvlTreeNode<T>* cur_node = array[i];
        cur_node->prev=prev_node;
        prev_node->next = cur_node;
    }
    delete[]  array;
};

template <typename T>
void IndexTree<T>::clear(){
    if(root == nullptr)
        return;
    root = root->addressing(0);
    while (root != nullptr)
    {
        IndexAvlTreeNode<T>* next = root->next;
        delete root;
        root = next; 
    }
}


template <typename T>
IndexTree<T>::~IndexTree(){
    if(root == nullptr)
        return;
    root = root->addressing(0);
    while (root != nullptr)
    {
        IndexAvlTreeNode<T>* next = root->next;
        delete root;
        root = next; 
    }
    
};



template <typename T>
IndexTree<T>::IndexTree(IndexTree && other){
    root = other.root;
    other.root = nullptr;
};




template <typename T>
IndexTree<T> IndexTree<T>::slice(int from,int to){
    IndexTree<T> *res = new IndexTree();
    if(size() != 0)
        for(int i=max(0,from);i<min(size(),to);++i){
            res->insert(i,addressing(i));
        }
    return move(*res);
}

template <typename T>
T IndexTree<T>::addressing(int idx){
    if(root == nullptr)
        throw IdxNotExistException(idx);
    IndexAvlTreeNode<T> *res = root->addressing(idx);
    if(res == nullptr)
        throw IdxNotExistException(idx);
    return move(res->value());
}

template <typename T>
T IndexTree<T>::pop(int idx){
    if(root == nullptr)
        throw IdxNotExistException(idx);
    IndexAvlTreeNode<T> *res = root->pop(idx,root);
    if(res == nullptr)
        throw IdxNotExistException(idx);
    return move(res->value());
}

template <typename T>
void IndexTree<T>::insert(int idx ,const T& data){
    if(root == nullptr)
        root = new IndexAvlTreeNode<T>(data);
    else{
        root = root->insert(idx,data);
    }
}

template <typename T>
void IndexTree<T>::modify(int idx ,const T& data){
    if(root == nullptr)
        throw IdxNotExistException(idx);
    IndexAvlTreeNode<T> *res = root->addressing(idx);
    if(res == nullptr)
        throw IdxNotExistException(idx);
    res->data = data;
}


template <typename T>
int const IndexTree<T>::size() const{
    if(root == nullptr)
        return 0;
    return root->nb_node;
}

#define INDEXAVLTREE_INCLUDED
#endif