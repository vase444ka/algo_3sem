#include <iostream>
#include <random>
#include "time.h"
#include "headers/d_heap.h"

const int OPTS_AMOUNT = 1000;
const int MAXVAL = 100;
const int RETURN_MAX = 2;
const int INC_KEY = 1;
const int INSERT = 0;
const int d = 4;

int main() {
    freopen("output_sample.txt", "w", stdout);
    int start = clock();

    std::mt19937 rand_gen(1);
    std::uniform_int_distribution<int> vals_distr(-MAXVAL, MAXVAL);

    std::vector <int> initial_data;
    std::cout<<"INITIAL DATA: \n";
    for (int i = 0; i < OPTS_AMOUNT; i++){
        int tmp = vals_distr(rand_gen);
        initial_data.push_back(tmp);
        std::cout<<tmp<<' ';
    }
    std::cout<<'\n';
    d_heap <int, d> my_heap(initial_data);

    std::cout<<"NUMBER OF OPERATIONS TO BE DEMONSTRATED: "<<OPTS_AMOUNT<<'\n';

    std::uniform_int_distribution<int> opts_distr(INSERT, RETURN_MAX);

    for (int i = 0; i < OPTS_AMOUNT; i++){
        int cur_op = opts_distr(rand_gen);

        if (cur_op == RETURN_MAX){
            std::cout<<"current maximum: "<<my_heap.extract_max()<<'\n';
        }
        if (cur_op == INC_KEY){
            int diff = abs(vals_distr(rand_gen));
            int pos = std::uniform_int_distribution <int> (0, my_heap.size() - 1) (rand_gen);
            std::cout<<"changing "<<pos<<"th element by "<<diff<<'\n';
            my_heap.increase_key(pos, diff);
        }
        if (cur_op == INSERT){
            int inserted_val = vals_distr(rand_gen);
            std::cout<<"inserting "<<inserted_val<<'\n';
            my_heap.insert(inserted_val);
        }
    }

    std::cout<<my_heap;
    std::cout<<"it took "<<(clock() - start)/double(CLOCKS_PER_SEC)<<"s to execute\n";
    return 0;
}