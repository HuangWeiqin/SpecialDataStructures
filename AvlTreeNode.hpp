#ifndef AVLTREENODE_INCLUDED
#include <iostream>
using namespace std;
template <typename T>
class AvlTreeNode
{
    public:
        AvlTreeNode(const T&dt):data(dt){};
        AvlTreeNode<T>* insert(int,const T&);
        AvlTreeNode<T>* pop(int,AvlTreeNode<T> *&);
        AvlTreeNode<T>* addressing(int);
        T &value(){return data;}
    protected:
        T data;
        int nb_node = 1;
        AvlTreeNode<T> *father = nullptr;
        AvlTreeNode<T> *left = nullptr;
        AvlTreeNode<T> *right = nullptr;
        AvlTreeNode<T> *prev = nullptr;
        AvlTreeNode<T> *next = nullptr;
        int high = 0;
        
        int left_high();
        int right_high();
        int idx();
        
        void insert_left(int,const T&);
        void insert_right(int,const T&);
        AvlTreeNode<T> * rotate_left();
        AvlTreeNode<T> * rotate_right();
        AvlTreeNode<T> * maintain_balance();

        void link_prev_next();
        void link_left(AvlTreeNode<T> *);
        void link_right(AvlTreeNode<T> *);
        void update_high();
        void update_nb();
        
        void replace_self_by(AvlTreeNode<T> *);
        AvlTreeNode<T> * pop_self();
        AvlTreeNode<T> * left_extrema();
        AvlTreeNode<T> * right_extrema();
        AvlTreeNode<T> * pop_back(AvlTreeNode<T> *&);
        AvlTreeNode<T> * pop_front(AvlTreeNode<T> *&);
};

template <typename T>
AvlTreeNode<T> * AvlTreeNode<T>::pop_back(AvlTreeNode<T> *& root){
    if(left == nullptr && right == nullptr){
        father = nullptr;
        root = nullptr;
        link_prev_next();
        return this;
    }
    else if (right == nullptr)
    {
        root = left;
        link_prev_next();
        left = nullptr;
        father = nullptr;
        return this;
    }
    else{
        AvlTreeNode<T> * res = right->pop_back(right);
        if(right != nullptr){
            right->father = this;
        }
        root = maintain_balance();
        return res;
    }
}


template <typename T>
AvlTreeNode<T> * AvlTreeNode<T>::pop_front(AvlTreeNode<T> *& root){
    if(left == nullptr && right == nullptr){
        father = nullptr;
        root = nullptr;
        link_prev_next();
        return this;
    }
    else if (left == nullptr)
    {
        root = right;
        link_prev_next();
        right = nullptr;
        father = nullptr;
        return this;
    }
    else{
        AvlTreeNode<T> * res = left->pop_front(left);
        if(left != nullptr){
            left->father = this;
        }
        root = maintain_balance();
        return res;
    }
}


template <typename T>
AvlTreeNode<T> * AvlTreeNode<T>:: pop_self(){
    if(left == nullptr && right == nullptr){
        link_prev_next();
        replace_self_by(nullptr);
        return nullptr;
    }
    else if (left != nullptr){
        AvlTreeNode<T>* new_root = left->pop_back(left);
        if(left != nullptr){
            left->father = this;
        }
        replace_self_by(new_root);
        return new_root->maintain_balance();
    }
    else{
        AvlTreeNode<T>* new_root = right->pop_front(right);
        if(right != nullptr){
            right->father = this;
        }
        replace_self_by(new_root);
        return new_root->maintain_balance();
    }
}

template <typename T>
void AvlTreeNode<T>:: replace_self_by(AvlTreeNode<T> *other){
    if(other != nullptr){
        other->father = father;
        other->left = left;
        other->right = right;
        other->prev = prev;
        other->next = next;
        other->nb_node = nb_node;
        other->nb_node = high;
    }

    if(father != nullptr){
        if(father->left == this)
            father->left = other;
        else
            father->right = other;
        father = nullptr;
    }

    if(left != nullptr){
        left->father = other;
        left = nullptr;
    }

    if(right != nullptr){
        right->father = other;
        right = nullptr;
    }

    if(prev != nullptr){
        prev->next = other;
        prev = nullptr;
    }

    if(next != nullptr){
        next->prev = other;
        next = nullptr;
    }
}

template <typename T>
AvlTreeNode<T> * AvlTreeNode<T>::left_extrema(){
    AvlTreeNode<T> * res = this;
    while (res->left != nullptr){
        res = res->left;
    }
    return res;
}

