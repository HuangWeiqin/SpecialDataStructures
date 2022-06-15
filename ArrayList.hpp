#ifndef ARRAYLIST_INCLUDED
#include <list>
#include <iostream>
#include "Handler.hpp"
#include "ListIdxIterManager.hpp"
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
        void insert(typename list<T>::iterator iter,T& val);
        typename list<T>::iterator begin();
        typename list<T>::iterator end();
        ArrayList<T> get(int from,int to);
        int size();
        void printf();
    protected:
        virtual void copy_data() override;
    private:
        ListIdxIter<T> begin_iterator;
        ListIdxIter<T> end_iterator;
        list<ListIdxIter<T>> iter_markers;

        void set_slice(int from,int to);
        bool is_slice();

        ListIdxIter<T>& find_nearest_iter(int);
        ListIdxIter<T>& move_iter_to(ListIdxIter<T>& iter, int dest_idx);
        ListIdxIter<T>& get_iter(int idx);
};

template <typename T>
ArrayList<T>::ArrayList():
    begin_iterator(0,this->data->begin()),
    end_iterator(0,this->data->end())
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
    begin_iterator(other.begin_iterator),
    end_iterator(other.end_iterator)
    {}

template <typename T>
void ArrayList<T>::copy_data(){
    this->data = new list<T>(begin_iterator.iterator, end_iterator.iterator);
    end_iterator.idx = this->data->size();
    begin_iterator.idx = 0;
    begin_iterator.iterator = this->data->begin();
    end_iterator.iterator = this->data->end();
}

template <typename T>
void ArrayList<T>::insert(typename list<T>::iterator iter,T& val){
    this->data->insert(iter,val);
    if(this->data->size()==1){
        begin_iterator = ListIdxIter<T>(0,this->data->begin());
        end_iterator = ListIdxIter<T>(0,this->data->end());
    }
}

template <typename T>
void ArrayList<T>::push_back(T &a){
    this->writing();
    insert(end_iterator.iterator,a);
    end_iterator.idx++;
}

template <typename T>
void ArrayList<T>::push_back(T a){
    this->writing();
    insert(end_iterator.iterator,a);
    end_iterator.idx++;
}

template <typename T>
void ArrayList<T>::push_front(T &a){
    this->writing();
    insert(begin_iterator.iterator,a);
    end_iterator.idx++;
    begin_iterator.idx--;
}

template <typename T>
void ArrayList<T>::push_front(T a){
    this->writing();
    insert(begin_iterator.iterator,a);
    end_iterator.idx++;
    begin_iterator.idx--;
}

template <typename T>
void ArrayList<T>::printf(){
    for(char i:*this->data){
        cout << i<<' ';
    }
    cout<<"count: "<< *this->count << endl;
    cout<<"begin: "<< begin_iterator.idx<<endl;
    cout<<"end: "<< end_iterator.idx<<endl;
}

template <typename T>
typename list<T>::iterator ArrayList<T>::begin(){
    return begin_iterator.iterator;
}

template <typename T>
typename list<T>::iterator ArrayList<T>::end(){
    return end_iterator.iterator;
}

template <typename T>
ArrayList<T> ArrayList<T>::get(int from,int to){
    ArrayList<T> res(*this);
    res.set_slice(from,to);
    return res;
}

template <typename T>
void ArrayList<T>::set_slice(int from,int to){
    end_iterator = get_iter(to);
    begin_iterator = get_iter(from);
    iter_markers.clear();
    iter_markers.emplace_back(begin_iterator);
    iter_markers.emplace_back(end_iterator);
}

template <typename T>
bool ArrayList<T>::is_slice(){
    return begin_iterator.idx>0 || end_iterator.idx<size();
}

template <typename T>
int ArrayList<T>::size(){
    return end_iterator.idx - begin_iterator.idx;
}

template <typename T>
ListIdxIter<T>& ArrayList<T>::find_nearest_iter(int idx){
    if(iter_markers.size() == 0){
        return begin_iterator;
    }

    ListIdxIter<T>* best = nullptr;
    int diff = 65535;
    for(ListIdxIter<T>& iter: iter_markers){
        int tmp_diff = abs(iter.idx - idx);
        if(tmp_diff < diff){
            best = &iter;
            diff = tmp_diff;
        }
    }
    
    return *best;
}

template <typename T>
ListIdxIter<T>& ArrayList<T>::move_iter_to(ListIdxIter<T>& iter,int idx){
    if(iter.idx == idx){
        return iter;
    }
    else if(iter.idx < idx){
        iter += idx - iter.idx;
    }
    else{
        iter -= iter.idx - idx;
    }
    return iter;
}

template <typename T>
ListIdxIter<T>& ArrayList<T>::get_iter(int idx){
    ListIdxIter<T>& nearby_iter = find_nearest_iter(idx);
    return move_iter_to(nearby_iter,idx);
}

#define ARRAYLIST_INCLUDED
#endif