#include <iostream>
#include "ArrayList.hpp"
#include "ListIdxIterManager.hpp"

using namespace std;

void test1(){
    ArrayList<char> list(6,"fucker");
    //list =list.get(0,7);
    list.printf();

    for(char c:list){
        cout<< c;
    }
    cout<<endl;
    if(1)
    cout<<INT_MAX;
}


void test2(){
    list<char> ls;
    ls.emplace_back('s');
    ls.emplace_back('d');
    ls.emplace_back('c');
    ls.emplace_back('w');
    ListIdxIterManager<char> tmp(ls);
    for(char &c : tmp){
        cout<< c;
    }
    cout<<endl;

    cout<< *(tmp.get_iter(2)).iterator <<endl;

    for(ListIdxIter<char> &c : tmp.iters){
        cout<< c.idx;
    }
    cout<<endl;

}

int main()
{
    test2();
    return 0;
}