template <typename T>
AvlTreeNode<T> * AvlTreeNode<T>::right_extrema(){
    AvlTreeNode<T> * res = this;
    while (res->right != nullptr){
        res = res->right;
    }
    return res;
}

template <typename T>
void AvlTreeNode<T>:: link_prev_next(){
    if(prev != nullptr){
        prev->next = next;
    }
    if(next != nullptr){
        next->prev = prev;
    }
    next = nullptr;
    prev = nullptr;
}

template <typename T>
void AvlTreeNode<T>:: link_left(AvlTreeNode<T> * newer){
    if(prev != nullptr){
        prev->next = newer;
        newer->prev = prev;
    }
    newer->next = this;
    prev = newer;
}

template <typename T>
void AvlTreeNode<T>:: link_right(AvlTreeNode<T> * newer){
    if(next != nullptr){
        next->prev = newer;
        newer->next = next;
    }
    newer->prev = this;
    next = newer;
}

template <typename T>
void AvlTreeNode<T>:: update_nb(){
    nb_node = 1;
    if(left != nullptr){
        nb_node += left->nb_node;
    }
    if(right != nullptr){
        nb_node += right->nb_node;
    }
}

template <typename T>
void AvlTreeNode<T>:: update_high(){
    high = max(left_high(),right_high()) + 1;
}

template <typename T>
int AvlTreeNode<T>:: left_high(){
    if(left == nullptr)
        return 0;
    return left->high;
}
template <typename T>
int AvlTreeNode<T>:: right_high(){
    if(right == nullptr)
        return 0;
    return right->high;
}

template <typename T>
int AvlTreeNode<T>:: idx(){
    if(left == nullptr)
        return 0;
    return left->nb_node;
}

template <typename T>
AvlTreeNode<T> * AvlTreeNode<T>:: addressing(int id){
    if(id == idx()){
        return this;
    }
    if(id <= idx()){
        if(left != nullptr)
            return left->addressing(id);
    }
    else{
        if(right != nullptr)
            return right->addressing(id - idx() - 1);
    }
    return nullptr;
}

template <typename T>
AvlTreeNode<T> * AvlTreeNode<T>:: pop(int id,AvlTreeNode<T> *&root){
    nb_node -= 1;
    if(id == idx()){
        root = pop_self();
        return this;
    }
    else if(id < idx()){
        AvlTreeNode<T> * res = left->pop(id,left);
        if(left != nullptr)
            left->father = this;
        root = maintain_balance();
        return res;
    }
    else{
        AvlTreeNode<T> * res = right->pop(id - idx() - 1,right);
        if(right != nullptr)
            right->father = this;
        root = maintain_balance();
        return res;
    }

    return maintain_balance();
}

template <typename T>
AvlTreeNode<T>* AvlTreeNode<T>::insert(int id,const T& dt){
    nb_node += 1;

    if(id <= idx()){
        insert_left(id,dt);
    }
    else{
        insert_right(id,dt);
    }

    return maintain_balance();
}

template <typename T>
void AvlTreeNode<T>:: insert_left(int id,const T& dt){
    if(left == nullptr){
        left = new AvlTreeNode(dt);
        link_left(left);
    }
    else{
        left = left->insert(id,dt);
    }
    left->father = this;
}
template <typename T>
void AvlTreeNode<T>:: insert_right(int id,const T& dt){
    if(right == nullptr){
        right = new AvlTreeNode(dt);
        link_right(right);
    }
    else{
        right = right->insert(id - idx() - 1,dt);
    }
    right->father = this;
}

template <typename T>
AvlTreeNode<T> * AvlTreeNode<T>:: rotate_left(){
    AvlTreeNode<T> * new_root = left;
    left = new_root->right;
    if(left != nullptr)
        left->father = this;
    new_root->right = this;
    father = new_root;
    new_root->father=father;
    
    update_high();
    update_nb();
    new_root->update_high();
    new_root->update_nb();
    
    return new_root;
}
template <typename T>
AvlTreeNode<T> * AvlTreeNode<T>:: rotate_right(){
    AvlTreeNode<T> * new_root = right;
    right = new_root->left;
    if(right != nullptr)
        right->father = this;
    new_root->left = this;
    father = new_root;
    new_root->father=nullptr;

    update_high();
    update_nb();
    new_root->update_high();
    new_root->update_nb();
    return new_root;
}

template <typename T>
AvlTreeNode<T> * AvlTreeNode<T>:: maintain_balance(){
    update_high();
    update_nb();
    int high_diff = left_high() - right_high();
    if(high_diff >= 2){
        return rotate_left();
    }
    else if(high_diff <= -2){
        return rotate_right();
    }
    return this;
}

#define AVLTREENODE_INCLUDED
#endif