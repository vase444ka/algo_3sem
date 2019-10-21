#ifndef INC_4LAB_MY_CLASS_H
#define INC_4LAB_MY_CLASS_H

template <typename T>
class my_class{
public:
    T data;
    int key;
    my_class(){
        key = 0;
    }
};

template <typename T>
std::ostream& operator<<(std::ostream& out, my_class <T> outp){
    out<<"key: "<<outp.key<<'\n'<<outp.data;
}

template <typename T>
std::istream& operator>>(std::istream& in, my_class <T> inp){
    in>>inp.key>>inp.data;
}

template <typename T>
bool operator < (const my_class <T> &a, const my_class <T> &b){
    return a.key < b.key;
}

template <typename T>
bool operator > (const my_class <T> &a, const my_class <T> &b){
    return a.key > b.key;
}

template <typename T>
bool operator >= (const my_class <T> &a, const my_class <T> &b){
    return a.key >= b.key;
}

template <typename T>
bool operator <= (const my_class <T> &a, const my_class <T> &b){
    return a.key <= b.key;
}

template <typename T>
bool operator == (const my_class <T> &a, const my_class <T> &b){
    return a.key = b.key;
}

#endif
