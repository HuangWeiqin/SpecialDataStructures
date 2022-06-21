#include <iostream>
#include "ListNode.hpp"
#include "IDX_AvlTree.hpp"
#include <vector>

using namespace std;


void test(){
    ListNode<ListNode<char>> ls;
    ListNode<char> tmp(3,"xst");
    ls.push_back(tmp);
    ls.value().debug_print();
}

template <typename T>
int IDXAvlTreeNode<T>::cnt = 0;

void help(IDXAvlTreeNode<int>* tmp,int it){
    for(int i=it-10;i<=it+15;i+=1){
        auto res = tmp->addressing(i);
        if(res)
            cout<<res->value()<<' ';
        else
            cout << "? ";
    }
    cout << endl;
}

void help2(IDXAvlTreeNode<int>* tmp,int it){
    auto res = tmp;
    for(int i=0;i<=it;i+=1){
        if(res){
            cout<<res->value()<<' ';
            res = res->_next;
        }
        else
            break;
    }
    cout <<"fishi"<< endl;
}


bool compare_with_vec(vector<int> &vec,IDXAvlTreeNode<int>* tmp){
    vector<int>::iterator iter = vec.begin();
    while (tmp != nullptr)
    {
        
        if(*iter != tmp->value()){
            cout << *iter<<" != "<<tmp->value()<<endl;
            cout<<" !!!!!!!!!!!!"<<endl;
            return false;
        }
            
        ++iter;
        tmp = tmp->_next;
        //cout << endl;
    }
    return true;
}

void test2(){
    
    IDXAvlTreeNode<int>* tmp = new IDXAvlTreeNode<int>(0,0);
    vector<int> vec;
    vec.push_back(0);
    for(int i=1;i<200000;i+=1){
        tmp = tmp->insert(i,i);
        vec.push_back(i);
    }

    for(int i=0;i<100000;i+=1){
        tmp = tmp->insert(1 + i%130000,i%10);
        auto res = tmp->pop( 1+(3*i)%130000,tmp);
        delete res;
        auto res2 = tmp->addressing(1+ (7*i)%130000);
        if(res2 != nullptr)
            cout <<"fucker"<<res2->value()<<endl;

        //vec.insert(vec.begin() + 1 + i%130000,i%10);
        //vec.erase(vec.begin() +1+ (3*i)%130000);
        //vec[1+ (7*i)%130000];
    }

    cout<< IDXAvlTreeNode<int>::cnt<<endl;
    cout<< tmp->_high <<endl;
     
}

int main()
{
    test2();
    return 0;
}