#include <iostream>
#include "ListNode.hpp"

using namespace std;


void test3(){
    ListNode<ListNode<char>> ls;
    ListNode<char> tmp(3,"xst");
    ls.push_back(tmp);
    ls.value().debug_print();
}

void test4(){
    ListNode<char> tmp(4,"xxxx");
    ListNode<char> p(3,"sdf");
    tmp = p;
    tmp.push_front('x');
    tmp.debug_print();
    p.debug_print();
}

int main()
{
    test4();
    return 0;
}