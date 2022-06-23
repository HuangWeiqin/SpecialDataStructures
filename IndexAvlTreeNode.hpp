#ifndef INDEXAVLTREENODE_INCLUDED
#include <iostream>
using namespace std;
template <typename T>
class IndexTree;
template <typename T>
class IndexAvlTreeNode
{
    public:
        IndexAvlTreeNode(const T&dt):data(dt){};
        IndexAvlTreeNode(const IndexAvlTreeNode&);
        IndexAvlTreeNode<T>* insert(int,const T&);
        IndexAvlTreeNode<T>* pop(int,IndexAvlTreeNode<T> *&);
        IndexAvlTreeNode<T>* addressing(int);
        T value(){return data;}
    protected:
        T data;
        int high = 0;
        int nb_node = 1;
        IndexAvlTreeNode<T> *father = nullptr;
        IndexAvlTreeNode<T> *left = nullptr;
        IndexAvlTreeNode<T> *right = nullptr;
        IndexAvlTreeNode<T> *prev = nullptr;
        IndexAvlTreeNode<T> *next = nullptr;
        
        int left_high();
        int right_high();
        int idx() const;
        
        void insert_left(int,const T&);
        void insert_right(int,const T&);
        IndexAvlTreeNode<T> * rotate_left();
        IndexAvlTreeNode<T> * rotate_right();
        IndexAvlTreeNode<T> * maintain_balance();

        void link_prev_next();
        void link_left(IndexAvlTreeNode<T> *);
        void link_right(IndexAvlTreeNode<T> *);
        void update_high();
        void update_nb();
        
        void replace_self_by(IndexAvlTreeNode<T> *);
        IndexAvlTreeNode<T> * pop_self();
        IndexAvlTreeNode<T> * left_extrema();
        IndexAvlTreeNode<T> * right_extrema();
        IndexAvlTreeNode<T> * pop_back(IndexAvlTreeNode<T> *&);
        IndexAvlTreeNode<T> * pop_front(IndexAvlTreeNode<T> *&);

    private:
        friend class IndexTree<T>;
};

template <typename T>
IndexAvlTreeNode<T>::IndexAvlTreeNode(const IndexAvlTreeNode& other):
data(other.data),
nb_node(other.nb_node),
high(other.high){}

template <typename T>
IndexAvlTreeNode<T> * IndexAvlTreeNode<T>::pop_back(IndexAvlTreeNode<T> *& root){
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
        IndexAvlTreeNode<T> * res = right->pop_back(right);
        if(right != nullptr){
            right->father = this;
        }
        root = maintain_balance();
        return res;
    }
}


template <typename T>
IndexAvlTreeNode<T> * IndexAvlTreeNode<T>::pop_front(IndexAvlTreeNode<T> *& root){
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
        IndexAvlTreeNode<T> * res = left->pop_front(left);
        if(left != nullptr){
            left->father = this;
        }
        root = maintain_balance();
        return res;
    }
}


template <typename T>
IndexAvlTreeNode<T> * IndexAvlTreeNode<T>:: pop_self(){
    if(left == nullptr && right == nullptr){
        link_prev_next();
        replace_self_by(nullptr);
        return nullptr;
    }
    else if (left != nullptr){
        IndexAvlTreeNode<T>* new_root = left->pop_back(left);
        if(left != nullptr){
            left->father = this;
        }
        replace_self_by(new_root);
        return new_root->maintain_balance();
    }
    else{
        IndexAvlTreeNode<T>* new_root = right->pop_front(right);
        if(right != nullptr){
            right->father = this;
        }
        replace_self_by(new_root);
        return new_root->maintain_balance();
    }
}

