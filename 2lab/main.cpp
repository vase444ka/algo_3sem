#include <iostream>
#include <vector>
#include <time.h>

using namespace std;

const int SIZE = 1000;

template <typename T>
void solution(vector <T> &screw, vector <T> &nut, int from, int to){
    if (from >= to) return;

    int pivot_screw = from;
    int l = from, r = to;
    while (l < r){
        while (l < r && nut[l] < screw[pivot_screw])
            l++;
        while (l < r && nut[r] > screw[pivot_screw])
            r--;

        if (l < r)
            swap(nut[l], nut[r]);
    }
    swap(screw[pivot_screw], screw[l]);
    int pivot_nut = l;
    l = from; r = to;
    while (l < r){
        while (l < r && screw[l] < nut[pivot_nut])
            l++;
        while (l < r && screw[r] > nut[pivot_nut])
            r--;

        if (l < r)
            swap(screw[l], screw[r]);
    }
    solution(screw, nut, from, l - 1);
    solution(screw, nut, l + 1, to);
}

void generate_rand(vector <int> &vec,  int N){
    int used[N];

    for (int i = 0; i <N; i++)
        used[i] = 0;

    for (int i = 0; i < N; i++){
        int tmp = rand()%N;
        while(used[tmp])
            tmp = rand()%N;
        vec.push_back(tmp);
        used[tmp] = 1;
    }

}

int main() {
    srand(time(0));
    vector <int> nut;
    vector <int> screw;

    generate_rand(nut, SIZE);
    generate_rand(screw, SIZE);

    for (int i = 0; i < SIZE; i++)
        cout<<nut[i]<<" - "<<screw[i]<<endl;
    cout<<endl;

    solution(screw, nut, 0, SIZE - 1);

    for (int i = 0; i < SIZE; i++)
        cout<<nut[i]<<" - "<<screw[i]<<endl;


    return 0;
}