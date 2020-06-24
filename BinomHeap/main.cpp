#include <iostream>
#include "BinHeap.h"

void f(){
    BinHeap<int> govno;
    govno.insert(1);
    govno.insert(0);
    govno.insert(3);
    govno.insert(2);
    govno.insert(5);
    govno.extractMin();
    govno.extractMin();
    govno.insert(0);
    std::cout<<govno.min()<<std::endl;
}

int main() {
    f();
    return 0;
}