template <typename T>
void IndexAvlTreeNode<T>:: replace_self_by(IndexAvlTreeNode<T> *other){
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
IndexAvlTreeNode<T> * IndexAvlTreeNode<T>::left_extrema(){
    IndexAvlTreeNode<T> * res = this;
    while (res->left != nullptr){
        res = res->left;
    }
    return res;
}

template <typename T>
IndexAvlTreeNode<T> * IndexAvlTreeNode<T>::right_extrema(){
    IndexAvlTreeNode<T> * res = this;
    while (res->right != nullptr){
        res = res->right;
    }
    return res;
}

template <typename T>
void IndexAvlTreeNode<T>:: link_prev_next(){
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
void IndexAvlTreeNode<T>:: link_left(IndexAvlTreeNode<T> * newer){
    if(prev != nullptr){
        prev->next = newer;
        newer->prev = prev;
    }
    newer->next = this;
    prev = newer;
}

template <typename T>
void IndexAvlTreeNode<T>:: link_right(IndexAvlTreeNode<T> * newer){
    if(next != nullptr){
        next->prev = newer;
        newer->next = next;
    }
    newer->prev = this;
    next = newer;
}

template <typename T>
void IndexAvlTreeNode<T>:: update_nb(){
    nb_node = 1;
    if(left != nullptr){
        nb_node += left->nb_node;
    }
    if(right != nullptr){
        nb_node += right->nb_node;
    }
}

template <typename T>
void IndexAvlTreeNode<T>:: update_high(){
    high = max(left_high(),right_high()) + 1;
}

template <typename T>
int IndexAvlTreeNode<T>:: left_high(){
    if(left == nullptr)
        return 0;
    return left->high;
}
template <typename T>
int IndexAvlTreeNode<T>:: right_high(){
    if(right == nullptr)
        return 0;
    return right->high;
}

template <typename T>
int IndexAvlTreeNode<T>:: idx() const{
    if(left == nullptr)
        return 0;
    return left->nb_node;
}

template <typename T>
IndexAvlTreeNode<T> * IndexAvlTreeNode<T>:: addressing(int id){
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
IndexAvlTreeNode<T> * IndexAvlTreeNode<T>:: pop(int id,IndexAvlTreeNode<T> *&root){
    //nb_node -= 1;
    if(id == idx()){
        root = pop_self();
        return this;
    }
    else if(id < idx()){
        IndexAvlTreeNode<T> * res = left->pop(id,left);
        if(left != nullptr)
            left->father = this;
        root = maintain_balance();
        return res;
    }
    else{
        IndexAvlTreeNode<T> * res = right->pop(id - idx() - 1,right);
        if(right != nullptr)
            right->father = this;
        root = maintain_balance();
        return res;
    }

    return maintain_balance();
}

template <typename T>
IndexAvlTreeNode<T>* IndexAvlTreeNode<T>::insert(int id,const T& dt){

    if(id <= idx()){
        insert_left(id,dt);
    }
    else{
        insert_right(id,dt);
    }

    return maintain_balance();
}

template <typename T>
void IndexAvlTreeNode<T>:: insert_left(int id,const T& dt){
    if(left == nullptr){
        left = new IndexAvlTreeNode(dt);
        link_left(left);
    }
    else{
        left = left->insert(id,dt);
    }
    left->father = this;
}
template <typename T>
void IndexAvlTreeNode<T>:: insert_right(int id,const T& dt){
    if(right == nullptr){
        right = new IndexAvlTreeNode(dt);
        link_right(right);
    }
    else{
        right = right->insert(id - idx() - 1,dt);
    }
    right->father = this;
}

template <typename T>
IndexAvlTreeNode<T> * IndexAvlTreeNode<T>:: rotate_left(){
    IndexAvlTreeNode<T> * new_root = left;
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
IndexAvlTreeNode<T> * IndexAvlTreeNode<T>:: rotate_right(){
    IndexAvlTreeNode<T> * new_root = right;
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
IndexAvlTreeNode<T> * IndexAvlTreeNode<T>:: maintain_balance(){
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

#define INDEXAVLTREENODE_INCLUDED
#endif