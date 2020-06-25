#include <iostream>
#include "BinHeap.h"

void f(){
    BinHeap<int> test_heap;
    test_heap.insert(1);
    std::cout << test_heap.min() << std::endl;

    test_heap.insert(0);
    std::cout << test_heap.min() << std::endl;

    test_heap.insert(3);
    std::cout << test_heap.min() << std::endl;

    test_heap.insert(2);
    std::cout << test_heap.min() << std::endl;

    test_heap.insert(5);
    std::cout << test_heap.min() << std::endl;

    test_heap.extractMin();
    std::cout << test_heap.min() << std::endl;

    test_heap.extractMin();
    std::cout << test_heap.min() << std::endl;

    test_heap.insert(0);
    std::cout << test_heap.min() << std::endl;
}

int main() {
    f();
    return 0;
}
