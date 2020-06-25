//
// Created by vbory on 6/22/2020.
//



template<typename T>
Node<T>::Node(): _height(0), _parent(nullptr) {}

template<typename T>
Node<T>::Node(T data):_data(data), _height(0), _parent(nullptr) {}

template<typename T>
T Node<T>::getData() const {
    return _data;
}

template<typename T>
std::shared_ptr<Node<T>> Node<T>::getParent() const {
    return _parent;
}

template<typename T>
void Node<T>::setParent(Node<T>* parent) {
    _parent = parent;
}

template<typename T>
std::vector<std::shared_ptr<Node<T>>> Node<T>::getKids() const {
    return _kids;
}

template<typename T>
unsigned int Node<T>::getHeight() const {
    return _height;
}

template <typename T>
void Node<T>::merge(std::shared_ptr<Node<T>> &that) {
    _kids.insert(_kids.begin(), that);
    _height++;
    that->setParent(this);
}



template<typename T>
BinHeap<T>::BinHeap(): _size(0) {}

template<typename T>
BinHeap<T>::BinHeap(const std::vector<std::shared_ptr<Node<T>>> &roots):_roots(roots) {
    _size = 0;
    for (auto &it: _roots){
        _size += (1<<it->getHeight());
    }
}

template<typename T>
auto BinHeap<T>::_iteratorMin(){
    auto min = _roots.begin();
    auto it = _roots.begin();
    while(it != _roots.end()){
        if ((*it)->getData() < (*min)->getData()){
            min = it;
        }
        it++;
    }
    return min;
}

template<typename T>
unsigned int BinHeap<T>::getSize() const {
    return _size;
}

template<typename T>
T BinHeap<T>::min() {
    return (*_iteratorMin())->getData();
}

template<typename T>
void BinHeap<T>::merge(BinHeap<T> &that){
    _size += that.getSize();
    std::list<std::shared_ptr<Node<T>>> tmp_container;
    int first_item = _roots.size() - 1, second_item = that._roots.size() - 1;
    while(first_item >= 0 && second_item >= 0){
        if (_roots[first_item]->getHeight() < that._roots[second_item]->getHeight()){
            tmp_container.push_back(_roots[first_item]);
            first_item--;
        }
        else{
            tmp_container.push_back(that._roots[second_item]);
            second_item--;
        }
    }
    while(first_item >= 0){
        tmp_container.push_back(_roots[first_item]);
        first_item--;
    }
    while(second_item >= 0){
        tmp_container.push_back(that._roots[second_item]);
        second_item--;
    }

    for (auto it = tmp_container.begin(), it_next = ++tmp_container.begin(); it_next != tmp_container.end(); ) {
        if ((*it)->getHeight() == (*it_next)->getHeight()) {
            if ((*it_next)->getData() > (*it)->getData()){
                std::swap(*it_next, *it);
            }
            (*it_next)->merge(*it);
            it = tmp_container.erase(it);
        } else {
            ++it;
        }
        ++it_next;
    }
    _roots.clear();
    for (auto it: tmp_container){
        _roots.push_back(it);
    }
    std::reverse(_roots.begin(), _roots.end());
}

template<typename T>
void BinHeap<T>::insert(T data) {
    BinHeap <T> that = BinHeap<T>(std::vector{std::make_shared<Node<T>>(data)});
    merge(that);
}

template<typename T>
T BinHeap<T>::extractMin() {
    auto minimal = _iteratorMin();
    BinHeap<T> that = BinHeap<T>((*minimal)->getKids());
    _roots.erase(minimal);
    merge(that);
    return (*minimal)->getData();
}

#include "BinHeap.h"
