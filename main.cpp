//
// Created by 黄颖盈 on 2020/12/1.
//

#include "matrix.h"
void input(Matrix & matrix,string str){
    cout << "Please input the number of rows and columns of "<<str<<" matrix : ";
    cin>>matrix;
    while(matrix.getColumn()==-1){
        cout<<"Your input is wrong! Please retype! "<<endl;
        cout << "Please input the number of rows and columns of "<<str<<" matrix : ";
        cin>>matrix;
    }
}

int main(){

    float data[]={1, 2, 3, 4};
    Matrix matrix1= Matrix(2, 2, data);
    Matrix matrix2= Matrix(2, 2, data);
    float tmpData[] ={4,3,2,1};
    Matrix matrix3= Matrix(2, 2, tmpData);

    if (matrix1==matrix2){
        cout<<"matrix1 equals matrix2."<<endl;
    }
    if (matrix1!=matrix3){
        cout<<"matrix1 doesn't equals matrix3."<<endl<<endl;
    }

    cout<<matrix1*matrix2<<endl;
    cout<<matrix2*4<<endl;
    cout<<3*matrix1<<endl;
    cout<<matrix1+matrix3<<endl;
    cout<<matrix1-matrix3<<endl;

    int choice;
    cout<<"If you want to enter the matrix manually, please input 0, if not, input 1."<<endl;
    cout<<"Please input your choice: ";
    cin>>choice;

    while (choice==0){
        int index;
        cout<<"type 1 : C=A*B "<<endl<<"type 2 : C=A*b "<<endl<<"type 3 : C=a*B "<<endl<<"type 4 : C=A+B "<<endl<<"type 5 : C=A-B "<<endl<<"type 6 : A==B "<<endl<<"type 7 : A!=B "<<endl;
        cout<<"Please input then index: ";
        cin>>index;

        Matrix matrix4;
        Matrix matrix5;
        float coe;

        if(index==1){
            input(matrix4,"first");
            input(matrix5,"second");
            cout<<matrix4*matrix5<<endl;
        }else if(index==2){
            input(matrix4,"the");
            cout<<"Please input a coefficient: ";
            cin>>coe;
            cout<<matrix4*coe<<endl;
        }else if(index==3){
            cout<<"Please input a coefficient: ";
            cin>>coe;
            input(matrix4,"the");
            cout<<coe*matrix4<<endl;
        }else if (index==4){
            input(matrix4,"first");
            input(matrix5,"second");
            cout<<matrix4+matrix5<<endl;
        }else if(index==5){
            input(matrix4,"first");
            input(matrix5,"second");
            cout<<matrix4-matrix5<<endl;
        } else if(index==6){
            input(matrix4,"first");
            input(matrix5,"second");
            cout<< (matrix4==matrix5 ? "true":"false")<<endl<<endl;
        }else if(index==7) {
            input(matrix4,"first");
            input(matrix5,"second");
            cout << (matrix4 != matrix5 ? "true" : "false") << endl<<endl;
        }else {
            cout << "No this type!" << endl;
        }

        cout<<"If you want to continue testing, input 0; if not, input 1."<<endl;
        cout<<"Please input your choice: ";
        cin>>choice;
    }

}
