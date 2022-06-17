#ifndef AVLTREENODE_INCLUDED
#include <iostream>
template <typename T>
class AvlTreeNode
{
    public:
        AvlTreeNode(int,const T&);
        AvlTreeNode<T>* push(int,const T&);
        int high();
        AvlTreeNode<T> * find(int v);
        T &value(){return data;}
        void debug_prinf(){
            cout<<" v:"<<val<<" H:"<<_high;
            if(left != nullptr){
                cout<<" L:"<<left->val;
            }
            if(right != nullptr){
                cout<<" R:"<<right->val;
            }
            if(father){
                cout<<" F:"<<father->val;
            }
            cout<<endl;
            if(left != nullptr){
                left->debug_prinf();
            }
            if(right != nullptr){
                right->debug_prinf();
            }
        }

    private:
        int val;
        T data;
        AvlTreeNode<T> *father = nullptr;
        AvlTreeNode<T> *left = nullptr;
        AvlTreeNode<T> *right = nullptr;

    protected:
        int _high=1;
        int left_high();
        int right_high();
        AvlTreeNode<T> * left_push(int,const T&);
        AvlTreeNode<T> * right_push(int,const T&);
        AvlTreeNode<T> * rotate_left();
        AvlTreeNode<T> * rotate_right();
        void update_high();

};

template <typename T>
AvlTreeNode<T>::AvlTreeNode(int v,const T& dt):val(v),data(dt){}

template <typename T>
AvlTreeNode<T>* AvlTreeNode<T>::push(int v,const T& dt){
    AvlTreeNode<T>* res = this;
    if(v == val){
        data = dt;
    }
    else if (v < val){
        left  = left_push(v,dt);
        left->father = this;
        if(left_high() - right_high() > 1){
            res =  rotate_left();
        }
    }
    else{
        right = right_push(v,dt);
        right->father = this;
        if(right_high() - left_high() > 1){
            res = rotate_right();
        }
    }
    update_high();
    return res;
}

template <typename T>
int AvlTreeNode<T>:: high(){
    return _high;
}
template <typename T>
int AvlTreeNode<T>:: left_high(){
    if(left == nullptr)
        return 0;
    return left->high();
}
template <typename T>
int AvlTreeNode<T>:: right_high(){
    if(right == nullptr)
        return 0;
    return right->high();
}

template <typename T>
AvlTreeNode<T> * AvlTreeNode<T>:: left_push(int v,const T& bt){
    if(left == nullptr){
        return new AvlTreeNode(v,bt);
    }
    else{
        return left->push(v,bt);
    }

}
template <typename T>
AvlTreeNode<T> * AvlTreeNode<T>:: right_push(int v,const T& bt){
    if(right== nullptr){
        return new AvlTreeNode(v,bt);
    }
    else{
        return right->push(v,bt);
    }
}
template <typename T>
AvlTreeNode<T> * AvlTreeNode<T>:: rotate_left(){
    AvlTreeNode<T> * new_root = left;
    left = new_root->right;
    if(left != nullptr)
        left->father = this;
    new_root->right = this;
    father = new_root;
    new_root->father=nullptr;
    update_high();
    new_root->update_high();
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
    new_root->update_high();
    return new_root;
}

template <typename T>
void AvlTreeNode<T>:: update_high(){
    int hl = left_high();
    int hr = right_high();
    if(hl > hr){
        _high = hl+1;
    }
    else{
        _high = hr+1;
    }
}

template <typename T>
AvlTreeNode<T> * AvlTreeNode<T>:: find(int v){
    if(val == v){
        return this;
    }
    else if (v < val)
    {
        if(left != nullptr){
            AvlTreeNode<T> *tmp = left->find(v);
            if(abs(v - val) < abs(v - tmp->val)){
                return this;
            }
            else{
                return tmp;
            }
        }else{
           return this;
        }
    }
    else{
        if(right != nullptr){
            AvlTreeNode<T> *tmp = right->find(v);
            if(abs(v - val) < abs(v - tmp->val)){
                return this;
            }
            else{
                return tmp;
            }
        }
        else{
            return this;
        }
    }
    
}

template <typename T>
class AVL_tree{
    public:
        AvlTreeNode<T> *root = nullptr;
        void push(int,const T&);
        T& find(int);
        int high(){return root->high();}
};

template <typename T>
void AVL_tree<T>:: push(int val,const T& dt){
    if(root == nullptr){
        root = new AvlTreeNode<T>(val,dt);
    }
    else{
        root = root->push(val,dt);
    }
    
}

template <typename T>
T& AVL_tree<T>:: find(int val){
    return root->find(val)->value();
}


#define AVLTREENODE_INCLUDED
#endif