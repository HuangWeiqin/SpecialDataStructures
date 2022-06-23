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

    for(int i = 0;i<23456;++i){
        tv.insert((i*17)%23,i);
    }

    for(int i = 0;i<2345;++i){
        tv.pop((i*17)%23);
    }

    cout << tv.size()<<" ";
    
    IndexTree<int> tvd(tv);
    tv.insert(3,45);
    for(int i=0;i<903;++i){
        cout<<tv.addressing(i)<<' '<<tvd.addressing(i)<<endl;
    }
    
}

int main()
{
    test2();
    return 0;
}