#include <vector>
using namespace std;
//my array for vector
template <typename T>
class MyArray{
    public:
        MyArray();
        MyArray(int,T);
        MyArray(vector<T>);
        T get(int);
        MyArray<T> get(int,int);
        void set(int,T);
    private:
        vector<T> data;
};

template <typename T>
MyArray<T>::MyArray(){}

template <typename T>
MyArray<T>::MyArray(int nb,T val){
    data.assign(nb,val);
}

template <typename T>
MyArray<T>::MyArray(vector<T> list){
    this->data = list;
}

template <typename T>
T MyArray<T>::get(int idx){
    return data[idx];
}

template <typename T>
MyArray<T> MyArray<T>::get(int start,int end){}

template <typename T>
void MyArray<T>::set(int idx,T val){
    data[idx] = val;
}