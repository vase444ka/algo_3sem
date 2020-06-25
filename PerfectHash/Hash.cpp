#include "Hash.hpp"

int rand_int(int min, int max) {
    static std::random_device rd;
    static std::seed_seq seed{rd(), static_cast<unsigned int>(time(nullptr))};
    static std::mt19937_64 gen(seed);
    std::uniform_int_distribution<int> dist(min, max);

    return dist(gen);
}

void HashNode::fill(int p) {
    _mod = (int) (_tmp.size() * _tmp.size());
    std::cout << "MJ: " << _tmp.size() << std::endl << std::endl;

    if (_mod == 1) {
        _elements = _tmp;
        _tmp.clear();
        return;
    }

    bool flag = false;
    while (!flag) {
        _elements.clear();
        _elements = std::vector<Student *>(_mod, nullptr);
        _a = rand_int(1, p - 1);
        _b = rand_int(0, p - 1);

        flag = true;
        for (auto &student: _tmp) {
            int index = student->hash(_a, _b, _mod, p);
            if (_elements[index] != nullptr) {
                flag = false;
                break;
            }
            _elements[index] = student;
        }
    }


}

Student *HashNode::getStudent(const std::string &str, int p) {
    Student temp = Student(str, 1);
    return _elements[temp.hash(_a, _b, _mod, p)];
}

void HashNode::insertToTmp(Student* ins) {
    _tmp.push_back(ins);
}


HashTable::HashTable(const std::vector<Student *> &elements) {
    _prime = 2153;
    _modulo = 50;
    _data = std::vector<HashNode>(_modulo);

    _a = rand_int(1, _prime - 1);
    _b = rand_int(0, _prime - 1);

    for (auto &e:elements) {
        _data[e->hash(_a, _b, _modulo, _prime)].insertToTmp(e);
    }

    for (auto &node:_data) {
        node.fill(_prime);
    }
}

Student *HashTable::getStudent(const std::string &str) {
    Student temp = Student(str, 1);
    return _data[temp.hash(_a, _b, _modulo, _prime)].getStudent(str, _prime);
}