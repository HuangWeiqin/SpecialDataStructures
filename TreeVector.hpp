#ifndef TREEVECTOR_INCLUDED
#include "IndexTree.hpp"
#include "Handler.hpp"

template <typename T>
class TreeVector: public Handler<IndexTree<T>>{
    public:
        T addressing(int);
        void insert(int,const T&);
};

template <typename T>
T TreeVector<T>::addressing(int idx){
    return move(this->data->addressing(idx));
}

template <typename T>
void TreeVector<T>::insert(int idx ,const T& data){
    this->writing();
    this->data->insert(idx,data);
}


#define TREEVECTOR_INCLUDED
#endif