#include <iostream>
#include <ctime>
using namespace std;

int** genRandMatrix(int size, int maxValue) 
{
	int i;
	int** matrix = new int* [size];
	for (i = 1; i <= size;i++) {
		int r = rand() % 10 + 1;
		*matrix[i] = r;
		matrix[i][1] = r;
		for (int j = 2; j < matrix[i][1];j++) {
			matrix[i][j] = rand() % maxValue + 1;
		}
	}
	matrix[1][1] = i;
	return matrix;
}
void print(int** matrix) {
	for (int i = 1; i < matrix[1][1];i++) {
		cout << matrix[i][0] << ": ";
		for (int j = 1; j < matrix[i][0];j++) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
	delete matrix;
}

int main() {
	srand(time(0));
	int size = 10;
	//int size = rand() % 10;
	int maxValue = 100;
	int** matrix = genRandMatrix(size, maxValue);
	print (matrix);}