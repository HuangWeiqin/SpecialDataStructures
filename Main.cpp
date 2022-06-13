#include <iostream>
#include "MyArray.hpp"
#include "RegMachine.hpp"
using namespace std;
int main()
{
    int k[8] = {3,3,3,2,2,2,2,4};
    MyArray<int> text(8,k);
    RegMachine machine;
    machine.add_transition(0,3,0);
    machine.add_transition(0,2,2);
    machine.add_transition(2,2,3);
    machine.add_transition(3,2,3);
    machine.add_transition(3,2,4);
    //machine.add_transition(4,4,4);
    machine.add_transition(4,4,-1);

    MyArray<int> token;
    MyArray<int> rest;
    cout << machine.read(&text,&token,&rest) << endl;

    token.debug_print();
    rest.debug_print();

    return 0;
}