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

void test2(){
    IDXAvlTreeNode<int>* tmp = new IDXAvlTreeNode<int>(100,100);
    for(int i=1;i<1000;++i){
        tmp = tmp->insert(i,i);
    }
    tmp->debug_prinf();
}

int main()
{
    test2();
    return 0;
}