#include <iostream>
#include <stdlib.h>
#include <iomanip>

using namespace std;
int** getRandMatrix() {
    int M = rand() % 10 + 1,N;
    int** matrix = new int* [M];
    for (int i = 0; i < M; i++) {
        N = rand() % 10 + 1;
        matrix[i] = new int[N];
        matrix[i][0] = N;
        for (int j = 1; j < N; j++) {
            matrix[i][j] = rand() % 10 + 1;
        }
    }
    matrix[0][0] = M;
    return matrix;
}
void printMatrix(int** matrix) {
    for (int i = 1; i < matrix[0][0]; i++) {
        for (int j = 0; j < matrix[i][0]; j++) {
            cout << setw(5) << matrix[i][j] << " ";
        }
        cout << endl;
    }
}
int main()
{
    setlocale(LC_ALL, "ru");
    //srand(time(0));
    int** matrix = getRandMatrix();
    printMatrix(matrix);
}
