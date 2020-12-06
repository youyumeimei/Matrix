//
// Created by 黄颖盈 on 2020/12/2.
//
#include <iostream>
#include <chrono>
#include "matrix.h"
using namespace std;
float data[]={1,1,1,1};

void thread01(Matrix & matrix1){
    for (int i = 1; i < 10000; i++){
        Matrix a (matrix1);
    }
}

int main(){
    Matrix matrix1(2,2,data);

    auto start = std::chrono::steady_clock::now();
    thread task01(thread01,ref(matrix1));
    thread task02(thread01,ref(matrix1));
    thread task03(thread01,ref(matrix1));
    thread task04(thread01,ref(matrix1));
    thread task05(thread01,ref(matrix1));
    task01.join();
    task02.join();
    task03.join();
    task04.join();
    task05.join();
    auto end = std::chrono::steady_clock::now();
    cout<< "The Multithreading consumes "
        << chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "µs ≈ "
        << chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms ≈ "
        << chrono::duration_cast<std::chrono::seconds>(end - start).count() << "s.\n";
    return 0;
}