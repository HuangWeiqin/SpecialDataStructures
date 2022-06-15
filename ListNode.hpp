#ifndef LISTNODE_INCLUDED
#include <iostream>

template <typename T>
class ListNode;

template <typename T>
class LN_MetaData{
    public:
        LN_MetaData(int s,ListNode<T> *h,ListNode<T> *t):size(s),head(h),tail(t){}
        int size = 0;
        ListNode<T> *head = nullptr;
        ListNode<T> *tail = nullptr;
};

template <typename T>
class ListNode
{
    public:
        ListNode(const T&);
        ListNode(int,const T*);
        ListNode(const ListNode<T>&);
        ~ListNode();
        void emplace(int,const T*);
        void debug_print();
    private:
        ListNode(const T&,LN_MetaData<T> *);
        T data;
        LN_MetaData<T> *meta_info = nullptr;
        ListNode<T> *left = nullptr;
        ListNode<T> *right = nullptr;
        void destroy_all();
        void destroy_left();
        void destroy_right();
        ListNode<T>* copy_left(LN_MetaData<T> *);
        ListNode<T>* copy_right(LN_MetaData<T> *);
};





template <typename T>
ListNode<T>::ListNode(const T &dt):data(dt),meta_info(new LN_MetaData<T>(1,this,this)){}

template <typename T>
ListNode<T>::ListNode(const T &dt, LN_MetaData<T> *meta):data(dt),meta_info(meta){}

template <typename T>
ListNode<T>::ListNode(const ListNode<T>& other):ListNode<T>(other.data){
    meta_info->size = other.meta_info->size;
    if(other.left != nullptr){
        left = other.left->copy_left(meta_info);
    }
    if(other.right != nullptr){
        right = other.right->copy_right(meta_info);
    }
}

template <typename T>
void ListNode<T>::emplace(int nb, const T* dt){
    if(nb <= 0){
        return;
    }

    data = *dt;

    if(--nb <= 0){
        return;
    }

    if(right == nullptr){
        right = new ListNode<T>(*dt,meta_info);
        right->left = this;
        ++meta_info->size;
        meta_info->tail = this;
    }
    
    right->emplace(nb,++dt);
    
}


template <typename T>
ListNode<T>::ListNode(int nb, const T* ptr):ListNode<T>(*ptr){
    emplace(nb,ptr);
}


template <typename T>
ListNode<T>::~ListNode(){
    if(meta_info->head == this){
        delete meta_info;
    }
}

template <typename T>
void ListNode<T>::destroy_left(){
    if(left != nullptr){
        left->destroy_left();
        delete left;
    }
}

template <typename T>
void ListNode<T>::destroy_right(){
    if(right != nullptr){
        right->destroy_right();
        delete right;
    }
}


template <typename T>
void ListNode<T>::destroy_all(){
    destroy_left();
    destroy_right();
    delete this;
}

template <typename T>
ListNode<T>* ListNode<T>::copy_left(LN_MetaData<T> *meta){
    ListNode<T>* res = new ListNode<T>(data,meta);
    if(left != nullptr){
        res->left = left->copy_left(meta);
    }
    else{
        meta->head = this;
    }
    return res;
}

template <typename T>
ListNode<T>* ListNode<T>::copy_right(LN_MetaData<T> *meta){
    ListNode<T>* res = new ListNode<T>(data,meta);
    if(right != nullptr){
        res->right = right->copy_right(meta);
    }
    else{
        meta->tail = this;
    }

    return res;
}


template <typename T>
void ListNode<T>::debug_print(){
    ListNode<T> *cur = meta_info->head;

    cout<<" size: "<<meta_info->size<<endl;
    cout<<"  data: ";
    while (cur != nullptr)
    {
        cout<<cur->data<<' ';
        cur = cur->right;
    }
    cout<<endl;
}


#define LISTNODE_INCLUDED
#endif