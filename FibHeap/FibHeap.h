//
// Created by vbory on 6/25/2020.
//

#ifndef FIBHEAP_FIBHEAP_H
#define FIBHEAP_FIBHEAP_H

template <typename T>
class FibNode;
template <typename T>
class FibHeap;

template <typename T>
class FibNode{
public:
    FibNode();
    explicit FibNode(T data);
    [[nodiscard]] T getData();
    [[nodiscard]] unsigned int getSize();
    [[nodiscard]] FibNode<T>* getChild() const;
    void resetParent();
    ~FibNode();

    friend  FibNode<T>* operator++(FibNode<T>*);

    //returns modified to
    friend FibNode <T>* merge(FibNode <T>* to, FibNode <T>* from);

private:
    T _data;
    FibNode *_parent_p, *_child_p, *_left_p, *_right_p;
    unsigned int _size;
    bool _subtree_deletions, _is_deleted;
};

template <typename T>
class FibHeap{
public:
    FibHeap();
    explicit FibHeap(T data);
    explicit FibHeap(FibNode<T>* single_node);
    [[nodiscard]] unsigned int getSize();
    void insert(T data);
    T min();
    FibNode<T> *extractMin();
    ~FibHeap();

    friend FibHeap<T> merge(FibHeap<T> a, FibHeap<T> b);

private:
    FibNode <T> *_min_p;
    unsigned int _size;
    void _clear();
};

#include "FibHeap.tpp"

#endif //FIBHEAP_FIBHEAP_H
