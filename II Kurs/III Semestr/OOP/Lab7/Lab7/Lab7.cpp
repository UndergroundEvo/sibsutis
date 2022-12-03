#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <stack>
using namespace std;
static int i = 0, j = 0, i_point = 0, i_end = 0, j_point = 0, j_end = 0;
class list {
protected:
    int num;
    int** matrix;
public:
    //list(int N) : matrix{0}{}
    list() : matrix{get_rand_matrix()} {}
    //list(int N) :matrix{get_matrix(N)} {}
    ~list(){}
    int** get_matrix(int N) {
        try {
            int** matrix = new int* [N];
            for (int i = 0;i < N;i++) {
                matrix[i] = new int[N];
                for (int j = 0; j < N; j++) {
                    cout << "Введите число от 0 до 100" << endl
                        << "Число [" << i << "][" << j << "]" << endl;
                    cin >> num;
                    if (num > 100) throw num;
                    matrix[i][j] = num;
                }
            }
        }
        catch (int num) {
            cout << "Число не входит в диапазон от 0 до 100" << endl;
        }
        return matrix;
    }
    int** get_rand_matrix() {
        int N = 100;
        int** matrix = new int* [N];
        for (int i = 0;i < N;i++) {
            matrix[i] = new int[N];
            for (int j = 0; j < N; j++) {
                matrix[i][j] = rand() % 100 + 1;
            }
        }
        return matrix;
    }
    void printMatrix(int N) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cout << setw(5) << matrix[i][j] << " ";
            }
            cout << endl;
        }
    }
};
class steck:public list {
protected:
    stack <int> almostmatrix;
public:
    ~steck(){}
};
class queue :public steck {
protected:
public:
    ~queue(){}
    stack <int> getArray_A(int N) {
            // В правом верхнем углу мы можем сначала думать о столбцах от n-1 до 0
            for (int k = N - 1; k >= 0; k--) {
                // Цикл каждого столбца, индекс строки i увеличится, а индекс столбца j увеличится
                for (i = 0, j = k; i <= N - 1 - k && j <= N - 1; i++, j++) {
                    almostmatrix.push(list::matrix[i][j]);
                }
            }
            // От 1 до n-1 строк
            for (int k = 1; k <= N - 1; k++) {
                // Цикл каждого столбца, индекс строки i увеличится, а индекс столбца j увеличится
                for (i = k, j = 0; i <= N - 1 && j <= N - 1 - k; i++, j++) {
        
                    almostmatrix.push(list::matrix[i][j]);
                }
            }
            return almostmatrix;
    }
    stack <int> getArray_B(int N) {
    // В правом верхнем углу мы можем сначала думать о столбцах от n-1 до 0
    for (int k = N - 1; k >= 0; k--) {
        // Цикл каждого столбца, индекс строки i увеличится, а индекс столбца j увеличится
        for (i = 0, j = k; i <= N - 1 - k && j <= N - 1; i++, j++) {
            almostmatrix.push(matrix[i][j]);
        }
    }
    // От 1 до n-1 строк
    for (int k = 1; k <= N - 1; k++) {
        // Цикл каждого столбца, индекс строки i увеличится, а индекс столбца j увеличится
        for (i = k, j = 0; i <= N - 1 && j <= N - 1 - k; i++, j++) {
            almostmatrix.push(matrix[i][j]);
        }
    }
    return almostmatrix;
}
    stack <int> getArray_C(int N) {
        int k = 1;
        int* array = new int[N * N + 1];
        while (k <= N * N) {
            almostmatrix.push(matrix[i][j]);
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
        k++;
    }
    return almostmatrix;
}
    stack <int> getArray_D(int N) {
    int kolvo = N * N;
    while (kolvo >= 1) {
        almostmatrix.push(matrix[i][j]);
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
    return almostmatrix;
}
    void print_stack(int N) {
        for (int i = 0; i < N*N; i++) {
                cout << setw(5) << almostmatrix.top() << " ";
                almostmatrix.pop();
        }
    cout << endl;
    }
};
int matrix_size() {
    int N;
    cout << "Введите размерность матрицы:" << endl;
    cin >> N;
    return N;
}
int matrix_mode() {
    int mode;
    cout << "Выбор ввода чисел в матрицу:" << endl
        << "1) Рандомные числа" << endl
        << "2) Ввести с клавиатуры" << endl;
    cin >> mode;
    return mode;
}
int menu() {
    int variant;
    cout << "Выберите порядок переписывания : " << endl;
    cout << "1.По правым диагоналям, начиная с правого верхнего элемента" << endl;
    cout << "2.По левым диагоналям, начиная с левого верхнего элемента" << endl;
    cout << "3.По спирали, начиная с центрального элемента" << endl;
    cout << "4.По спирали, начиная с левого верхнего элемента" << endl;
    cin >> variant;
    return variant;
}
int main() {
    setlocale(LC_ALL, "ru");
    srand(time(0));
    //int mode = matrix_mode();
    int N = matrix_size();
    //list(N);
    queue almostmatrix;
    almostmatrix.get_rand_matrix();
    //switch (mode) {
    //case (1):
    //    //list;
    //    almostmatrix.get_rand_matrix();
    //    break;
    //default:
    //    //list(N);
    //    almostmatrix.get_matrix(N);
    //    break;
    //}
    almostmatrix.printMatrix(N);
    int variant = menu();
    switch (variant) {
    default:
        almostmatrix.getArray_A(N);
    break;
    case (2):
        almostmatrix.getArray_B(N);
    break;
    case (3):
        almostmatrix.getArray_C(N);
        break;
    case (4):
        almostmatrix.getArray_D(N);
        break;
    }
    almostmatrix.print_stack(N);
    return 0;
}
