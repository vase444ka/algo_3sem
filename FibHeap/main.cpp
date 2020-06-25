#include <iostream>

#include "FibHeap.h"

int main() {

    FibHeap<int> test_heap;
    for (int i = 9; i >= 0; i--) {
        test_heap.insert((i*2)%10);
    }

    auto iterator = test_heap.tmpMin();
    for (int i = 0;  i < 10; i++){
        iterator->tmpAll();
        iterator = iterate(iterator);
    }


    return 0;
}
