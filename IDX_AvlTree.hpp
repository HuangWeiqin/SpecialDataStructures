#ifndef IDX_AVL_INCLUDED
#include <iostream>
#include "Handler.hpp"
#include <unordered_map>
#include <sstream>
#define MAX_INT  100000
#define MIN_INT  -100000
using namespace std;
template <typename T>
class IDXAvlTreeNode
{   
    public:
    
        IDXAvlTreeNode(int id,const T& data):_fake_idx(id),_data(data){}
        IDXAvlTreeNode(IDXAvlTreeNode<T> &);
        //IDXAvlTreeNode<T>* emplace(int,const T&);
        //IDXAvlTreeNode<T>* deplace(int);
        IDXAvlTreeNode<T>* insert(int,const T&);
        IDXAvlTreeNode<T>* pop(int,IDXAvlTreeNode<T> *&);
        IDXAvlTreeNode<T>* pop();
        IDXAvlTreeNode<T>* pop_back(IDXAvlTreeNode<T> *&);
        IDXAvlTreeNode<T>* pop_front(IDXAvlTreeNode<T> *&);
        IDXAvlTreeNode<T>* addressing(int);
        IDXAvlTreeNode<T>* maintain_balance();
        IDXAvlTreeNode<T>* begin();
        IDXAvlTreeNode<T>* end();
        
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
        void link_next_prev();
        void replace_by(IDXAvlTreeNode<T>*);
    protected:
        int idx(){return _fake_idx;}
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
IDXAvlTreeNode<T>::IDXAvlTreeNode(IDXAvlTreeNode<T> &other):IDXAvlTreeNode(other._fake_idx,other._data){
    unordered_map<int,IDXAvlTreeNode<T>*> tmp_dic;
    IDXAvlTreeNode<T>* start = other.begin();
    
    IDXAvlTreeNode<T>* cur = start->_next;
    
    IDXAvlTreeNode<T>* prev_node = start;

    if(start == &other)
        prev_node = this;
    else
        prev_node = new IDXAvlTreeNode<T>(start->_fake_idx,start->_data);
    tmp_dic[prev_node->_fake_idx] = prev_node;
    start->right_propagation();
    while (cur != nullptr){
        IDXAvlTreeNode<T>* tmp_build = nullptr;
        if(cur == &other)
            tmp_build = this;
        else
            tmp_build = new IDXAvlTreeNode<T>(cur->_fake_idx,cur->_data);

        prev_node->_next = tmp_build;
        tmp_build->_prev = prev_node;
        tmp_dic[cur->_fake_idx] = tmp_build;
        cur->right_propagation();
        prev_node = tmp_build;
        cur = cur->_next;
    }

    cur = start;
    while (cur != nullptr){
        IDXAvlTreeNode<T>* tmp_build = tmp_dic[cur->_fake_idx];
        if(cur->_father != nullptr)
            tmp_build->_father = tmp_dic[cur->_father->_fake_idx];
        if(cur->_right != nullptr)
            tmp_build->_right = tmp_dic[cur->_right->_fake_idx];
        if(cur->_left != nullptr)
            tmp_build->_left = tmp_dic[cur->_left->_fake_idx];
        cur = cur->_next;
    }

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
IDXAvlTreeNode<T>* IDXAvlTreeNode<T>::begin(){
    IDXAvlTreeNode<T>* res= this;
    while (res->_prev != nullptr){
        res = res->_prev;
    }
    return res;
}

template <typename T>
IDXAvlTreeNode<T>* IDXAvlTreeNode<T>::end(){
    IDXAvlTreeNode<T>* res= this;
    while (res->_next != nullptr){
        res = res->_next;
    }
    return res;
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
    if(high_diff >= 2){
        return rotate_left();
    }
    else if (high_diff <= -2){
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

class IdxNotExistException : public exception
{
    public:
    int idx = 0;
    IdxNotExistException(int i):idx(i){}
    const char * what () const throw ()
    {
        return "idx not in TreeVector Exception" ;
    }
};

template <typename T>
class IDX_AvlTree{
    public:
        IDX_AvlTree(){};
        IDX_AvlTree(const IDX_AvlTree& other);
        ~IDX_AvlTree();
        T addressing(int);
        void insert(int,const T&);
        void modify(int,const T&);
        T pop(int);
    //private:
        IDXAvlTreeNode<T>* root = nullptr;
        int _size = 0;
        int _max_idx = 0;
        int _min_idx = 0;
        void init(int,const T&);
};

template <typename T>
IDX_AvlTree<T>::IDX_AvlTree(const IDX_AvlTree& other):
    _min_idx(other._min_idx),
    _max_idx(other._max_idx),
    _size(other._size),
    root(new IDXAvlTreeNode<T>(*other.root))
    {}

template <typename T>
IDX_AvlTree<T>::~IDX_AvlTree(){
    if(root == nullptr)
        return;
    IDXAvlTreeNode<T>* cur = root->begin();
    while (cur != nullptr){
        IDXAvlTreeNode<T>* to_delete = cur;
        cout<< "delete cur->"<<to_delete->value()<<endl;
        cur = cur->_next;
        delete to_delete;
    }
}


template <typename T>
void IDX_AvlTree<T>::init(int idx,const T& val){
    root = new IDXAvlTreeNode<T>(idx,val);
    _size = 1;
    _max_idx = idx;
    _min_idx = idx;
}

template <typename T>
void IDX_AvlTree<T>::insert(int idx,const T& val){
    if(root == nullptr){
        init(idx,val);
    }
    else{
        root  = root->insert(idx,val);
        ++_size;
        _max_idx = max(idx,_max_idx);
        _min_idx = min(idx,_min_idx);
    }
}

template <typename T>
void IDX_AvlTree<T>::modify(int idx,const T& val){
    if(root == nullptr){
        throw IdxNotExistException(idx);
    }
    else{
        IDXAvlTreeNode<T>* res  = root->addressing(idx);
        if(res != nullptr){
            res->_data = val;
        }
        else{
            throw IdxNotExistException(idx);
        }
    }
}

template <typename T>
T IDX_AvlTree<T>::pop(int idx){
    if(root == nullptr){
        throw IdxNotExistException(idx);
    }
    else{
        IDXAvlTreeNode<T>* res = root->pop(idx,root);
        if(res != nullptr){
            --_size;
            T restult = res->value(); 
            delete res;
            return restult;
        }
        throw IdxNotExistException(idx);
    }
}

template <typename T>
T IDX_AvlTree<T>::addressing(int idx){
    if(root == nullptr){
        throw IdxNotExistException(idx);
    }
    else{
        IDXAvlTreeNode<T>* res = root->addressing(idx);
        if(res != nullptr){
            return res->value();
        }
        throw IdxNotExistException(idx);
    }
}

template <typename T>
class TreeVector:public Handler<IDX_AvlTree<T>>{
    public:
        TreeVector():Handler<IDX_AvlTree<T>>(){};
        TreeVector(const TreeVector& other):
                Handler<IDX_AvlTree<T>>(other),
                start_idx(other.start_idx),
                end_idx(other.end_idx),
                _size(other._size){}
        T addressing(int);
        void push_back(const T&);
        void push_front(const T&);
        void insert(int,const T&);
        void modify(int,const T&);
        T pop(int);
        int size();
    private:
        int start_idx = MAX_INT;
        int end_idx = MIN_INT;
        int _size = 0;
        int convert_idx(int);
};

template <typename T>
T TreeVector<T>::addressing(int i){
    return this->data->addressing(convert_idx(i));
}
template <typename T>
void TreeVector<T>::push_back(const T& val){
    this->writing();
    this->data->insert(end_idx+1,val);
    ++end_idx;
    ++_size;
}
template <typename T>
void TreeVector<T>::push_front(const T& val){
    this->writing();
    this->data->insert(start_idx,val);
    ++end_idx;
    ++_size;
}
template <typename T>
void TreeVector<T>::insert(int idx,const T& val){
    this->writing();
    this->data->insert(idx,val);
    end_idx = max(idx,end_idx);
    start_idx = min(idx,start_idx);
    ++_size;
}
template <typename T>
void TreeVector<T>::modify(int idx,const T& val){
    this->writing();
    this->data->modify(idx,val);
}
template <typename T>
T TreeVector<T>::pop(int idx){
    this->writing();
    --end_idx;
    --_size;
    return this->data->pop(idx);
}

template <typename T>
int TreeVector<T>::size(){
    return _size;
}

template <typename T>
int TreeVector<T>::convert_idx(int i){
    return start_idx+i;
}


#define IDX_AVL_INCLUDED
#endif