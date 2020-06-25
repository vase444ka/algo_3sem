template<typename T>
FibNode<T>::FibNode() {
    _parent_p = nullptr;
    _child_p = nullptr;
    _left_p = _right_p = this;
    _size = 0;
    _subtree_deletions = false;
}

template<typename T>
FibNode<T>::FibNode(T data) {
    FibNode();
    _data = data;
}

template<typename T>//todo recursive
FibNode<T>::~FibNode() {
    if(_left_p)
        delete _left_p;
    if (_right_p)
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

template <typename T>//todo
FibNode<T>* merge(FibNode<T>* to, FibNode<T>* from) {
    to->_right_p->_left_p = ;
    to->_right_p = from;

    from->_left_p->_right_p = to->_right_p;
    from->_left_p = to;
}


template<typename T>
FibHeap<T>::FibHeap():_min_p(nullptr), _size(0) {}

template<typename T>
FibHeap<T>::FibHeap(T data): _min_p(data), _size(0) {}

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

template<typename T>//todo
FibNode<T> *FibHeap<T>::extractMin() {

}

template<typename T>
unsigned int FibHeap<T>::getSize() {
    return _size;
}

template<typename T>
FibHeap<T>::~FibHeap() {
    delete _min_p;
}

template <typename T>
FibHeap<T> merge(FibHeap<T> a, FibHeap<T> b) {
    FibHeap <T> res;

    res._size = a.getSize() + b.getSize();
    if (a.min() < b.min()){
        res._min_p = merge(a._min_p, b._min_p);
    }
    else{
        res._min_p = merge(b._min_p, a._min_p);
    }

    a._clear();
    b._clear();
    return res;
}

