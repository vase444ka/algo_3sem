#include <iostream>
#include <vector>
#include <time.h>
#include "headers/my_class.h"
#include "headers/sorts.h"

const int N = 10;

void randomize(std::vector <my_class <int> > &data){
    for (int i = 0; i < N; i++){
        my_class <int> tmp;
        tmp.key = rand()%2;
        tmp.data = rand();
        data.push_back(tmp);
    }

}

int main() {
    srand(time(0));
    std::vector <my_class <int> > data;
    randomize(data);

    std::cout<<"My vector:\n";
    for (auto &&it: data)
        std::cout<<it<<std::endl;

    //TODO time here

    int sort_type;
    std::cout<<"Enter:\n1 - bubble sort\n2 - count sort\n3 - swap sort\n";
    std::cin>>sort_type;

    if (sort_type == 1)
        bubble_sort(data);
    if (sort_type == 2)
        counting_sort(data);
    if (sort_type == 3)
        swap_sort(data);

    std::cout<<"Sorted vector:\n";
    for (auto &&it: data)
        std::cout<<it<<std::endl;

    return 0;
}