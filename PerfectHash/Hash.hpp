#ifndef PERFECT_HASH_HASH_HPP
#define PERFECT_HASH_HASH_HPP

#include <vector>
#include <random>
#include <ctime>
#include <conio.h>
#include <iostream>
#include "Student.h"

class HashNode {
public:
    HashNode() = default;
    void fill(int p);
    Student *getStudent(const std::string &str, int p);
    void insertToTmp(Student* ins);
private:
    int _a;
    int _b;
    int _mod;
    std::vector<Student*> _tmp;
    std::vector<Student*> _elements;
};

class HashTable {
public:
    HashTable(std::vector<Student *> elements);
    Student *getStudent(const std::string &str);

private:
    std::vector<HashNode> _data;
    int _prime, _modulo, _a, _b;
};

int rand_int(int min, int max);


#endif //PERFECT_HASH_HASH_HPP