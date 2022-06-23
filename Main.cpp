#include <iostream>
#include "IndexTree.hpp"
#include <vector>

using namespace std;


void test2(){
    IndexTree<int> tv;
    tv.insert(0,89);
    tv.insert(1,65);
    tv.insert(2,59);

    cout<<tv.addressing(1)<<endl;
}

int main()
{
    test2();
    return 0;
}