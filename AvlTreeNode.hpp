#ifndef AVLTREENODE_INCLUDED
#include <iostream>
template <typename T>
class AvlTreeNode
{
    public:
        AvlTreeNode(int,const T&);
        AvlTreeNode<T>* real_push(int,const T&);
        AvlTreeNode<T>* push(int,const T&, int);
        AvlTreeNode<T>* remove(){return this;};
        int high();
        AvlTreeNode<T> * find(int v);
        T &value(){return data;}
        void debug_prinf(){
            
            cout<<" real_idx:"<<real_idx()<<" fake: "<< fake_idx<<" offset:"<<offset << " data:"<<data;
            if(left != nullptr){
                cout<<" L:"<<left->data;
            }
            if(right != nullptr){
                cout<<" R:"<<right->data;
            }
            if(father != nullptr){
                cout<<" F:"<<father->data;
            }
            cout<<endl;
            if(left != nullptr){
                left->debug_prinf();
            }
            if(right != nullptr){
                right->debug_prinf();
            }
        }
        bool debug = false;
    private:
        int offset;
        int insert_nb;
        bool inserted;
        int fake_idx;
        T data;
        AvlTreeNode<T> *father = nullptr;
        AvlTreeNode<T> *left = nullptr;
        AvlTreeNode<T> *right = nullptr;

        int diff;
        int _high=1;

    protected:
        
        int left_high();
        int right_high();
        int get_offset();
        
        AvlTreeNode<T> * left_push(int,const T&, int);
        AvlTreeNode<T> * right_push(int,const T&, int);
        AvlTreeNode<T> * rotate_left();
        AvlTreeNode<T> * rotate_right();
        void update_high();
        

        int real_idx(){
            return fake_idx + get_offset();
        }
};

template <typename T>
AvlTreeNode<T>::AvlTreeNode(int v,const T& dt):fake_idx(v),data(dt),offset(0),insert_nb(0),inserted(false),diff(0){}

template <typename T>
AvlTreeNode<T>* AvlTreeNode<T>::push(int v,const T& dt,int insert){
    
    int idx = fake_idx + get_offset();
    if(debug) cout<< "push "<<v<<" to "<< idx <<endl;
    insert_nb += insert;
    AvlTreeNode<T>* res = this;
    if(v == idx){
        if(insert==0){
            data = dt;
        }
        else if(insert>0){
            left  = left_push(v ,dt, insert);
            if(left != nullptr)
                left->father = this;
            if(left_high() - right_high() > 1){
                res =  rotate_left();
            }
        }
        else{
            update_high();
            return remove();
        }
    }
    else if (v < idx){
        left  = left_push(v ,dt, insert);
        if(left != nullptr)
            left->father = this;
        if(left_high() - right_high() > 1){
            res =  rotate_left();
        }
    }
    else{
        right = right_push(v - offset ,dt, insert);
        if(right != nullptr)
            right->father = this;
        if(right_high() - left_high() > 1){
            res = rotate_right();
        }
    }
    update_high();
    return res;
}


template <typename T>
AvlTreeNode<T>* AvlTreeNode<T>::real_push(int real_idx,const T& dt){
    return push(real_idx,dt,1);
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
int AvlTreeNode<T>:: get_offset(){
    if(father == nullptr){
        if(left != nullptr)
            offset = left->insert_nb + left->inserted;
    }
    else if(father->left == this){
        if(right == nullptr)
            offset = father->offset - inserted;
        else
            offset = father->offset - right->insert_nb - inserted;
    }
    else{
        if(left == nullptr)
            offset = father->offset;
        else
            offset = left->insert_nb + father->offset;
    }
    return offset;
}


template <typename T>
AvlTreeNode<T> * AvlTreeNode<T>:: left_push(int v,const T& bt,int insert){
    if(left == nullptr){
        if(insert<0)
            return nullptr;
        AvlTreeNode<T> *res = new AvlTreeNode(v,bt);
        if(insert > 0)
            res->inserted = true;
        return res;
    }
    else{
        return left->push(v,bt,insert);
    }

}
template <typename T>
AvlTreeNode<T> * AvlTreeNode<T>:: right_push(int v,const T& bt,int insert){
    if(right== nullptr){
        if(insert<0)
            return nullptr;
        AvlTreeNode<T> *res = new AvlTreeNode(v,bt);
        if(insert > 0)
            res->inserted = true;
        return res;
    }
    else{
        return right->push(v,bt,insert);
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
    cout<<"rotate_left "<<data<<endl;
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
    cout<<"rotate_right new root"<<new_root->data<<endl;
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

    insert_nb = (int)inserted;
    if(left != nullptr){
        insert_nb += left->insert_nb;
    }
    else if(right != nullptr){
        insert_nb += right->insert_nb;
    }
    get_offset();
}

template <typename T>
AvlTreeNode<T> * AvlTreeNode<T>:: find(int v){
    int idx = fake_idx + offset;
    diff = abs(v - idx);

    if(idx == v){
        return this;
    }
    else if (v < idx)
    {
        if(left != nullptr){
            AvlTreeNode<T> *tmp = left->find(v);
            if(diff < tmp->diff){
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
            if(diff < tmp->diff){
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
        void push(int,const T&,int);
        T& find(int);
        int high(){return root->high();}
};

template <typename T>
void AVL_tree<T>:: push(int fake_idx,const T& dt,int insert){
    if(root == nullptr){
        root = new AvlTreeNode<T>(fake_idx,dt);
    }
    else{
        root = root->push(fake_idx,dt,insert);
    }
    
}

template <typename T>
T& AVL_tree<T>:: find(int fake_idx){
    return root->find(fake_idx)->value();
}


#define AVLTREENODE_INCLUDED
#endif