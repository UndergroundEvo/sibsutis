#include <iostream>
#include <ctime>
#include <stdlib.h>
using namespace std;

int** genRandMatrix(int size, int maxValue) {
	int** matrix = new int* [size];
	for (int i = 0; i < size; i++) {
		int r = rand() % 10 + 1;
		matrix[i] = new int[r];
		matrix[i][0] = r;
		for (int j = 1; j <= matrix[i][0]; j++) {
			matrix[i][j] = rand() % maxValue + 1;
		}
	}
	matrix[0][0] = size;
	return matrix;
}

void print(int** matrix) {
	cout<<matrix[0][0]<<endl;
	for (int i = 0; i < matrix[0][0]; i++) {
		cout << matrix[i][0] << ": ";
		for (int j = 1; j <= matrix[i][0]; j++) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
	delete matrix;
}

int main() {
	srand(time(0));
	int size = rand() % 10;
	int maxValue = 100;
	int** matrix = genRandMatrix(size, maxValue);
	print(matrix);
}
