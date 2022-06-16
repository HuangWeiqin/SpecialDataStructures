#include <iostream>
#include "ListNode.hpp"
#include "AvlTreeNode.hpp"

using namespace std;


void test3(){
    ListNode<ListNode<char>> ls;
    ListNode<char> tmp(3,"xst");
    ls.push_back(tmp);
    ls.value().debug_print();
}

void test4(){
    ListNode<char> tmp(5,"xxxxx");
    ListNode<char> p;
    p.push_front('e');
    tmp = p;
    tmp.push_front('s');
    tmp.debug_print();
    p.debug_print();
}

void test5(){
    AVL_tree<int> avls;
    for(int i=0;i<128;++i){
        avls.push(3*i,3*-i);
    }
    cout<<"find "<< avls.find(125)<<endl;
    cout<<"high "<< avls.high()<<endl;
}

int main()
{
    test5();
    return 0;
}