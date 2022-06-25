#ifndef TREEVECTOR_INCLUDED
#include "IndexTree.hpp"
#include "Handler.hpp"

class SlicingException : public exception
{   public:
        int sidx = 0;
        int eidx = 0;
        SlicingException(int s,int e):sidx(s),eidx(e){}
        const char * what () const throw ()
        {
            return "start idx must <= end idx" ;
        }
};

template <typename T>
class TreeVector: public Handler<IndexTree<T>>{
    public:
        TreeVector(){};
        TreeVector(const TreeVector&);
        TreeVector(TreeVector &&);
        T pop(int);
        T addressing(int);
        void insert(int,const T&);
        TreeVector<T> slice(int begin_idx,int end_idx);
        inline int const size() const {return _size;};
        inline int const high() const {return this->data->high();};
        void debug_print();
    private:
        int begin_idx=0;
        int _size=0;
        virtual void copy_data(); 
        inline int idx(int id){return begin_idx + (id%_size + _size)%_size;};
        inline int idxs(int id){int tmpsz=_size+1;return begin_idx+(id%tmpsz + tmpsz)%tmpsz;};
};

template <typename T>
void TreeVector<T>::debug_print(){
    for(int i=0;i<_size;++i){
        cout << addressing(i) << " ";
    }
    cout << endl;
}


template <typename T>
TreeVector<T>::TreeVector(const TreeVector& other):
Handler<IndexTree<T>>(other),begin_idx(other.begin_idx),_size(other._size){}

template <typename T>
TreeVector<T>::TreeVector(TreeVector && other):
Handler<IndexTree<T>>(other),begin_idx(other.begin_idx),_size(other._size){}

template <typename T>
TreeVector<T> TreeVector<T>::slice(int start_idx,int end_idx){
    TreeVector<T> result(*this);
    int new_begin_idx = idx(start_idx);
    int new_end_idx = idxs(end_idx);
    result._size = new_end_idx - new_begin_idx;
    if(result.size() < 0)
        throw SlicingException(start_idx,end_idx);
    result.begin_idx = new_begin_idx;
    return move(result);
}

template <typename T>
T TreeVector<T>::pop(int id){
    this->writing();
    auto tmp = this->data->pop(idx(id));
    _size -= 1;
    return move(tmp);
}

template <typename T>
T TreeVector<T>::addressing(int id){
    return move(this->data->addressing(idx(id)));
}

template <typename T>
void TreeVector<T>::insert(int id ,const T& data){
    this->writing();
    this->data->insert(idxs(id),data);
    _size += 1;
}

template <typename T>
void TreeVector<T>::copy_data(){
    if(begin_idx == 0 && this->data->size() == _size){
        this->data = new IndexTree<T>(*(this->data));
    }
    else{
        this->data = new IndexTree<T>(this->data->slice(begin_idx, begin_idx + _size));
        begin_idx = 0;
        _size = this->data->size();
    }
}


#define TREEVECTOR_INCLUDED
#endif