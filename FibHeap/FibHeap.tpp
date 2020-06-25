
#include "FibHeap.h"

template<typename T>
FibNode<T>::FibNode() {
    _parent_p = nullptr;
    _child_p = nullptr;
    _left_p = this;
    _right_p = this;
    _size = 1;
    _subtree_deletions = false;
}

template<typename T>
FibNode<T>::FibNode(T data) {
    _parent_p = nullptr;
    _child_p = nullptr;
    _left_p = this;
    _right_p = this;
    _size = 1;
    _subtree_deletions = false;
    _data = data;
}

template<typename T>
unsigned int FibNode<T>::getSize() {
    return _size;
}

template<typename T>
T FibNode<T>::getData() {
    return _data;
}

template<typename T>
FibNode<T> *FibNode<T>::getChild() const {
    return _child_p;
}

template<typename T>
FibNode<T> *link(FibNode<T> *to, FibNode<T> *from) {
    FibNode<T> *to_left_link = to,
            *to_right_link = to->_right_p,
            *from_left_link = from,
            *from_right_link = from->_left_p;

    to_left_link->_right_p = from_left_link;
    from_left_link->_left_p = to_left_link;

    to_right_link->_left_p = from_right_link;
    from_right_link->_right_p = to_right_link;

    return to;
}

template<typename T>
FibNode<T>* iterate(FibNode<T> *operand) {
    if (operand) {
        return operand->_right_p;
    }
    return nullptr;
}

template<typename T>
bool FibNode<T>::resetParent() {
    if (_parent_p == nullptr){
        return false;
    }
    _parent_p = nullptr;
    return true;
}

template<typename T>
void FibNode<T>::listRemove() {
    FibNode<T> *L = _left_p, *R = _right_p;
    L->_right_p = R;
    R->_left_p = L;
    _left_p = _right_p = this;
}

template<typename T>
bool FibNode<T>::resetChild() {
    if (_child_p == nullptr){
        return false;
    }
    _child_p = nullptr;
    return true;}


template<typename T>
FibHeap<T>::FibHeap():_min_p(nullptr), _size(0), _max_root_size(0) {}

template<typename T>
FibHeap<T>::FibHeap(T data): _min_p(new FibNode<T>(data)), _size(1), _max_root_size(1) {}

template<typename T>
FibHeap<T>::FibHeap(FibNode<T> *single) : _min_p(single), _size(single->getSize()), _max_root_size(single->getSize()) {}

template<typename T>
FibHeap<T> merge(FibHeap<T> a, FibHeap<T> b) {
    if (a.getSize() == 0){
        return b;
    }
    if (b.getSize() == 0){
        return a;
    }

    FibHeap<T> res;
    res._size = a.getSize() + b.getSize();
    res._max_root_size = std::max(a._max_root_size, b._max_root_size);
    if (a.min() < b.min()) {
        res._min_p = link(a._min_p, b._min_p);
    } else {
        res._min_p = link(b._min_p, a._min_p);
    }

    return res;
}

template<typename T>
unsigned int FibHeap<T>::getSize() {
    return _size;
}

template<typename T>
T FibHeap<T>::min() {
    return _min_p->getData();
}

template<typename T>
void FibHeap<T>::insert(T data) {
    FibHeap inserted(data);
    *this = merge(inserted, (*this));
}

template<typename T>
FibNode<T> *FibHeap<T>::extractMin() {
    FibNode<T> *res = _min_p;
    if (res == nullptr) {
        return res;
    }
    FibNode<T> *it = res->getChild();
    if (it) {
        it->resetParent();
        res = link(res, it);
        it = iterate(it);
    }
    while (it != nullptr && it->resetParent()) {
        it = iterate(it);
    }
    res->resetChild();
    if (getSize() == 1){
        return res;
    }
    _min_p = iterate(_min_p);
    res->listRemove();
    _consolidate();//todo

    _size--;

    return res;
}

template<typename T>
void FibHeap<T>::_consolidate() {
    int degree = _max_root_size;
    _max_root_size = 0;

    FibNode<T>** A = new FibNode<T>*[degree + 1];
    for (int i = 0; i <= degree; i++)
        A[i] = nullptr;





    _min_p = nullptr;
    for (int i = 0; i <= degree; i++){
        if (A[i]){
            FibHeap inserted(A[i]);
            *this = merge(inserted, (*this));
            if (_min_p == nullptr || A[i]->getData() < _min_p->getData()){
                _min_p = A[i];
            }
            if (A[i]->getSize() > _max_root_size){
                _max_root_size = A[i]->getSize();
            }
        }

    }
}

