//
// Created by vbory on 6/25/2020.
//
#include "Student.h"

Student::Student(std::string name, int group):_name(name), _group(group) {}

std::string Student::getName() const {
    return _name;
}

int Student::getGroup() const {
    return _group;
}

int Student::hash(int a, int b, int mod, int prime) const{
    int h = 0;
    for (char i : _name) {
        h = (b + a * (h + (int) i)) % prime;
    }
    return h % mod;
}

