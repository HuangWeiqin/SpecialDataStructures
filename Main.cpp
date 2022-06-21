#include <iostream>
#include "ListNode.hpp"
#include "IDX_AvlTree.hpp"

using namespace std;


void test(){
    ListNode<ListNode<char>> ls;
    ListNode<char> tmp(3,"xst");
    ls.push_back(tmp);
    ls.value().debug_print();
}

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


void test2(){
    
    IDXAvlTreeNode<int>* tmp = new IDXAvlTreeNode<int>(0,0);

    for(int i=0;i<2000;i+=1){
        tmp = tmp->insert(i,i);
    }
    
    for(int i=0;i<=500;++i){
        auto res = tmp->pop(i,tmp);
        if(res)
            cout<<'<'<<i<<'>'<< res->value()<<" -> ";
        help(tmp,i);
        delete res;
    }
    help2(tmp->addressing(109),10);


    //tmp->addressing(10)->debug_prinf();
    //cout<<"!!!!!!"<< tmp->pop(0,tmp)->value()<<endl;
    //tmp->debug_prinf();
    //cout<< tmp->addressing(993)->value()<<endl;
    //cout<< tmp->pop(99,tmp)->value()<<endl;
    //cout<< tmp->addressing(999)->value()<<endl;
    cout<< IDXAvlTreeNode<int>::cnt<<endl;
    
     
}

int main()
{
    test2();
    return 0;
}