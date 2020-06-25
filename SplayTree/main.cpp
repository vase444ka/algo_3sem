#include "SplayTree.hpp"

#include <iostream>

int main() {
    SplayTree<int> test_tree{4, 5, 7, 9};
    test_tree.insert(1);
    test_tree.insert(2);
    test_tree.insert(3);
    if (test_tree.search(5))
        std::cout<<"found"<<std::endl;

    return 0;
}
