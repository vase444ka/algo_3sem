#ifndef INC_4LAB_SORTS_H
#define INC_4LAB_SORTS_H

#include <vector>
#include <algorithm>
#include "../headers/my_class.h"

//[from, to)

template <typename T>
void counting_sort(std::vector <my_class <T> >&); //stable, O(N) time

template <typename T>
void bubble_sort(std::vector <my_class <T> >&); //stable, O(1) memory

template <typename T>
void swap_sort(std::vector <my_class <T> >&); //O(N) time, O(1) memory

#include "../includes/sorts.inc"
#endif //INC_4LAB_SORTS_H
