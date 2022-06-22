#include <iostream>
#include "IDX_AvlTree.hpp"
#include <vector>

using namespace std;


template <typename T>
int IDXAvlTreeNode<T>::cnt = 0;

void help(IDXAvlTreeNode<int>* tmp,int it){
    for(int i=it-10;i<=it+15;i+=1){
        auto res = tmp->addressing(i);
        if(res)
            cout<<res->value()<<' ';
        else
            cout << "? ";
    }
    cout << endl;
}

void help2(IDXAvlTreeNode<int>* tmp,int it){
    auto res = tmp;
    for(int i=0;i<=it;i+=1){
        if(res){
            cout<<res->value()<<' ';
            res = res->_next;
        }
        else
            break;
    }
    cout <<"fishi"<< endl;
}


bool compare_with_vec(vector<int> &vec,IDXAvlTreeNode<int>* tmp){
    vector<int>::iterator iter = vec.begin();
    while (tmp != nullptr)
    {
        
        if(*iter != tmp->value()){
            cout << *iter<<" != "<<tmp->value()<<endl;
            cout<<" !!!!!!!!!!!!"<<endl;
            return false;
        }
            
        ++iter;
        tmp = tmp->_next;
        //cout << endl;
    }
    return true;
}

class ta{
    public:
        ~ta(){
            cout <<"fucker"<<endl;
        }
};

ta&& get(){
    ta &a= *(new ta());
    return a;
}

void test2(){
    ta &b = get();
    //delete &b;
}

int main()
{
    test2();
    cout<<"sds"<<endl;
    return 0;
}