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
    IDXAvlTreeNode<int>* st = tmp;
    for(int i=1;i<=6;i+=1){
        tmp = tmp->insert(i,i);
    }
    //tmp->addressing(96)->debug_prinf();
    //cout<< IDXAvlTreeNode<int>::cnt <<endl;
    //cout<< tmp->pop(999,tmp)->value()<<endl;
    //cout<< tmp->addressing(999)->value()<<endl;
    cout<< tmp->pop_front(tmp)->value()<<endl;
    cout << "fucker!!!"<<endl;
    cout<< tmp->pop_front(tmp)->value()<<endl;
    cout<< tmp->pop_front(tmp)->value()<<endl;
    cout<< tmp->pop_front(tmp)->value()<<endl;
    cout<< tmp->pop_front(tmp)->value()<<endl;
    //cout<< tmp->addressing(999)->value()<<endl;
    //cout<< IDXAvlTreeNode<int>::cnt<<endl;

    
    tmp->debug_prinf();
    //IDXAvlTreeNode<int>* kd = new IDXAvlTreeNode<int>(*tmp);

    //tmp->addressing()->debug_prinf();

    
    
    //tmp->debug_prinf();
}

int main()
{
    test2();
    return 0;
}