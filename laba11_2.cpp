#include <iostream>
#include <vector>
#include <fstream>
#include <time.h>
#include <math.h>

using namespace std;

template<typename T>
void Print2_1(const vector<T>& arr){
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] == 2) {
            cout << i << " ";
        }
    }
}

void laba2_1(){
    int isize = 10001;
    vector<int> arr(isize, 0);
    ifstream file("./numbers.txt");
    if (file.is_open()) {
        int temp = 0;
        while (file >> temp) {
            arr[temp] = arr[temp] + 1;
        }
    }
    Print2_1(arr);
}




int f(int i, int j, int value){
    return i * value + j;
}

template<typename T>
vector<T> matrixsum(vector<T> matrix1, const vector<T>& matrix2){
    for(int i = 0; i < sqrt(matrix2.size()); i++){
        for(int i_n = 0; i_n < sqrt(matrix2.size()); i_n++){
            matrix1[f(i, i_n, sqrt(matrix2.size()))] += matrix2[f(i, i_n, sqrt(matrix2.size()))];
        }
    }
    return matrix1;
}

template<typename T>
vector<T> matrixmultiply(const vector<T>& matrix0, const vector<T>& matrix1){
    vector<T> tempmatrix(matrix0.size());
    for(int i = 0; i < sqrt(matrix0.size()); i++){
        for(int i_n = 0; i_n < sqrt(matrix0.size()); i_n++){
            int sum = 0;
            for(int counter = 0; counter < sqrt(matrix0.size()); counter++){
                sum += matrix0[f(i, counter, sqrt(matrix0.size()))] * matrix1[f(counter, i_n, sqrt(matrix0.size()))];
            }
            tempmatrix[f(i, i_n, sqrt(matrix0.size()))] = sum;
        }
    }
    return tempmatrix;
}

template<typename T>
void Print2_2(const vector<T>& matrix){
    for(int i = 0; i < sqrt(matrix.size()); i++){
        for(int i_n = 0; i_n < sqrt(matrix.size()); i_n++){
            printf("%20.3f",matrix[f(i, i_n, sqrt(matrix.size()))]);
        }
        cout << endl;
    }
}

void laba2_2(){
    srand(time(nullptr));
    cout << "Enter matrix size: ";
    int isize = 0;
    cin >> isize;

    cout << "Enter max matrix power: ";
    int ipower = 0;
    cin >> ipower;
    
    vector<double> matrix(isize * isize);
    vector<double> E(isize * isize);
    
    for(int i = 0; i < isize; i++){
        for(int i_n = 0; i_n < isize; i_n++){
            matrix[f(i, i_n, isize)] = rand() % 100;     // matrix.pushback(rand() % 100)
            E[f(i, i_n, isize)] = 0;
        }
        E[f(i, i, isize)] = 1;
    }

    Print2_2(matrix);
    cout << endl;
    
    vector<double> prevmatrix(matrix);
    vector<double> resualtmatrix(matrix);

    resualtmatrix = matrixsum(prevmatrix, E);
    for(int i = 2; i <= ipower; i++){
        prevmatrix = matrixmultiply(matrix, prevmatrix);
        resualtmatrix = matrixsum(resualtmatrix, prevmatrix);
    }
    Print2_2(resualtmatrix);
}

int main(){
    int key = 0;
    cout << "Enter 1 if u want complite 2_1 and 2 for 2_2: ";
    cin >> key;
    switch(key){
        case 1:{
            laba2_1();
            break;
        }
        case 2: {
            laba2_2();
            break;
        }
        default: {
            cout << "Try to read!";
            return 0;
        }
    }
    return 0;
}