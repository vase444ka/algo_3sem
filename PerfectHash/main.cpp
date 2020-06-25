#include <iostream>
#include "Hash.hpp"

const int TESTS = 1000;


std::string random_string(int len){
    std::string res;
    for (int i = 0; i<len; i++)
        res.insert(res.end(), (char)rand_int('a', 'z'));
}

int main() {

    HashTable test_table(std::vector<Student*>{new Student("Ivan Ivanov", 1),
                                     new Student("Petro Petrov", 2),
                                     new Student("Oleg Olegov", 3)});
    if (test_table.getStudent("Ivan Ivanov"))
        std::cout<<"found"<<std::endl;
    if (test_table.getStudent("Viktor Viktorov") == nullptr)
        std::cout<<"not found"<<std::endl;
    if (test_table.getStudent("Petro Petrov"))
        std::cout<<"found"<<std::endl;
    if (test_table.getStudent("Oleg Olegov"))
        std::cout<<"found"<<std::endl;
    if (test_table.getStudent("Vasyl Vasyliev") == nullptr)
        std::cout<<"not found"<<std::endl;


    return 0;
}