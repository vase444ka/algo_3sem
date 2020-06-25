
#include "FibHeap.h"

template<typename T>
FibNode<T>::FibNode() {
    _parent_p = nullptr;
    _child_p = nullptr;
    _left_p = _right_p = this;
    _size = 1;
    _subtree_deletions = false;
    _is_deleted = false;
}

template<typename T>
FibNode<T>::FibNode(T data) {
    FibNode();
    _data = data;
}

template<typename T>
FibNode<T>::~FibNode() {
    if (_child_p)
        delete _child_p;
    _is_deleted = true;
    if (!(_right_p->_is_deleted))
        delete _right_p;
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
FibNode<T> *operator++(FibNode<T> *operand) {
    if (operand) {
        operand = operand->_right_p;
        return operand;
    }
    return nullptr;
}

template<typename T>
void FibNode<T>::resetParent() {
    _parent_p = nullptr;
}

template<typename T>
void FibNode<T>::listRemove() {
    FibNode<T> *L = _left_p, *R = _right_p;
    L->_right_p = R;
    R->_left_p = L;
    _left_p = _right_p = this;
    _child_p = nullptr;
}


template<typename T>
FibHeap<T>::FibHeap():_min_p(nullptr), _size(0) {}

template<typename T>
FibHeap<T>::FibHeap(T data): _min_p(data), _size(1) {}

template<typename T>
FibHeap<T>::FibHeap(FibNode<T> *single) : _min_p(single), _size(single->getSize()) {}

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
void FibHeap<T>::_clear() {
    _min_p = nullptr;
    _size = 0;
}

template<typename T>
FibNode<T> *FibHeap<T>::extractMin() {
    FibNode<T> *res = _min_p;
    if (res == nullptr) {
        return res;
    }
    FibNode<T> *iterator = res->getChild();
    if (iterator) {
        iterator->resetParent();
        res = link(res, FibNode<T>(iterator));
        iterator++;
    }
    while (iterator != res->getChild()) {
        iterator->resetParent();
        res = link(res, FibNode<T>(iterator));
        iterator++;
    }
    if (getSize() == 1){
        _clear();
        return res;
    }
    _min_p++;
    res->listRemove();//todo
    _consolidate();

    _size--;

    return res;
}

template<typename T>
unsigned int FibHeap<T>::getSize() {
    return _size;
}

template<typename T>
FibHeap<T>::~FibHeap() {
    delete _min_p;
}

template<typename T>
FibHeap<T> merge(const FibHeap<T> &a, const FibHeap<T> &b) {
    FibHeap<T> res;
    if (a.getSize() == 0){
        res = b;
        b._clear();
        return res;
    }
    if (b.getSize() == 0){
        res = a;
        a._clear();
        return res;
    }

    res._size = a.getSize() + b.getSize();
    if (a.min() < b.min()) {
        res._min_p = link(a._min_p, b._min_p);
    } else {
        res._min_p = link(b._min_p, a._min_p);
    }

    a._clear();
    b._clear();
    return res;
}

template<typename T>
void FibHeap<T>::_consolidate() {

}

