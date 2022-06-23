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
        ~IndexTree(){};
        IndexTree(const IndexTree &){};
        IndexTree(IndexTree &&){};
        IndexTree && slice(int ,int );
        T && addressing(int);
        T && pop(int);
        void insert(int,const T&);
        int size();
    private:
        IndexAvlTreeNode<T> *root = nullptr;
};

template <typename T>
IndexTree<T>::~IndexTree(){
    if(root == nullptr)
        return;
    root = root->addressing(0);
    while (root != nullptr)
    {
        IndexAvlTreeNode<T> next = root->next;
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
IndexTree<T>::IndexTree(const IndexTree & other){
    
};

template <typename T>
IndexTree<T> && IndexTree<T>::slice(int from,int to){

}

template <typename T>
T && IndexTree<T>::addressing(int idx){
    if(root == nullptr)
        throw IdxNotExistException(idx);
    IndexAvlTreeNode<T> *res = root->addressing(idx);
    if(res == nullptr)
        throw IdxNotExistException(idx);
    return move(res->value());
}

template <typename T>
T && IndexTree<T>::pop(int idx){
    if(root == nullptr)
        throw IdxNotExistException(idx);
    IndexAvlTreeNode<T> *res = root->pop(idx);
    if(res == nullptr)
        throw IdxNotExistException(idx);
    return move(res->value());
}

template <typename T>
void IndexTree<T>::insert(int idx ,const T& data){
    if(root == nullptr)
        root = new IndexAvlTreeNode<T>(data);
    else{
        root->insert(idx,data);
    }
}


template <typename T>
int IndexTree<T>::size(){
    if(root == nullptr)
        return 0;
    return root->nb_node;
}

#define INDEXAVLTREE_INCLUDED
#endif