#ifndef ListIdxIterManager_INCLUDED
#include <list>
#include <iostream>
#include <climits>
#include "Handler.hpp"
using namespace std;

template <typename T>
class ListIdxIter{
    public:
        ListIdxIter(){};
        ListIdxIter(int i, typename list<T>::iterator iter):idx(i),iterator(iter){};
        ListIdxIter(const ListIdxIter& iter):idx(iter.idx),iterator(iter.iterator){};
        int idx;
        typename list<T>::iterator iterator;

        ListIdxIter<T>& operator+=(int diff){
            for(int i=0;i<diff;++i){
                iterator++;
            }
            idx += diff;
        }

        ListIdxIter<T>& operator-=(int diff){
            for(int i=0;i<diff;++i){
                iterator--;
            }
            idx -= diff;
        }

};

template <typename T>
class ListIdxIterManager{
    public:
        ListIdxIterManager(list<T>& ls){init(ls);};
        void init(list<T>& ls);
        ListIdxIter<T> get_iter(int idx);
        void begin_advance(int);
        void end_backward(int);
        typename list<T>::iterator begin();
        typename list<T>::iterator end();
        list<ListIdxIter<T>> iters;
    private:
        ListIdxIter<T>& begin_iterator();
        ListIdxIter<T>& end_iterator();
        ListIdxIter<T>& move_iter_to(ListIdxIter<T>& iter, int dest_idx);
        ListIdxIter<T> copy_iter_to(ListIdxIter<T> iter, int dest_idx);

        int size();
};

template <typename T>
void ListIdxIterManager<T>::init(list<T>& ls){
    iters.clear();
    iters.emplace_back(ListIdxIter<T>(0,ls.begin()));
    iters.emplace_back(ListIdxIter<T>(ls.size(),ls.end()));
}

template <typename T>
void ListIdxIterManager<T>::begin_advance(int diff){
    if(size() == 0){
        return;
    }
    for(int i=0;i<diff;++i){

        if(begin_iterator().idx == end_iterator().idx){
            return;
        }

        for(ListIdxIter<T>& iter:iters){
            if(iter.idx>0){
                iter.idx-=1;
                break;
            }
        }
        begin_iterator().iterator++;
    }
    
}

template <typename T>
void ListIdxIterManager<T>::end_backward(int diff){
    if(size() == 0){
        return;
    }
}


template <typename T>
typename list<T>::iterator ListIdxIterManager<T>::begin(){
    return begin_iterator().iterator;
}

template <typename T>
typename list<T>::iterator ListIdxIterManager<T>::end(){
    return end_iterator().iterator;
}

template <typename T>
ListIdxIter<T>& ListIdxIterManager<T>::begin_iterator(){
    return *iters.begin();
}

template <typename T>
ListIdxIter<T>& ListIdxIterManager<T>::end_iterator(){
    return *(--iters.end());
}

template <typename T>
int ListIdxIterManager<T>::size(){
    int res = 0;
    for(ListIdxIter<T>& iter : iters){
        res += iter.idx;
    }
    return res;
}

template <typename T>
ListIdxIter<T>& ListIdxIterManager<T>::move_iter_to(ListIdxIter<T>& iter,int diff){
    if(diff == 0){
        return iter;
    }
    iter +=  diff;
    return iter;
}

template <typename T>
ListIdxIter<T> ListIdxIterManager<T>::copy_iter_to(ListIdxIter<T> iter,int diff){
    if(diff == 0){
        return iter;
    }
    iter +=  diff;
    return iter;
}

template <typename T>
ListIdxIter<T> ListIdxIterManager<T>::get_iter(int idx){
    if(idx <= 0){
        return *iters.begin();
    }
    else if(idx >= size()){
        return *iters.end();
    }
    
    ListIdxIter<T>* right_iter = nullptr;
    ListIdxIter<T>* left_iter = nullptr;
    int right_idx = 0;
    int left_idx = 0;
    typename list<ListIdxIter<T>>::iterator pos = iters.begin();
    for(ListIdxIter<T>& iter: iters){
        right_idx += iter.idx;
        if(right_idx >= idx){
            right_iter = &iter;
            break;
        }
        left_iter = &iter;
        left_idx = right_idx;
        ++pos;
    }


    ListIdxIter<T>* near_iter = nullptr;
    int diff = 0;

    int mid = right_idx -  (right_iter->idx)/2;
    if(idx > mid){
        near_iter = right_iter;
        diff = idx - right_idx;
    }
    else{
        near_iter = left_iter;
        diff = idx - left_idx;
    }
    ListIdxIter<T> res = move_iter_to(*near_iter,diff);
    iters.insert(pos,res);
    return res;
}




#define ListIdxIterManager_INCLUDED
#endif