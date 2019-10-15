#include <iostream>
#include <vector>
#include <time.h>

using namespace std;

const int SIZE = 10;

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


int main() {
    srand(time(0));
    vector <int> nut;
    vector <int> screw;

    for (int i = 0; i < SIZE; i++){
        nut.push_back(9 - i);
        screw.push_back((5 + i)%10);
    }

    for (int i = 0; i < 10; i++)
        cout<<nut[i]<<" - "<<screw[i]<<endl;
    cout<<endl;

    solution(screw, nut, 0, 9);

    for (int i = 0; i < 10; i++)
        cout<<nut[i]<<" - "<<screw[i]<<endl;


    return 0;
}