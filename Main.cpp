#include <iostream>
#include "IndexTree.hpp"
#include <vector>
#include <map>
#include <set>
#include "TreeVector.hpp"

using namespace std;


void test2(){
    TreeVector<int> tv;
    vector<int> vc;
    set<int> sc;
    //tv.insert(0,89);
    //tv.insert(1,65);
    //tv.insert(2,59);
    int nb = 3000;

    for(int i = 0;i<3006;++i){
        tv.insert(i,i);
        vc.push_back(i);
        //sc.insert(i);
    }

    for(int i = 0;i<nb;++i){
        tv.insert(i%3000,i);
        vc.insert(vc.begin() + i%3000,i);
        tv.pop((i*13)%1777);
        vc.erase(vc.begin() + (i*13)%1777);
        //vc.push_back(i);
        //sc.insert(i);
    }
    cout << " finish insert high: "<<tv.high()<<endl;

    for(int i = 0;i<nb;++i){
        int a = tv.addressing(i);
        int b = vc[i];
        if(a!=b){
            cout << "at idx:"<<i<<" "<<a<<"!="<<b<<endl;
            break;
        }
        //int d = sc.count(i);
    }
    
    cout << " finish reading"<<endl;
}

int main()
{
    test2();
    return 0;
}