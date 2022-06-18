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

void test2(){
    
    IDXAvlTreeNode<int>* tmp = new IDXAvlTreeNode<int>(0,0);
    for(int i=1;i<2001;i+=7){
        tmp = tmp->insert(i%23,i%23);
    }
    for(int i=1;i<2001;i+=7){
        tmp = tmp->maintain_balance();
        cout<< tmp->pop_front()->value()<<endl;
    }
    cout<< IDXAvlTreeNode<int>::cnt<<endl;
    tmp->debug_prinf();
    //cout<< tmp->find(167)->value() <<endl;
    
}

int main()
{
    test2();
    return 0;
}