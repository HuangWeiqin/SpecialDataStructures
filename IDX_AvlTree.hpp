#ifndef IDX_AVL_INCLUDED
#include <iostream>
#define MINIMUM -99999
#define MAXIMUM 99999
template <typename T>
class IDXAvlTreeNode
{   
    public:
    
        IDXAvlTreeNode(int id,const T& data):_fake_idx(id),_data(data){}
        IDXAvlTreeNode(const IDXAvlTreeNode<T> &);
        //IDXAvlTreeNode<T>* emplace(int,const T&);
        //IDXAvlTreeNode<T>* deplace(int);
        IDXAvlTreeNode<T>* insert(int,const T&);
        IDXAvlTreeNode<T>* pop(int,IDXAvlTreeNode<T> *&);
        IDXAvlTreeNode<T>* pop();
        IDXAvlTreeNode<T>* pop_back(IDXAvlTreeNode<T> *&);
        IDXAvlTreeNode<T>* pop_front(IDXAvlTreeNode<T> *&);
        IDXAvlTreeNode<T>* addressing(int);
        IDXAvlTreeNode<T>* maintain_balance();
        void link_next_prev();
        void replace_by(IDXAvlTreeNode<T>*);


        T& value(){return _data;}
        static int cnt;  
        void debug_prinf(){
            right_propagation();
            cout<<" real_idx:"<<idx()<<" high:"<<  get_hight() << " data:"<<_data << " radd:"<<_right_added<<endl;
            if(_left != nullptr){
                cout<<" L:"<<_left->_data;
            }
            if(_right != nullptr){
                cout<<" R:"<<_right->_data;
            }
            if(_father != nullptr){
                if(_father->_left == this)
                    cout<<" RF:"<<_father->_data;
                else
                    cout<<" LF:"<<_father->_data;
            }
            cout<<endl;
            if(_left != nullptr){
                _left->debug_prinf();
            }
            if(_right != nullptr){
                _right->debug_prinf();
            }
        }
        

    //private:
        T _data;
        IDXAvlTreeNode<T>* _left = nullptr;
        IDXAvlTreeNode<T>* _right = nullptr;
        IDXAvlTreeNode<T>* _father = nullptr;
        IDXAvlTreeNode<T>* _prev = nullptr;
        IDXAvlTreeNode<T>* _next = nullptr;
        
        int _high = 1;
        int _fake_idx = 0;
        int _right_added = 0;

        IDXAvlTreeNode<T>* rotate_left();
        IDXAvlTreeNode<T>* rotate_right();
        
