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
        ArrayList(const ArrayList<T>&);
        void push_back(T&);
        void push_back(T);
        void push_front(T&);
        void push_front(T);
        typename list<T>::iterator begin();
        typename list<T>::iterator end();
        ArrayList<T> get(int from,int to);
        int size();
        void printf();
        typename list<T>::iterator begin_iterator;
        typename list<T>::iterator end_iterator;
    protected:
        virtual void copy_data() override;
    private:
        int begin_idx = -1;
        int end_idx = -1;
        
        void set_slice(int from,int to);
        bool is_slice();

};

template <typename T>
ArrayList<T>::ArrayList():
    begin_idx(0),
    end_idx(0),
    begin_iterator(this->data->begin()),
    end_iterator(this->data->end())
    {}

template <typename T>
ArrayList<T>::ArrayList(int nb,const T* array):ArrayList(){
    for(int i=0; i<nb; ++i){
        push_back(array[i]);
    }
}

template <typename T>
ArrayList<T>::ArrayList(const ArrayList<T>& other):
    Handler<list<T>>(other),
    begin_idx(other.begin_idx),
    end_idx(other.end_idx),
    begin_iterator(other.begin_iterator),
    end_iterator(other.end_iterator)
    {}

template <typename T>
void ArrayList<T>::copy_data(){
    this->data = new list<T>(begin_iterator, end_iterator);
    end_idx = this->data->size();
    begin_idx = 0;
    begin_iterator = this->data->begin();
    end_iterator = this->data->end();
    cout<<"copy data"<<endl;
}

template <typename T>
void ArrayList<T>::push_back(T &a){
    this->writing();
    this->data->insert(end_iterator,a);
    end_idx++;
}

template <typename T>
void ArrayList<T>::push_back(T a){
    this->writing();
    this->data->insert(end_iterator,a);
    end_idx++;
}

template <typename T>
void ArrayList<T>::push_front(T &a){
    this->writing();
    this->data->insert(begin_iterator,a);
    end_idx++;
    begin_iterator--;
}

template <typename T>
void ArrayList<T>::push_front(T a){
    this->writing();
    this->data->insert(begin_iterator,a);
    end_idx++;
    begin_iterator--;
}

template <typename T>
void ArrayList<T>::printf(){
    for(char i:*this->data){
        cout << i<<' ';
    }
    cout<<"count: "<< *this->count << endl;
}

template <typename T>
typename list<T>::iterator ArrayList<T>::begin(){
    return begin_iterator;
}

template <typename T>
typename list<T>::iterator ArrayList<T>::end(){
    return end_iterator;
}

template <typename T>
ArrayList<T> ArrayList<T>::get(int from,int to){
    ArrayList<T> res(*this);
    res.set_slice(from,to);
    return res;
}

template <typename T>
void ArrayList<T>::set_slice(int from,int to){

}

template <typename T>
bool ArrayList<T>::is_slice(){
    return begin_idx>0 || end_idx<size();
}

template <typename T>
int ArrayList<T>::size(){
    return this->data->size();
}

#define ARRAYLIST_INCLUDED
#endif