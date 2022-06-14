#ifndef HANDLER_INCLUDED
template <typename T>
class Handler{
    public:
        Handler();
        Handler(const Handler<T>&);
        virtual Handler& operator=(const Handler<T>&);
        virtual ~Handler();
    protected:
        int *count = nullptr;
        T *data = nullptr;
        void writing();
        virtual void copy_data() = 0;
    private:
        void inc();
        void dec();
};

template <typename T>
Handler<T>::Handler():data(new T()),count(new int(1)){}

template <typename T>
Handler<T>::Handler(const Handler& other):count(other.count){
    data = other.data;
    inc();
}

template <typename T>
Handler<T>& Handler<T>::operator=(const Handler<T>& other){
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