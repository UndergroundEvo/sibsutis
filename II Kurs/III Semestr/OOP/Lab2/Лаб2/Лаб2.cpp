#include <iostream>
#include <iomanip>
#include <stdlib.h>
using namespace std;
int menu(int variant) {
    cout << "Выберите порядок переписывания : " << endl;
    cout << "1.По правым диагоналям, начиная с правого верхнего элемента" << endl;
    cout << "2.По левым диагоналям, начиная с левого верхнего элемента" << endl;
    cout << "3.По спирали, начиная с центрального элемента" << endl;
    cout << "4.По спирали, начиная с левого верхнего элемента" << endl;
    cin >> variant;
    return variant;
}
int** getRandMatrix(int N) {
    int** matrix = new int* [N];
    for (int i=0;i<N;i++) {
        matrix[i] = new int[N];
        for (int j = 0; j < N; j++) {
            matrix[i][j] = rand() % 10 + 1;
        }
    }
    matrix[0][0] = N;
    return matrix;
} 
int* getArray_A(int** matrix) {
    int kolvo = 1, i = 0, j = 0;
    int N = matrix[0][0];
    int* array = new int[N * N + 1];
    // В правом верхнем углу мы можем сначала думать о столбцах от n-1 до 0
    for (int k = N - 1; k >= 0; k--) {
        // Цикл каждого столбца, индекс строки i увеличится, а индекс столбца j увеличится
        for (i = 0, j = k; i <= N - 1 - k && j <= N - 1; i++, j++) {
            array[kolvo] = matrix[i][j];
            kolvo++;
        }
    }
    // От 1 до n-1 строк
    for (int k = 1; k <= N - 1; k++) {
        // Цикл каждого столбца, индекс строки i увеличится, а индекс столбца j увеличится
        for (i = k, j = 0; i <= N - 1 && j <= N - 1 - k; i++, j++,kolvo++) {
            
            array[kolvo] = matrix[i][j];
        }
    }
    array[0] = kolvo;
    return array;
}
int* getArray_B(int** matrix) {
    int N = matrix[0][0];
	int kolvo = 1, i = 0, j = 0;
    int* array = new int[N * N + 1];
    // В правом верхнем углу мы можем сначала думать о столбцах от n-1 до 0
    for (int k = N - 1; k >= 0; k--) {
        // Цикл каждого столбца, индекс строки i увеличится, а индекс столбца j увеличится
        for (i = 0, j = k; i <= N - 1 - k && j <= N - 1; i++, j++) {
            array[kolvo] = matrix[i][j];
            kolvo++;
        }
    }
    // От 1 до n-1 строк
    for (int k = 1; k <= N - 1; k++) {
        // Цикл каждого столбца, индекс строки i увеличится, а индекс столбца j увеличится
        for (i = k, j = 0; i <= N - 1 && j <= N - 1 - k; i++, j++, kolvo++) {

            array[kolvo] = matrix[i][j];
        }
    }
    array[0] = kolvo;
    return array;
}
int* getArray_C(int** matrix) {
    int N = matrix[0][0], kolvo = 1, i = 0, j = 0, i_point = 0, i_end = 0, j_point = 0, j_end = 0;
    int* array = new int[N * N + 1];
    while (kolvo <= N * N) {
        array[kolvo] = matrix[i][j];
        if (i == i_point && j < N - j_end - 1)
            ++j;
        else if (j == N - j_end - 1 && i < N - i_end - 1)
            ++i;
        else if (i == N - i_end - 1 && j > j_point)
            --j;
        else
            --i;
        if ((i == i_point + 1) && (j == j_point) && (j_point != N - j_end - 1)) {
            ++i_point;
            ++i_end;
            ++j_point;
            ++j_end;
        }
        kolvo++;
    }
    array[0] = kolvo;
    return array;
}
int* getArray_D(int** matrix) {
    int N = matrix[0][0], kolvo = N * N, i = 0, j = 0, i_point = 0, i_end = 0, j_point = 0, j_end = 0;
    int* array = new int[N * N + 1];
    while (kolvo >= 1) {
        array[kolvo] = matrix[i][j];
        if (i == i_point && j < N - j_end - 1)
            ++j;
        else if (j == N - j_end - 1 && i < N - i_end - 1)
            ++i;
        else if (i == N - i_end - 1 && j > j_point)
            --j;
        else
            --i;
        if ((i == i_point + 1) && (j == j_point) && (j_point != N - j_end - 1)) {
            ++i_point;
            ++i_end;
            ++j_point;
            ++j_end;
        }
        kolvo--;
    }
    array[0] = (N*N)+1;
    return array;
}
void printMatrix(int** matrix,int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << setw(5) << matrix[i][j] << " ";
        }
        cout << endl;
    }
}
void printArray(int* array) {
    cout << array[0] << ": ";
    for (int i = 1; i < array[0]; i++) cout << array[i] << " ";
    cout << endl;
    delete[] array;
}
int main()
{
    setlocale(LC_ALL, "ru");
    //srand(time(0));
    int variant,N, D = 10;
    cout << "Введите N:";
    cin >> N;
    int** matrix = getRandMatrix(N);
    printMatrix(matrix, N);
    cout << "A)По правым диагоналям, начиная с правого верхнего элемента"<<endl;
    int* array = getArray_A(matrix);
    printArray(array);
    cout << "Б)По левым диагоналям, начиная с левого верхнего элемента" << endl;
    array = getArray_B(matrix);
    printArray(array);
    cout << "В)По спирали, начиная с центрального элемента" << endl;
    array = getArray_C(matrix);
    printArray(array);
    cout << "Г)По спирали, начиная с левого верхнего элемента" << endl;
    array = getArray_D(matrix);
    printArray(array);
    return 0;
}