        void right_propagation();
        void right_advance(int);
        IDXAvlTreeNode<T>* insert_left(int,const T&);
        IDXAvlTreeNode<T>* insert_right(int,const T&);
        void replace(IDXAvlTreeNode<T>*,IDXAvlTreeNode<T>*);
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
IDXAvlTreeNode<T>::IDXAvlTreeNode(const IDXAvlTreeNode<T> &other){
}

template <typename T>
IDXAvlTreeNode<T>* IDXAvlTreeNode<T>::insert(int new_idx,const T& data){

    if(new_idx <= idx()){
        insert_left(new_idx,data);
    }
    else{
        insert_right(new_idx,data);
    }

    return maintain_balance();
}


template <typename T>
IDXAvlTreeNode<T>* IDXAvlTreeNode<T>::insert_left(int new_idx,const T& data){
    right_advance(1);
    if(_left == nullptr){
        _left = new IDXAvlTreeNode(new_idx,data);
        _left->_father = this;
        if(_prev != nullptr){
            _prev->_next = _left;
            _left->_prev = _prev;
        }
        _prev = _left;
        _prev->_next = this;
    }
    else{
        _left = _left->insert(new_idx , data);
        _left->_father = this;
        
    }
    return _left;
}

template <typename T>
IDXAvlTreeNode<T>* IDXAvlTreeNode<T>::insert_right(int new_idx,const T& data){
    if(_right == nullptr){
        _right_added = 0;
        _right = new IDXAvlTreeNode(new_idx,data);
        _right->_father = this;
        if(_next != nullptr){
            _next->_prev = _right;
            _right->_next = _next;
        }
        _next = _right;
        _next->_prev = this;
    }
    else{
        _right = _right->insert(new_idx-_right_added, data);
        _right->_father = this;
    }
    return _right;
}


template <typename T>
void IDXAvlTreeNode<T>::right_advance(int i){
    if(_right != nullptr)
        _right_added += i;
    _fake_idx += i;
}

template <typename T>
void IDXAvlTreeNode<T>::right_propagation(){
    if(_right_added == 0) return;
    if(_right != nullptr){
        IDXAvlTreeNode<T>* node = _right;
        while (node != nullptr)
        {
            node->_fake_idx += _right_added;
            if(node->_right != nullptr)
                node->_right_added += _right_added;
            node = node->_left;
            ++cnt;
        }
    }
    
    _right_added = 0;
}

template <typename T>
void IDXAvlTreeNode<T>::link_next_prev(){
    if(_prev != nullptr){
        _prev->_next = _next;
    }
    if(_next != nullptr){
        _next->_prev = _prev;
    }
    _prev = nullptr;
    _next = nullptr;
}

template <typename T>
void IDXAvlTreeNode<T>::replace_by(IDXAvlTreeNode<T>* other){
    other->_father = nullptr;
    other->_left = nullptr;
    other->_right = nullptr;
    other->_next = nullptr;
    other->_prev = nullptr;

    if(_father != nullptr){
        if(_father->_left == this){
            _father->_left = other;
        }
        else{
            _father->_right = other;
        }
        other->_father = _father;
        _father = nullptr;
    }

    if(_left != nullptr){
        _left->_father = other;
        other->_left = _left;
        _left = nullptr;
    }

    if(_right != nullptr){
        _right->_father = other;
        other->_right = _right;
        _right = nullptr;
    }

    if(_prev != nullptr){
        _prev->_next = other;
        other->_prev = _prev;
        _prev = nullptr;
    }

    if(_next != nullptr){
        _next->_prev = other;
        other->_next = _next;
        _next = nullptr;
    }
    
    other->_right_added = _right_added;
}

template <typename T>
IDXAvlTreeNode<T>* IDXAvlTreeNode<T>::maintain_balance(){
    int high_diff = get_left_hight() - get_right_hight();
    if(high_diff >= 3){
        return rotate_left();
    }
    else if (high_diff <= -3){
        return rotate_right();
    }
    _high = get_hight();
    return this;
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
    right_propagation();

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

template <typename T>
IDXAvlTreeNode<T>* IDXAvlTreeNode<T>::addressing(int id){
    
    if(id == idx()){
        return this;
    }
    else if(id < idx()){
        if(_left != nullptr){
            return _left->addressing(id);
        }
    }
    else{
        if(_right != nullptr){
            return _right->addressing(id - _right_added);
        }
    }
    return nullptr;
}

template <typename T>
IDXAvlTreeNode<T>* IDXAvlTreeNode<T>::pop_back(IDXAvlTreeNode<T> *&root){
    if(_right == nullptr && _left == nullptr){
        _father = nullptr;
        root = nullptr;
        link_next_prev();
        _right_added = 0;
        return this;
    }
    else if(_right == nullptr){
        root = _left;
        root->_father = nullptr;
        link_next_prev();
        _right_added = 0;
        return this;
    }
    else{
        IDXAvlTreeNode<T>* res = _right->pop_back(_right);
        if(_right != nullptr)
            _right->_father = this;
        res->_fake_idx +=  _right_added;
        root = maintain_balance();
        return res;
    }
}

template <typename T>
IDXAvlTreeNode<T>* IDXAvlTreeNode<T>::pop_front(IDXAvlTreeNode<T> *&root){
    if(_right == nullptr && _left == nullptr){
        _father = nullptr;
        root = nullptr;
        link_next_prev();
        return this;
    }
    else if(_left == nullptr){
        root = _right;
        root->_father = nullptr;
        _right_added -= 1;
        right_propagation();
        link_next_prev();
        return this;
    }
    else{
        _right_added -= 1;
        IDXAvlTreeNode<T>* res = _left->pop_front(_left);
        if(_left != nullptr)
            _left->_father = this;
        root = maintain_balance();
        return res;
    }
}

template <typename T>
IDXAvlTreeNode<T>* IDXAvlTreeNode<T>::pop(){
    right_advance(-1);
    //right_propagation();
    if(_left == nullptr && _right == nullptr){
        if(_father != nullptr){
            if(_father->_left == this)
                _father->_left = nullptr;
            else
                _father->_right = nullptr;
            _father = nullptr;
        }
        link_next_prev();
        return nullptr;
    }
    else if (_left != nullptr)
    {
        IDXAvlTreeNode<T>* new_root = _left->pop_back(_left);
        if(_left != nullptr)
            _left->_father = this;
        replace_by(new_root);
        return new_root->maintain_balance();
    }
    else{
        IDXAvlTreeNode<T>* new_root = _right->pop_front(_right);
        if(_right != nullptr)
            _right->_father = this;
        new_root->_fake_idx += _right_added;
        replace_by(new_root);
        return new_root->maintain_balance();
    }
}

template <typename T>
IDXAvlTreeNode<T>* IDXAvlTreeNode<T>::pop(int id,IDXAvlTreeNode<T>* &new_root){
    if(id == idx()){
        new_root = pop();
        return this;
    }
    else if(id < idx()){
        if(_left != nullptr){
            right_advance(-1);
            IDXAvlTreeNode<T>* res = _left->pop(id , _left);
            if(_left != nullptr)
                _left->_father = this;
            new_root = maintain_balance();
            return res;
        }
    }
    else{
        if(_right != nullptr){
            IDXAvlTreeNode<T>* res = _right->pop(id - _right_added , _right);
            if(_right != nullptr)
                _right->_father = this;
            new_root = maintain_balance();
            return res;
        }
    }
    new_root = this;
    return nullptr;
}




#define IDX_AVL_INCLUDED
#endif