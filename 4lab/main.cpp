#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include "headers/my_class.h"
#include "headers/sorts.h"

int main() {
    std::vector <my_class <int> > data;

    std::ifstream in("../../4lab_randomizer/cmake-build-debug/input.txt");

    my_class <int> input;
    while(in>>input){
        //std::cout<<input<<std::endl;
        data.push_back(input);
    }

    int sort_type;
    std::cout<<"Enter:\n1 - bubble sort\n2 - count sort\n3 - swap sort\n";
    std::cin>>sort_type;

    //int tacts = clock();

    if (sort_type == 1)
        bubble_sort(data);
    if (sort_type == 2)
        counting_sort(data);
    if (sort_type == 3)
        swap_sort(data);

    int tacts = clock(); //- tacts;

    std::cout<<"Time needed for algorithm: "<< (float(tacts)) / CLOCKS_PER_SEC <<" s.\n";

    std::cout<<"Sorted vector:\n";
    for (auto &&it: data)
        std::cout<<it<<std::endl;

    return 0;
}