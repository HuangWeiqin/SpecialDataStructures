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
    for(int i=1;i<2000;i+=1){
        tmp = tmp->insert(i,i);
    }

    cout<< IDXAvlTreeNode<int>::cnt <<endl;
    cout<< tmp->pop(999,tmp)->value()<<endl;
    cout<< tmp->addressing(999)->value()<<endl;
    cout<< tmp->pop(99,tmp)->value()<<endl;
    cout<< tmp->addressing(999)->value()<<endl;
    cout<< IDXAvlTreeNode<int>::cnt<<endl;

    IDXAvlTreeNode<int>* vc = tmp->addressing(56);
    while (vc)
    {
        cout<< vc->value() <<" ";
        vc = vc->_next;
    }
     

    
}

int main()
{
    test2();
    return 0;
}