#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include "../4lab/headers/my_class.h"

const int N = 100;

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
    std::vector <my_class<int> > data;
    randomize(data);
    freopen("input.txt", "w", stdout);
    for (auto &&it: data)
        std::cout<<it<<std::endl;
    return 0;
}