#ifndef LISTNODE_INCLUDED
#include <iostream>
#include "Handler.hpp"
using namespace std;

template <typename T>
class ListNode;

template <typename T>
class LN_MetaData{
    public:
        LN_MetaData(int s,ListNode<T> *h,ListNode<T> *t):size(s),head(h),tail(t){}
        int size = 0;
        ListNode<T> *head = nullptr;
        ListNode<T> *tail = nullptr;
        bool destroyed = false;
};

template <typename T>
class ListNode :public Handler<T>{
    public:
        ListNode():ListNode('~'){meta_info->size = 0;};
        ListNode(const T&);
        ListNode(int,const T*);
        ListNode(const ListNode<T>&);
        ~ListNode();
        virtual ListNode<T>& operator=(const ListNode<T>&);
        void emplace(int,const T*);
        void debug_print();
        void insert_right(const T&);
        void insert_left(const T&);
    private:
        ListNode(const T&,LN_MetaData<T> *);
        ListNode(const ListNode<T>&,LN_MetaData<T> *);
        LN_MetaData<T> *meta_info = nullptr;
        ListNode<T> *left = nullptr;
        ListNode<T> *right = nullptr;
        void destroy_others();
        void destroy_left();
        void destroy_right();
        ListNode<T>* copy_left(LN_MetaData<T> *);
        ListNode<T>* copy_right(LN_MetaData<T> *);
};


template <typename T>
ListNode<T>& ListNode<T>::operator=(const ListNode<T>& other){
    this->share_from(other);

    meta_info->size = other.meta_info->size;
    if(other.left != nullptr){
        left = other.left->copy_left(meta_info);
    }
    if(other.right != nullptr){
        right = other.right->copy_right(meta_info);
    }
}

template <typename T>
ListNode<T>::ListNode(const T &dt):Handler<T>(dt),meta_info(new LN_MetaData<T>(1,this,this)){}

template <typename T>
ListNode<T>::ListNode(const T &dt, LN_MetaData<T> *meta):Handler<T>(dt),meta_info(meta){}

template <typename T>
ListNode<T>::ListNode(const ListNode<T>& other):Handler<T>(other),meta_info(new LN_MetaData<T>(1,this,this)){
    meta_info->size = other.meta_info->size;
    if(other.left != nullptr){
        left = other.left->copy_left(meta_info);
    }
    if(other.right != nullptr){
        right = other.right->copy_right(meta_info);
    }
}

template <typename T>
ListNode<T>::ListNode(const ListNode<T>& other, LN_MetaData<T> *meta):Handler<T>(other),meta_info(meta){}

template <typename T>
void ListNode<T>::emplace(int nb, const T* dt){
    if(nb <= 0){
        return;
    }

    this->set_value(*dt);

    if(--nb <= 0){
        return;
    }

    if(right == nullptr)
        insert_right(*dt);

    
    if(right != nullptr)
        right->emplace(nb,++dt);
    
}


template <typename T>
ListNode<T>::ListNode(int nb, const T* ptr):ListNode<T>(*ptr){
    emplace(nb,ptr);
}


template <typename T>
ListNode<T>::~ListNode(){
    if(!meta_info->destroyed){
        meta_info->destroyed = true;
        destroy_others();
        delete meta_info;
    }
}

template <typename T>
void ListNode<T>::destroy_left(){
    if(left != nullptr){
        left->destroy_left();
        delete left;
        meta_info->head = this;
        --meta_info->size;
    }
}

template <typename T>
void ListNode<T>::destroy_right(){
    if(right != nullptr){
        right->destroy_right();
        delete right;
        meta_info->tail = this;
        --meta_info->size;
    }
}


template <typename T>
void ListNode<T>::destroy_others(){
    destroy_left();
    destroy_right();
    
}

template <typename T>
ListNode<T>* ListNode<T>::copy_left(LN_MetaData<T> *meta){
    ListNode<T>* copy = new ListNode<T>(*this,meta);
    if(left != nullptr){
        copy->left = left->copy_left(meta);
    }
    else{
        meta->head = this;
    }
    return copy;
}

template <typename T>
ListNode<T>* ListNode<T>::copy_right(LN_MetaData<T> *meta){
    ListNode<T>* copy = new ListNode<T>(*this,meta);
    if(right != nullptr){
        copy->right = right->copy_right(meta);
    }
    else{
        meta->tail = this;
    }

    return copy;
}



template <typename T>
void ListNode<T>::debug_print(){
    ListNode<T> *cur = meta_info->head;

    cout<<" size: "<<meta_info->size<<endl;
    while (cur != nullptr)
    {
        cout<<cur->value()<<" coutn: "<<cur->share_count() <<" size: "<< cur->meta_info->size<< endl;
        cur = cur->right;
    }
    cout<<endl;
}

template <typename T>
void ListNode<T>::insert_right(const T& val){
    if(meta_info->size++ == 0){
        this->set_value(val);
        return;
    }

    ListNode<T> *newcommer = new ListNode<T>(val,meta_info);
    
    if(meta_info->tail == this){
        meta_info->tail = newcommer;
        right = newcommer;
        newcommer->left = this;
    }
    else{
        newcommer->right = right;
        right->left = newcommer;
        newcommer->left = this;
        right = newcommer;
    }
}

template <typename T>
void ListNode<T>::insert_left(const T& val){
    if(meta_info->size++ == 0){
        this->set_value(val);
        return;
    }

    ListNode<T> *newcommer = new ListNode<T>(val,meta_info);
    
    if(meta_info->head == this){
        meta_info->head = newcommer;
        left = newcommer;
        newcommer->right = this;
    }
    else{
        newcommer->left = left;
        left->right = newcommer;
        newcommer->right = this;
        left = newcommer;
    }
}

#define LISTNODE_INCLUDED
#endif