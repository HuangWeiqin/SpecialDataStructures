#ifndef REGMACHINE_INCLUDED
#include "AutoMachineNode.hpp"
#include "MyArray.hpp"

class RegMachine: public AutoMachineNode{
    public:
        bool read(MyArray<int>* , MyArray<int>* , MyArray<int>* );

};

bool RegMachine::read(MyArray<int> *text, MyArray<int> *token, MyArray<int> *rest){
    if(state == -1){
        rest->extend(text);
        return true;
    }
    if(text->size() == 0){
        
        return false;
    }

    int i;
    for(i = 0; i < text->size(); ++i){
        int key = text->get(i);
        MyArray<int> choices = trigger_transition(key);
        int size = choices.size();
        if(size == 0){
            if(state != -1){
                return false;
            }
            MyArray<int> tmp_token = text->get(0,i);
            MyArray<int> tmp_rest = text->get(i,-1);
            token->extend(&tmp_token);
            rest->extend(&tmp_rest);
            return true;
        }
        else if(size == 1){
            state = choices.get(0);
        }
        else{
            MyArray<int> tmp_token = text->get(0,i+1);
            MyArray<int> tmp_rest = text->get(i+1,-1);
            token->extend(&tmp_token);
            for(int s:*choices.get_data()){
                state = s;
                if(read(&tmp_rest, token,rest) == true){
                    return true;
                }
            }
            token->clear();
            return false;
        }
    }

    token->extend(text);
    return true;
}


#define REGMACHINE_INCLUDED
#endif