#include <iostream>
#include "AvlTreeNode.hpp"
#include <vector>

using namespace std;


void test2(){
    AvlTreeNode<int> node(0);
    AvlTreeNode<int> *root = &node;
    for(int i=1;i<200;++i){
        root = root->insert(i,i);
    }
    for(int i=0;i<50;++i){
        
        auto res = root->pop((i*56)%107,root);
        cout<<"remove"<<res->value()<<endl;
    }
    

    cout << root->addressing(20)->value() << endl;
}

int main()
{
    test2();
    return 0;
}