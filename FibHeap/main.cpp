#include <iostream>

#include "FibHeap.h"

int main() {

    FibHeap<int> test_heap;
    for (int i = 9; i >= 0; i--) {
        test_heap.insert((i*2)%10);
    }
    test_heap.extractMin();
    for (int i = 9; i >= 0; i--) {
        test_heap.insert((i*3)%10);
    }

    auto iterator = test_heap.tmpMin();
    for (int i = 0;  i < 19; i++){
        iterator->tmpAll();
        iterator = iterate(iterator);
    }


    return 0;
}
