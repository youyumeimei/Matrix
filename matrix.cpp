//
// Created by 黄颖盈 on 2020/12/1.
//

#include "matrix.h"

float dot_product1(const float *p1, const float * p2, size_t n,int m);
bool judge(string string);
mutex m;

Matrix::Matrix(){
    row=0;
    column=0;
    data=nullptr;
//    this->count=new int ;
    this->count=new atomic_int ;
    *count=1;
}
Matrix::Matrix(int row,int column,const float * data) {
    this->row = row;
    this->column = column;
    this->data=new float[row*column];
    for (int i = 0; i < row*column; ++i) {
        *(this->data+i)=*(data+i);
    }
//    this->count=new int ;
    this->count=new atomic_int ;
    *this->count=1;
}
Matrix::Matrix(const Matrix& matrix){
    this->row=matrix.row;
    this->column=matrix.column;
    this->data=matrix.data;
    this->count=matrix.count;
//    m.lock();
    (*this->count) +=1;
//    m.unlock();
}

Matrix::~Matrix(){
    if (*count==1){
        delete [] data;
        delete count;
    }else{
//        m.lock();
        (*count) -=1;
//        m.unlock();
    }
}

Matrix &Matrix::operator=(const Matrix &matrix) {
    if(this==&matrix){
        return *this;
    }
    if (*count==1){
        delete [] data;
        delete count;
    }else{
//        m.lock();
        (*count)--;
//        m.unlock();
    }
    this->row = matrix.row;
    this->column = matrix.column;
    this->data=matrix.data;
    this->count=matrix.count;
    (*this->count)++;
    return *this;
}

Matrix Matrix::operator*(Matrix& matrix) const{
    cout<<"type 1 : C=A*B "<<endl;
    float *Data =  new float[row * column];
    if (column == matrix.row) {
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < matrix.column; ++j) {
                *(Data + i * matrix.column + j) = dot_product1(data + i * column, matrix.data + j, column,matrix.column);
            }
        }
    } else{
        cout<<"Your two matrices don't match"<<endl;
        return Matrix();
    }
    return Matrix(row,matrix.column,Data);
}
Matrix Matrix::operator*(float coe){
    cout<<"type 2 : C=A*b "<<endl;
    float * Data=new float [row*column];
    for (int i = 0; i < row*column; ++i) {
        *(Data+i)=(*(data+i))*coe;
    }
    return Matrix(row,column,Data);
}
Matrix operator*(float coe, Matrix& matrix) {
    cout<<"type 3 : C=a*B "<<endl;
    float * Data=new float [matrix.row*matrix.column];
    for (int i = 0; i < matrix.row*matrix.column; ++i) {
        *(Data+i)=(*(matrix.data+i))*coe;
    }
    return Matrix(matrix.row,matrix.column,Data);
}

Matrix Matrix::operator+(const Matrix &matrix) {
    cout<<"type 4 : C=A+B "<<endl;
    float * Data=new float [matrix.row*matrix.column];
    if (row==matrix.row&&column==matrix.column){
        for (int i = 0; i < row * column; ++i) {
            *(Data+i)=*(data+i)+*(matrix.data+i);
        }
    } else{
        cout<<"Your two matrices don't match!"<<endl;
        return Matrix();
    }
    return Matrix(row,column,Data);
}
Matrix Matrix::operator-(const Matrix &matrix) {
    cout<<"type 5 : C=A-B "<<endl;
    float * Data=new float [matrix.row*matrix.column];
    if (row==matrix.row&&column==matrix.column){
        for (int i = 0; i < row * column; ++i) {
            *(Data+i)=*(data+i)-*(matrix.data+i);
        }
    } else{
        cout<<"Your two matrices don't match!"<<endl;
        return Matrix();
    }
    return Matrix(row,column,Data);
}

bool Matrix::operator==(const Matrix &matrix) {
    cout<<"type 6 : A==B "<<endl;
    if (row==matrix.row&&column==matrix.column){
        for (int i = 0; i < row * column; ++i) {
            if(*(data+i)!=*(matrix.data+i)){
                return false;
            }
        }
    } else{
        return false;
    }
    return true;
}
bool Matrix::operator!=(const Matrix &matrix) {
    cout<<"type 7 : A!=B "<<endl;
    if (row==matrix.row&&column==matrix.column){
        for (int i = 0; i < row * column; ++i) {
            if(*(data+i)==*(matrix.data+i)){
                return false;
            }
        }
    } else{
        return true;
    }
    return true;
}


ostream & operator<<(ostream& os,const Matrix& matrix){

    os.setf(ios_base::fixed, ios_base::floatfield);
    os.precision(3);

    for (int i = 0; i < matrix.row; ++i) {
        for (int j = 0; j < matrix.column; ++j) {
            os<<*(matrix.data+j+i*matrix.column)<<" ";
        }
        os<<endl;
    }
    return os;
}
istream & operator>>(istream& is,Matrix& matrix){
    int row,column;
    cin >> row >> column;
    matrix.data = new float [row*column]();
    cout<<"Please input items of the  matrix: "<<endl;
    matrix.row=row;
    matrix.column=column;
    bool flag=true;
    for (int i = 0; i < matrix.row * matrix.column; ++i) {
        string string1;
        cin >> string1;

        if (judge(string1)){
            *(matrix.data+i)=stof(string1);
        } else{
            flag= false;
        }
    }
    if (!flag) {
        delete [] matrix.data;
        matrix.column=-1;
    }
    return is;
}

float dot_product1(const float *p1, const float * p2, size_t n,int m)
{
    float sum = 0.0f;
    for (size_t i = 0; i < n; i++)
        sum += (p1[i] * p2[i*m]);
    return sum;
}
bool judge(string string){
    int count1=0;
    int count2=0;
    int count3=0;
    if (string[0]=='-'){
        if (isdigit(string[1])) {
            for (int i = 2; i < string.length(); ++i) {
                if (isdigit(string[i])) {
                } else if (string[i] == '.') {
                    count1++;
                } else if (string[i] == 'E') {
                    count2++;
                    if (i == string.length() - 1) {
                    } else {
                        if (string[i+1] == '-' || string[i+1] == '+'||isdigit(string[i+1])) {
                        } else {
                            return false;
                        }
                        i++;
                    }
                } else if (string[i] == 'e') {
                    count3++;
                    if (i == string.length() - 1) {
                    } else {
                        if (string[i+1] == '-' || string[i+1] == '+'||isdigit(string[i+1])) {
                        } else {
                            return false;
                        }
                        i++;
                    }
                } else {
                    return false;
                }
                if (count1 <= 1 && count2 <= 1 && count3 <= 1) {
                } else {
                    return false;
                }
            }
        } else{
            return false;
        }
    }else if (isdigit(string[0])){
        for (int i = 1; i < string.length(); ++i) {
            if (isdigit(string[i])) {

            }else if (string[i]=='.'){
                count1++;
            }else if (string[i]=='E') {
                count2++;
                if (i == string.length() - 1) {
                } else {
                    if (string[i + 1] == '-' || string[i + 1] == '+' || isdigit(string[i + 1])) {
                    } else {
                        return false;
                    }
                    i++;
                }
            }else if (string[i]=='e') {
                count3++;
                if (i == string.length() - 1) {
                } else {
                    if (string[i + 1] == '-' || string[i + 1] == '+' || isdigit(string[i + 1])) {
                    } else {
                        return false;
                    }
                    i++;
                }
            }else{
                return false;
            }
            if (count1<=1&&count2<=1&&count3<=1){
            }else{
                return false;
            }
        }
    } else{
        return false;
    }
    return true;
}