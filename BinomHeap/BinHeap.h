//
// Created by vbory on 6/22/2020.
//

#ifndef BINHEAP_H
#define BINHEAP_H

#include <vector>
#include <memory>
#include <algorithm>

template <typename T>
class Node{
public:
    Node();
    explicit Node(T data);

    [[nodiscard]] T getData() const;
    [[nodiscard]] std::shared_ptr<Node<T>> getParent() const;
    void setParent(const std::shared_ptr<Node<T>> &parent);
    [[nodiscard]] std::vector <std::shared_ptr<Node<T>>> getKids() const;
    [[nodiscard]] unsigned int getHeight() const;
    //this and that of equal height
    //merges that into this
    void merge(std::shared_ptr<Node<T>> &that);

private:
    T _data;
    unsigned int _height;
    std::vector <std::shared_ptr<Node <T>>> _kids;
    std::shared_ptr<Node <T>> _parent;
};

template<typename T>
Node<T>::Node(): _height(0) {}

template<typename T>
Node<T>::Node(T data):_data(data), _height(0) {}

template<typename T>
T Node<T>::getData() const {
    return _data;
}

template<typename T>
std::shared_ptr<Node<T>> Node<T>::getParent() const {
    return _parent;
}

template<typename T>
void Node<T>::setParent(const std::shared_ptr<Node<T>> &parent) {
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
    _kids.push_back(that);
    _height++;
    that->setParent(std::shared_ptr<Node<T>>(this));
}


template <typename T>
class BinHeap {
public:
    BinHeap();
    explicit BinHeap(const std::vector<std::shared_ptr<Node<T>>> &roots);
    [[nodiscard]] unsigned int getSize() const;
    [[nodiscard]] T min();
    std::shared_ptr <Node<T>> extractMin();
    void insert(T data);
    void merge(BinHeap<T> &that);
private:
    std::vector <std::shared_ptr<Node <T>>> _roots;
    unsigned int _size;
    [[nodiscard]] std::shared_ptr<Node<T>> _nodeMin();
};

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
std::shared_ptr<Node<T>> BinHeap<T>::_nodeMin() {
    if (_roots.size()){
        std::shared_ptr<Node<T>> min = _roots[0];
        for (auto it: _roots){
            if (it->getData() < min->getData()){
                min = it;
            }
        }
        return min;
    }
}

template<typename T>
unsigned int BinHeap<T>::getSize() const {
    return _size;
}

template<typename T>
T BinHeap<T>::min() {
    return _nodeMin()->getData();
}

template<typename T>
void BinHeap<T>::merge(BinHeap<T> &that){
    _size += that.getSize();

}

template<typename T>
void BinHeap<T>::insert(T data) {
    BinHeap <T> that = BinHeap<T>(std::vector{std::make_shared<Node<T>>(data)});
    merge(that);
}

template<typename T>
std::shared_ptr<Node<T>> BinHeap<T>::extractMin() {
    Node minimal = _nodeMin();
    _roots.erase(minimal);
    merge(BinHeap<T>(minimal._kids));
    return minimal;
}



#endif //BINHEAP_H
