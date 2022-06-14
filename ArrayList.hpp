#ifndef ARRAYLIST_INCLUDED
#include <list>
#include <iostream>
#include "Handler.hpp"
using namespace std;

template <typename T>
class ArrayList: public Handler<list<T>>{
    public:
        ArrayList();
        ArrayList(int,const T*);
        void push_back(T&);
        void push_back(T);
        void push_front(T&);
        void push_front(T);
        void printf();
    protected:
        virtual void copy_data() override;
};

template <typename T>
ArrayList<T>::ArrayList(){}

template <typename T>
ArrayList<T>::ArrayList(int nb,const T* array){
    for(int i=0; i<nb; ++i){
        push_back(array[i]);
    }
}

template <typename T>
void ArrayList<T>::copy_data(){
    this->data = new list<T>(*this->data);
}

template <typename T>
void ArrayList<T>::push_back(T &a){
    this->writing();
    this->data->emplace_back(a);
}

template <typename T>
void ArrayList<T>::push_back(T a){
    this->writing();
    this->data->emplace_back(a);
}

template <typename T>
void ArrayList<T>::push_front(T &a){
    this->writing();
    this->data->emplace_front(a);
}

template <typename T>
void ArrayList<T>::push_front(T a){
    this->writing();
    this->data->emplace_front(a);
}

template <typename T>
void ArrayList<T>::printf(){
    for(char i:*this->data){
        cout << i<<' ';
    }
    cout<<"count: "<< *this->count << endl;
}

#define ARRAYLIST_INCLUDED
#endif