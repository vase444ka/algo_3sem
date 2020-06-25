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
    bool resetParent();//true if parent was chaged
    bool resetChild();//true if child was chaged
    void listRemove();//should have at least 1 sibiling
    ~FibNode() = default;

    template<typename t>
    friend FibNode<t>* iterate(FibNode<t>*a);

    void tmpAll(){
        std::cout<<_data<<' '<<_parent_p<<' '<<_child_p<<' '<<_left_p<<' '<<_right_p<<std::endl;
    }
    //returns modified to
    template <typename t>
    friend FibNode <t>* link(FibNode <t>* to, FibNode <t>* from);

private:
    T _data;
    FibNode *_parent_p, *_child_p, *_left_p, *_right_p;
    unsigned int _size;
    bool _subtree_deletions;
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
    ~FibHeap() = default;

    FibNode<T> *tmpMin(){return _min_p;}

    template<typename t>
    friend FibHeap<t> merge(FibHeap<t> a, FibHeap<t> b);

private:
    FibNode <T> *_min_p;
    unsigned int _size, _max_root_size;
    void _consolidate();
};

#include "FibHeap.tpp"

#endif //FIBHEAP_FIBHEAP_H
