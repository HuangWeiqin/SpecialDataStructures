#ifndef MYARRAY_INCLUDED
#include <vector>
#include <iostream>
using namespace std;
//my array for vector
template <typename T>
class MyArray{
    public:
        MyArray();
        MyArray(int,T);
        MyArray(vector<T>);
        MyArray(int,const T*);
        T get(int);
        MyArray<T> get(int,int);
        void set(int,T);
        int size();
        void append(T val);
        void extend(MyArray<T>*);
        void clear();
        vector<T> *get_data();
        void debug_print();
    private:
        vector<T> data;
        int correct_idx(int idx);
        int correct_slice_idx(int idx);
};

template <typename T>
MyArray<T>::MyArray(){}

template <typename T>
MyArray<T>::MyArray(int nb,const T *array){
    for(int i = 0; i < nb ; ++i){
        this->data.emplace_back(array[i]);
    }
}

template <typename T>
MyArray<T>::MyArray(int nb,T val){
    this->data.assign(nb,val);
}

template <typename T>
MyArray<T>::MyArray(vector<T> list){
    this->data = list;
}

template <typename T>
int MyArray<T>::correct_idx(int idx){
    if(idx < 0){
        return (this->data.size() + idx)%this->data.size();
    }
    if(idx >= this->data.size()){
        return this->data.size() - 1;
    }
    return idx;
}

template <typename T>
int MyArray<T>::correct_slice_idx(int idx){
    if(idx < 0){
        return (this->data.size() + idx)%this->data.size() + 1;
    }
    if(idx >= this->data.size()){
        return this->data.size();
    }
    return idx;
}

template <typename T>
T MyArray<T>::get(int idx){
    int i = correct_idx(idx);
    return this->data[i];
}

template <typename T>
MyArray<T> MyArray<T>::get(int _start,int _end){
    int start = correct_slice_idx(_start);
    int end = correct_slice_idx(_end);

    MyArray<T> res;
    for(int i = start; i < end; ++i){
        res.append(this->data[i]);
    }
    return res;
}

template <typename T>
void MyArray<T>::set(int idx,T val){
    data[idx] = val;
}

template <typename T>
void MyArray<T>::append(T val){
    data.emplace_back(val);
}

template <typename T>
void MyArray<T>::extend(MyArray<T> *other){
    data.insert(data.end(),other->data.begin(),other->data.end());
}



template <typename T>
int MyArray<T>::size(){
    return this->data.size();
}

template <typename T>
void MyArray<T>::clear(){
    return this->data.clear();
}

template <typename T>
vector<T> * MyArray<T>::get_data(){
    return &data;
}

template <typename T>
void MyArray<T>::debug_print(){
    for (int i:data)
    {
       cout<< i<<' ';
    }
    cout << endl;
}



#define MYARRAY_INCLUDED
#endif