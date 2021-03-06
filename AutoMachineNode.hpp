#ifndef AUTOMACHINENODE_INCLUDED
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include "MyArray.hpp"
using namespace std;

class AutoMachineNode
{
   public:
        AutoMachineNode();
        int state = 0;
        unordered_map< int, unordered_map<int, MyArray<int> > > all_stats; 
        unordered_set<int> all_triggers;
        bool add_transition(int,int,int);
        MyArray<int> trigger_transition(int);

};


AutoMachineNode::AutoMachineNode(){
    add_transition(0,-1,-1);
    add_transition(-1,0,0);
}

bool AutoMachineNode::add_transition(int from,int trigger,int to){
    if(all_stats.count(from) == 0){
        all_stats.emplace(from, unordered_map<int,MyArray<int> >());
    }

    if(all_stats[from].count(trigger) == 0){
        all_stats[from].emplace(trigger,MyArray<int>());
    }
    all_stats[from][trigger].append(to);
    all_triggers.insert(trigger);
    return true;
}

MyArray<int> AutoMachineNode::trigger_transition(int t){
    if(all_stats[state].count(t) == 0){
        return MyArray<int>();
    }
    return all_stats[state][t];
}

#define AUTOMACHINENODE_INCLUDED
#endif