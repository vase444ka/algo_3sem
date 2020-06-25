#include <iostream>
#include "BinHeap.h"

void f(){
    BinHeap<int> test_heap;
    test_heap.insert(1);
    test_heap.insert(0);
    test_heap.insert(3);
    test_heap.insert(2);
    test_heap.insert(5);
    test_heap.extractMin();
    test_heap.extractMin();
    test_heap.insert(0);
    std::cout << test_heap.min() << std::endl;
}

int main() {
    f();
    return 0;
}
