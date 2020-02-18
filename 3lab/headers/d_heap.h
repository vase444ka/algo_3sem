#ifndef INC_3LAB_D_HEAP_H
#define INC_3LAB_D_HEAP_H

#include <vector>
#include <algorithm>

template <typename T, int d>
class d_heap;

template <typename T, int d>
std::ostream& operator<<(std::ostream&, const d_heap<T, d>&);

template <typename T, int d>
class d_heap{
    std::vector <T> data;
    void restore(int);
    void move_up(int);
    int max_son(int);
public:
    d_heap(const std::vector <T> &val = {});
    T extract_max();
    void insert(T);
    void increase_key(int pos, T diff);
    int size();
    friend std::ostream& operator<< <T, d> (std::ostream& out, const d_heap<T, d> &a);
};

template <typename T, int d>
int d_heap<T, d>::size(){
    return data.size();
}

template <typename T, int d>
int d_heap<T, d>:: max_son(int dad){
    if (dad < 0 || dad >= data.size())
        return -1;

    int sample = dad;
    for (int i = dad*d + 2; i < std::min(int(data.size()), dad*d + d + 1); i++)
        if (data[i] > data[sample])
            sample = i;

    return sample;
}

template <typename T, int d>
void d_heap<T, d>::restore(int from) {//key of higher is smaller than key of lower
    int to = max_son(from);
    if (to > from){
        std::swap(data[from], data[to]);
        restore(to);
    }
}

template <typename T, int d>
void d_heap<T, d>::move_up(int cur_son){ //current key is larger then father key
    while(cur_son > 0){                 //subtree keys are smaller then father key
        int cur_dad = (cur_son - 1)/d;
        if (data[cur_son] <= data[cur_dad])
            break;
        std::swap(data[cur_son], data[cur_dad]);
        cur_son = cur_dad;
    }
}

template <typename T, int d>
d_heap<T, d>::d_heap(const std::vector<T> &val) {
    data = val;
    for (int i = int(data.size()) - 1; i >= 0; i--)
        restore(i);
}

template <typename T, int d>
T d_heap<T, d>::extract_max() {
    if (data.size())
        return data[0];
}

template <typename T, int d>
void d_heap<T, d>::insert(T val) {
    data.push_back(val);
    int cur_son = data.size() - 1;
    move_up(cur_son);
}

template <typename T, int d>
void d_heap<T, d>::increase_key(int key_pos, T diff) {
    if (key_pos >= data.size() || key_pos < 0)
        return;

    data[key_pos] += diff;
    move_up(key_pos);
}

template <typename T, int d>
std::ostream &operator<<(std::ostream &out, const d_heap <T, d> &a) {
    std::cout<<std::endl<<"size: "<<a.data.size()<<std::endl;
    int max_w = 1;
    int tmp = 1;
    while(tmp < a.data.size()){
        max_w*=d;
        tmp+=max_w;
    }
    bool is_break = false;
    int cur_start = 0;
    for (int i = 1; ;i*=d){
        int cur_space = max_w/i - 1;
        for (int j = cur_start; j < cur_start + i; j++)
            if (j < a.data.size()) {
                std::cout << a.data[j] << "   ";
                for (int k = 0; k < cur_space; k++)
                    std::cout << ' ';
            }
            else{
                is_break = true;
                break;
            }
        std::cout<<"---------------------endrow----------"<<std::endl;
        cur_start+=i;
        if (is_break)
            break;
    }
    return out;
}

#endif //INC_3LAB_D_HEAP_H
