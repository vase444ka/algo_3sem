//
// Created by vbory on 6/22/2020.
//

#ifndef BINHEAP_H
#define BINHEAP_H

#include <vector>
#include <memory>
#include <algorithm>
#include <list>

template <typename T>
class Node{
public:
    Node();
    explicit Node(T data);

    [[nodiscard]] T getData() const;
    [[nodiscard]] std::shared_ptr<Node<T>> getParent() const;
    void setParent(Node<T>* parent);
    [[nodiscard]] std::vector <std::shared_ptr<Node<T>>> getKids() const;
    [[nodiscard]] unsigned int getHeight() const;
    //this and that of equal height
    //merges that into this
    void merge(std::shared_ptr<Node<T>> &that);

private:
    T _data;
    unsigned int _height;
    std::vector <std::shared_ptr<Node <T>>> _kids;
    Node <T>* _parent;
};

template <typename T>
class BinHeap {
public:
    BinHeap();
    explicit BinHeap(const std::vector<std::shared_ptr<Node<T>>> &roots);
    [[nodiscard]] unsigned int getSize() const;
    [[nodiscard]] T min();
    T extractMin();
    void insert(T data);
    void merge(BinHeap<T> &that);

private:
    std::vector <std::shared_ptr<Node <T>>> _roots;//from large to small
    unsigned int _size;
    [[nodiscard]] auto _iteratorMin();
};

#include "BinHeap.tpp"

#endif //BINHEAP_H
