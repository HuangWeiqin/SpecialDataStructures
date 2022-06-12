#include <iostream>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class AutoMachineNode
{
   public:
        int state = 0;
        AutoMachineNode* father = nullptr;
        unordered_map<int, AutoMachineNode*> brothers; // trigger : next node
        unordered_map<int, AutoMachineNode*> childrend; // trigger : next node
        bool machine_add_transition(int,int,int); // node, trigger, next node
        bool machine_trigger(int);
    private:
        bool node_add_transition(int,int); // trigger, next node
        bool machine_trigger(int);
};