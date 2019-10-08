#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <string>
#include <bits/stdc++.h>

//create files table
//rewrite sorted chunks into newly created files
//merging

const int RAM_SIZE = 4;

int neutral(){
    return -1;
}

//requires correct data
int* create_distribution(int data_N, const int FILES_N, int &chunks_N){
    if (data_N < 1)
        return nullptr;

    int precounted_chunks = ceil(data_N/double(RAM_SIZE));
    int prev_max = 1;
    bool is_max_taken = false;
    chunks_N = 1;
    int *distrib = new int[FILES_N];

    distrib[0] = 1;
    for (int i = 1; i<FILES_N; i++)
        distrib[i] = 0;

    while(chunks_N < precounted_chunks){
        int new_max = prev_max;
        chunks_N += prev_max*(FILES_N - 2);
        for (int i = 0; i < FILES_N; i++){
            if (distrib[i] == prev_max && !is_max_taken){
                distrib[i] = 0;
                is_max_taken = true;
            }
            else
                distrib[i] += prev_max;
            new_max = std::max(new_max, distrib[i]);
        }
        is_max_taken = false;
        prev_max = new_max;
    }

    return distrib;
}

template <typename T>
class sort_heap{
    T *body;
    int size;

    void restore(int v){
        int left_son = v*2 + 1;
        int right_son = v*2 + 2;
        int to = v;

        if (left_son < size && body[left_son] < body[to])
            to = left_son;
        if (right_son < size && body[right_son] < body[to])
            to = right_son;

        if (to != v){
            std::swap(body[v], body[to]);
            restore(to);
        }
    }

public:
    sort_heap(std::vector <T> &data, int from, int to){
        if (from > to || from < 0 || to < 0 || from >= int(data.size()) || to >= int(data.size()))
            return;
        size = to - from + 1;
        body = new T[size];
        for (int i = 0; i < size; i++)
            body[i] = data[from + i];

        for (int i = size - 1; i >= 0; i--)
            restore(i);
    }

    void erase(int v){
        if (v >= size || v < 0)
            return;
        std::swap(body[v], body[size - 1]);
        size--;
        restore(v);

    }

    T top(){
        return body[0];
    }

};

template <typename T>
void heap_sort(std::vector <T> &dat, int from, int to){//[from, to]
    if (from > to || from < 0 || to < 0 || from >= int(dat.size()) || to >= int(dat.size()))
        return;

    sort_heap <T> heap(dat, from, to);

    for (int i = from; i <= to; i++){
        dat[i] = heap.top();
        heap.erase(0);
    }
}

bool is_bigger(int cur_chunk, int chunks_N, int data_N){
    return cur_chunk <= data_N % chunks_N;
}

template <typename T>//n chunks in shrt, k in lng, 0 in dest, n <= k
void merge(std::fstream &destin, std::fstream &shrt, std::fstream &lng){
    while(!shrt.eof() && !lng.eof()){
        T shrt_inp, lng_inp;
        //shrt>>shrt_inp;
        //lng>>lng_inp;
        shrt.read((char*)shrt_inp, sizeof(T));
        lng.read((char*)lng_inp, sizeof(T));
        if (shrt.eof() || lng.eof())
            break;
        while(!shrt.eof() && !lng.eof() && shrt_inp != neutral() && lng_inp != neutral()){
            if (shrt_inp < lng_inp){
                //destin<<' '<<shrt_inp;
                //shrt>>shrt_inp;
                destin.write(reinterpret_cast <char*> (&shrt_inp), sizeof(T));
                shrt.read((char*)shrt_inp, sizeof(T));
            }
            else{
                //destin<<' '<<lng_inp;
                //lng>>lng_inp;
                destin.write(reinterpret_cast <char*> (&lng_inp), sizeof(T));
                lng.read((char*)lng_inp, sizeof(T));
            }
        }
        while(!shrt.eof() && shrt_inp != neutral()){
            //destin<<' '<<shrt_inp;
            //shrt>>shrt_inp;
            destin.write(reinterpret_cast <char*> (&shrt_inp), sizeof(T));
            shrt.read((char*)shrt_inp, sizeof(T));
        }
        while(!lng.eof() && lng_inp != neutral()){
            //destin<<' '<<lng_inp;
            //lng>>lng_inp;
            destin.write(reinterpret_cast <char*> (&lng_inp), sizeof(T));
            lng.read((char*)lng_inp, sizeof(T));
        }

        //destin<<' '<<neutral();
        T neutr = neutral();
        destin.write(reinterpret_cast<char*> (&neutr), sizeof(T));

    }
}

