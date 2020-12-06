//
// Created by 黄颖盈 on 2020/12/1.
//

#ifndef ASSIGNMENT_MATRIX_H
#define ASSIGNMENT_MATRIX_H
#include <iostream>
#include <atomic>
#include <thread>

#include <mutex>
using namespace std;
class Matrix{
private:
    int row;
    int column;
    float * data;
//    int * count;
    atomic_int * count;
public:
    Matrix();
    Matrix(int row,int column,const float * data);
    Matrix(const Matrix& matrix);
    ~Matrix();
    int getColumn() const {return column;}

    Matrix operator*(float coe);
    Matrix operator*(Matrix& matrix) const;
    friend Matrix operator*(float coe,Matrix& matrix);

    Matrix & operator=(const Matrix& matrix);
    Matrix operator+(const Matrix& matrix);
    Matrix operator-(const Matrix& matrix);
    bool operator==(const Matrix& matrix);
    bool operator!=(const Matrix& matrix);

    friend ostream & operator<<(ostream& os,const Matrix& matrix);
    friend istream & operator>>(istream& is,Matrix& other);

};


#endif //ASSIGNMENT_MATRIX_H
