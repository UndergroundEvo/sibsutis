#include <iostream>
#include <iomanip>
using namespace std;

int** getRandMatrix(int N) {
    int** matrix = new int* [N];
    for (int i = 0; i <= N; i++) {
        matrix[i] = new int[N];
        for (int j = 0; j < N; j++) {
            matrix[i][j] = rand() % 100 + 1;
        }
    }
    matrix[0][0] = N;
    return matrix;
}
/*
int* getRandArray(int D) {
    int* array = new int [D];
    array[0] = rand() % 10 + 1;
    for (int i = 1; i < array[0]; i++) array[i] = rand() % 100 + 1;
    return array;
}
*/
int* getArray_A(int** matrix) {
    int kolvo = 0,u=-1, N=matrix[0][0];
    for (int i = 0; i <= N; i++) {
        u++;
        for (int j = N--; j >= u; j--) kolvo++;
    }
    //for (int j = matrix[0][0]; j > 1; j--) for (int i = 0; i < matrix[0][0]; i++) kolvo++;
    int* array = new int[kolvo++];
    u = 0;
    //int k = matrix[0][0];
    for (int k=1,j = matrix[0][0]; j > 1; j--)
    {
        for (int i = 0; i < matrix[0][0]; i++)
        {
            array[k] = matrix[j][i];
                k++;
            }
        }
    /*for (int i = 1; i <= matrix[0][0]; i++) {
        for (int j = matrix[0][0]; j >= u; j--,u++) {
            array[u] = matrix[j][i];
        }
    }*/
    /*for (int i = 1,j=matrix[0][0]; i <= kolvo; i++,j--) {
        array[i] = matrix[i][j];
    }*/

    array[0] = kolvo;
    return array;
    } 
void printMatrix(int** matrix) {
    int N = matrix[0][0];
    for (int i = 0; i < N; i++) {
        cout<< setw(5) << matrix[i][0] << ": ";
        for (int j = 1; j < N; j++) {
            cout<<setw(5)<< matrix[i][j] << " ";
        }
        cout << endl;
    }
}
void printArray(int* array) {
    cout << endl;
    cout << array[0] << ": " << endl;;
    for (int i = 1; i < array[0]; i++) cout << array[i] << " ";
}
int main()
{
    setlocale(LC_ALL, "ru");
    srand(time(0));
    int N, D = 10;
    cout << "Введите N:";
    cin >> N;
    int** matrix = getRandMatrix(N);
    int* array = getArray_A(matrix);
    printMatrix(matrix);
    printArray(array);
    return 0;
}