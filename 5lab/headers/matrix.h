#ifndef INC_5LAB_MATRIX_H
#define INC_5LAB_MATRIX_H

#include <fstream>

const unsigned int efficient = 5;

struct point{int x, y;};

template <typename T>
class matrix_view;

template <typename T>
class matrix{
    T **matr;
    int n, m;
public:
    matrix(int n, int m, int is_rand = 0);
    friend std::ostream operator<<(std::ostream&, const matrix&);
    friend std::istream operator>>(const std::istream&, matrix&);
    friend matrix operator+(const matrix&, const matrix&);
    friend matrix operator-(const matrix&, const matrix&);
    friend matrix operator*(const matrix&, const matrix&);
    friend matrix operator^(const matrix&, const matrix&);
    std::pair <int, int> get_size();
    ~matrix();

    friend class matrix_view <T>;
};

template <typename T>
class matrix_view{
    matrix <T> *viewed;
    point upper_left, lower_right;
    int n, m;
public:
    matrix_view(matrix <T>* to_view, int x1, int y1, int x2, int y2){
        viewed = to_view;
        if (x1 > x2 || y1 > y2){
            upper_left = {0, 0};
            lower_right = {0, 0};
            n = 1;
            m = 1;
        }
        else{
            upper_left = {x1, y1};
            lower_right = {x2, y2};
            n = y2 - y1 + 1;
            m = x2 - x1 + 1;
        }
    }
    friend matrix<T> operator+(const matrix_view&, const matrix_view&);
    friend matrix<T> operator-(const matrix_view&, const matrix_view&);
    friend matrix<T> operator*(const matrix_view&, const matrix_view&);
    friend matrix<T> operator^(const matrix_view&, const matrix_view&);
    ~matrix_view() = default;
};

template <typename T>
matrix<T>::matrix(int given_n, int given_m, int is_rand){
    if (given_n < 1 || given_m < 1) return;
    n = given_n;
    m = given_m;

    matr = new T*[n];
    for (int i = 0; i < n; i++){
        matr[i] = new T[m];
        if (is_rand)
            for (int j = 0; j < m; j++);//TODO
    }
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const matrix<T>& A){

    for (int i = 0; i < A.n; i++){
        for (int j = 0; j < A.m; j++)
            out<<A.matr[i][j]<<' ';
        out<<'\n';
    }
    return out;
}

template <typename T>
std::istream& operator>>(const std::istream& in, matrix<T>& A){
    for (int i = 0; i < A.n; i++)
        for (int j = 0; j < A.m; j++)
            in>>A.matr[i][j];
    return in;
}

template <typename T>
matrix<T> operator+(const matrix<T>& A, const matrix<T>& B){
    if (A.n != B.n || A.m != B.m){
        matrix <T> res(0, 0);
        return res;
    }

    matrix <T> res(A.n, A.m);
    for (int i = 0; i < res.n; i++)
        for (int j = 0; j < res.m; j++)
            res.matr[i][j] = A.matr[i][j] + B.matr[i][j];
}

template <typename T>
matrix<T> operator-(const matrix<T>& A, const matrix<T>& B){
    if (A.n != B.n || A.m != B.m){
        matrix <T> res(0, 0);
        return res;
    }

    matrix <T> res(A.n, A.m);
    for (int i = 0; i < res.n; i++)
        for (int j = 0; j < res.m; j++)
            res.matr[i][j] = A.matr[i][j] - B.matr[i][j];
}

template <typename T>
matrix<T> operator*(const matrix<T>& A, const matrix<T>& B){
    if (A.m != B.n){
        matrix <T> res(0, 0);
        return res;
    }

    int q = A.m;

    matrix <T> res(A.n, B.m);
    for (int i = 0; i < A.n; i++)
        for (int j = 0; j < B.m; j++){
            res.matr[i][j] = 0;
            for (int k = 0; k < q; k++)
                res.matr[i][j] += A.matr[i][k]*B.matr[k][j];
        }
    return res;
}

template <typename T>
matrix<T> operator^(const matrix<T>& A, const matrix<T>& B){
    if (A.m != B.n){
        matrix <T> res(0, 0);
        return res;
    }

    //todo resize

    if (A.m <= 1<<efficient) {
        return A*B;
    }

    /*n = n >> 1;


    int[][] p1 = (a11 + a22)^(b11 + b22);
    int[][] p2 = (a21 + a22)^b11;
    int[][] p3 = a11^(b12 - b22);
    int[][] p4 = a22^(b21 - b11);
    int[][] p5 = (a11 + a12)^b22;
    int[][] p6 = (a21 - a11)^(b11 + b12);
    int[][] p7 = (a12 - a22)^(b21 + b22);

    int[][] c11 = (p1 + p4) + (p7 - p5);
    int[][] c12 = p3 + p5;
    int[][] c21 = p2 + p4;
    int[][] c22 = (p1 - p2) + (p3 + p6);
     newmatr = m.slice(n/2, n/2);
     */
}

template <typename T>
std::pair <int, int> matrix<T>::get_size(){
    return {n, m};
}

template <typename T>
matrix<T>::~matrix(){
    //TODO
}

#endif //INC_5LAB_MATRIX_H
