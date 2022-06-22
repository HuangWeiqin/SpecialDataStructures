#ifndef HANDLER_INCLUDED
#include <iostream>
using namespace std;
template <typename T>
class Handler{
    public:
        Handler();
        Handler(const T& dt):data(new T(dt)),count(new int(1)){}
        Handler(const Handler<T>&);
        virtual Handler<T>& operator=(const Handler<T>&);
        virtual Handler<T>& share_from(const Handler<T>&);
        virtual ~Handler();
    protected:
        void inc();
        void dec();
        T *data = nullptr;
        int *count = nullptr;
    protected:
        virtual void writing();
        virtual void copy_data(){data = new T(*data);};
    
};

template <typename T>
Handler<T>::Handler():data(new T()),count(new int(1))
{}

template <typename T>
Handler<T>::Handler(const Handler<T>& other):count(other.count){
    data = other.data;
    inc();
}

template <typename T>
Handler<T>& Handler<T>::operator=(const Handler<T>& other){
    return share_from(other);
}

template <typename T>
Handler<T>& Handler<T>::share_from(const Handler<T>& other){
    if(this != &other){
        dec();
        count = other.count;
        data = other.data;
        inc();
    }
    return *this;
}

template <typename T>
Handler<T>::~Handler(){
    dec();
}

template <typename T>
void Handler<T>::inc(){
    ++*count;
}

template <typename T>
void Handler<T>::dec(){
    if(--*count == 0){
        delete data;
        delete count;
        data = nullptr;
        count = nullptr;
    }
}

template <typename T>
void Handler<T>::writing(){
    if(*count>1){
        copy_data();
        dec();
        count = new int(1);
    }
    
}

#define HANDLER_INCLUDED
#endif