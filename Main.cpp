#include <iostream>
#include "ArrayList.hpp"
using namespace std;
int main()
{
    ArrayList<char> list(6,"fucker");
    ArrayList<char> tmp = list.get(1,4);
    for(char c:tmp){
        cout<<c;
    }
    tmp.printf();
    return 0;
}