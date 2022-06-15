#include <iostream>
#include "ArrayList.hpp"
using namespace std;
int main()
{
    ArrayList<char> list(6,"fucker");
    //list =list.get(0,7);
    list.printf();

    for(char c:list){
        cout<< c;
    }
    cout<<endl;
    return 0;
}