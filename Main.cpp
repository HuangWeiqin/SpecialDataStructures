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
    avls.push(0,0);
    avls.push(9999,9999);
    avls.push(8888,8888);

    cout<<"find "<< avls.find(100)<<endl;
    cout<<"high "<< avls.high()<<endl;
    avls.root->debug_prinf();
}

int main()
{
    test5();
    return 0;
}