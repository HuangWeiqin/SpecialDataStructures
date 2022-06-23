#include <iostream>
#include "IndexTree.hpp"
#include <vector>

using namespace std;


void test2(){
    IndexTree<int> tv;
    //tv.insert(0,89);
    //tv.insert(1,65);
    //tv.insert(2,59);

    for(int i = 0;i<25;++i){
        tv.insert(i,i);
    }

    for(int i = 0;i<1190;++i){
        tv.insert((i*17)%23,i);
    }

    for(int i = 0;i<234;++i){
        tv.pop((i*17)%23);
    }

    cout << tv.size()<<" ";
    
    IndexTree<int> tvd(tv);
}

int main()
{
    test2();
    return 0;
}