template <typename T>
void multiphase_sort(std::fstream &data){
    const int FILES_N = 3;
    int data_N, *distrib, chunks_N, cur_chunk = 1;
    std::fstream used_files[FILES_N];
    //read from data
    //TODO binary i/o

    data>>data_N;
    distrib = create_distribution(data_N, FILES_N, chunks_N);
    int chunk_size = data_N/chunks_N;

    for (int i = 0; i < FILES_N; i++){
        used_files[i].open(std::to_string(i)+".txt", std::ios::in | std::ios::out | std::ios::trunc);

        for (int j = 0; j < distrib[i]; j++){

            std::vector <T> tmp;
            T input;
            for (int k = 0; k < chunk_size + is_bigger(cur_chunk, chunks_N, data_N); k++){
                data>>input;
                tmp.push_back(input);
            }

            heap_sort(tmp, 0, tmp.size() - 1);

            for (auto &&it: tmp){
                used_files[i]<<' '<<it;
                //used_files[i].write(std::to_string(it).c_str(), sizeof(T));
            }

            used_files[i]<<' '<<neutral();
            //used_files[i].write(std::to_string(neutral()).c_str(), sizeof(T));


            cur_chunk++;
        }
        used_files[i].seekp(0);
        used_files[i].seekg(0);

    }

    std::set <std::pair<int, int> > cur_file; //first - size, second - num
    int destin;
    for (int i = 0; i < FILES_N; i++)
        if (distrib[i] > 0)
            cur_file.insert({-distrib[i], i});
        else
            destin = i;

    for (auto &&it: cur_file)
            std::cout<<it.first<<' '<<it.second<<std::endl;
    std::cout<<std::endl;

    while(cur_file.size() > 1){
        int lng = cur_file.begin()->second;
        cur_file.erase(cur_file.begin());

        int shrt = cur_file.begin()->second;
        cur_file.erase(cur_file.begin());

        if (distrib[shrt] != distrib[lng])
            cur_file.insert({distrib[shrt] - distrib[lng], lng});
        cur_file.insert({-distrib[shrt], destin});
        distrib[destin] = distrib[shrt];
        distrib[lng] -= distrib[shrt];
        distrib[shrt] = 0;

        std::cout<<destin<<' '<<shrt<<' '<<lng<<std::endl;
        merge <T> (used_files[destin], used_files[shrt], used_files[lng]);
        used_files[destin].seekp(0);
        used_files[destin].seekg(0);
        destin = shrt;

        for (auto &&it: cur_file)
            std::cout<<it.first<<' '<<it.second<<std::endl;
        std::cout<<std::endl;

        used_files[shrt].close();
        used_files[shrt].open(std::to_string(shrt)+".txt", std::ios::in | std::ios::out | std::ios::trunc | std::ios::binary);
    }

    data.seekp(0);
    data.seekg(0);
    data<<data_N<<'\n';
    if (cur_file.size() == 1){
        int res = cur_file.begin()->second;
        T tmp;
        used_files[res].seekg(0);
        used_files[res]>>tmp;
        //char *str_tmp;
        //used_files[res].read(str_tmp, sizeof(T));
        //tmp = atoi(str_tmp);
        while(!used_files[res].eof() && tmp != neutral()){
            std::cout<<tmp<<"\n";
            data<<tmp<<' ';
            used_files[res]>>tmp;
            //used_files[res].read(str_tmp, sizeof(T));
            //tmp = atoi(str_tmp);
        }
    }

    /*for (int i = 0; i < FILES_N; i++){
        used_files[i].close();
        std::string tmp_1 = std::to_string(i) + ".txt";
        const char* tmp = tmp_1.c_str();
        std::remove(tmp);
    }*/
}

int main()
{
    std::fstream in("input.txt");
    multiphase_sort <int> (in);
    return 0;
}
