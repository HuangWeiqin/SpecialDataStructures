#ifndef IDX_AVL_INCLUDED
#include <iostream>

template <typename T>
class IDXAvlTreeNode
{   
    public:
        IDXAvlTreeNode(int id,const T& data):_fake_idx(id),_data(data){}
        //IDXAvlTreeNode<T>* emplace(int,const T&);
        IDXAvlTreeNode<T>* insert(int,const T&);
        //IDXAvlTreeNode<T>* remove(int,const T&);
        //IDXAvlTreeNode<T>* find(int,const T&);
         void debug_prinf(){
            
            cout<<" real_idx:"<<idx()<<" high:"<<  get_hight() << " data:"<<_data;
            if(_left != nullptr){
                cout<<" L:"<<_left->_data;
            }
            if(_right != nullptr){
                cout<<" R:"<<_right->_data;
            }
            if(_father != nullptr){
                cout<<" F:"<<_father->_data;
            }
            cout<<endl;
            if(_left != nullptr){
                _left->debug_prinf();
            }
            if(_right != nullptr){
                _right->debug_prinf();
            }
        }


    private:
        T _data;
        IDXAvlTreeNode<T>* _left = nullptr;
        IDXAvlTreeNode<T>* _right = nullptr;
        IDXAvlTreeNode<T>* _father = nullptr;
        
        int _high = 1;
        int _fake_idx = 0;
        int _right_added = 0;

        IDXAvlTreeNode<T>* rotate_left();
        IDXAvlTreeNode<T>* rotate_right();
        void right_propagation();
        void right_advance();
        IDXAvlTreeNode<T>* insert_left(int,const T&);
        IDXAvlTreeNode<T>* insert_right(int,const T&);
    protected:
        int tmp_diff = 0;
        int idx(){return _fake_idx;}
        int max(int a, int b){
            if(a>=b)
                return a;
            return b;
        }
        int get_hight(){return 1+max(get_left_hight(),get_right_hight());}
        int get_left_hight(){
            if(_left == nullptr)
                return 0;
            return _left->_high;
        }
        int get_right_hight(){
            if(_right == nullptr)
                return 0;
            return _right->_high;
        }

};

template <typename T>
IDXAvlTreeNode<T>* IDXAvlTreeNode<T>::insert(int new_idx,const T& data){
    int self_idx = idx();

    if(new_idx <= self_idx){
        insert_left(new_idx,data);
    }
    else{
        insert_right(new_idx,data);
    }

    _high = get_hight();
    int high_diff = get_left_hight() - get_right_hight();
    if(high_diff > 1){
        return rotate_left();
    }
    else if (high_diff < -1){
        return rotate_right();
    }
    
    return this;
}


template <typename T>
IDXAvlTreeNode<T>* IDXAvlTreeNode<T>::insert_left(int new_idx,const T& data){
    right_advance();
    if(_left == nullptr){
        _left = new IDXAvlTreeNode(new_idx,data);
        _left->_father = this;
        return _left;
    }
    else{
        _left = _left->insert(new_idx , data);
        _left->_father = this;
        return _left;
    }
}


template <typename T>
IDXAvlTreeNode<T>* IDXAvlTreeNode<T>::insert_right(int new_idx,const T& data){
    right_propagation();
    if(_right == nullptr){
        _right = new IDXAvlTreeNode(new_idx,data);
        _right->_father = this;
        return _right;
    }
    else{
        _right = _right->insert(new_idx , data);
        _right->_father = this;
        return _right;
    }
}


template <typename T>
void IDXAvlTreeNode<T>::right_advance(){
    _right_added += 1;
    _fake_idx += 1;
}

template <typename T>
void IDXAvlTreeNode<T>::right_propagation(){
    if(_right == nullptr) return;
    IDXAvlTreeNode<T>* node = _right;
    while (node != nullptr)
    {
        node->_fake_idx += _right_added;
        node->_right_added += _right_added;
        node = node->_left;
    }
    _right_added = 0;
}


template <typename T>
IDXAvlTreeNode<T>* IDXAvlTreeNode<T>::rotate_left(){
    IDXAvlTreeNode<T>* new_root = _left;
    IDXAvlTreeNode<T>* new_left = new_root->_right;
    new_root->right_propagation();

    if(new_left != nullptr)
        new_left->_father = this;
    _left = new_left;

    new_root->_father = _father;
    new_root->_right = this;
    _father = new_root;

    
    _high = get_hight();
    new_root->_high = new_root->get_hight();
    return new_root;
}

template <typename T>
IDXAvlTreeNode<T>* IDXAvlTreeNode<T>::rotate_right(){
    IDXAvlTreeNode<T>* new_root = _right;
    IDXAvlTreeNode<T>* new_right = new_root->_left;
    new_root->right_propagation();

    if(new_right != nullptr)
        new_right->_father = this;
    _right = new_right;

    new_root->_father = _father;
    new_root->_left = this;
    _father = new_root;

    
    _high = get_hight();
    new_root->_high = new_root->get_hight();
    return new_root;
}

#define IDX_AVL_INCLUDED
#endif