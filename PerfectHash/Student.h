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

#endif //PERFECT_HASH_STUDENT_H
