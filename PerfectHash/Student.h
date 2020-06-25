//
// Created by vbory on 6/25/2020.
//

#ifndef PERFECT_HASH_STUDENT_H
#define PERFECT_HASH_STUDENT_H

#include <string>

class Student{
public:
    Student() = default;
    Student(std::string name, int group);
    [[nodiscard]] std::string getName() const;
    [[nodiscard]] int getGroup() const;
    [[nodiscard]] int hash(int a, int b, int mod, int prime) const;
private:
    std::string _name;
    int _group;
};

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

#endif //PERFECT_HASH_STUDENT_H
