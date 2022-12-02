#include <iostream>
#include <stdlib.h>
using namespace std;

int* genRandArray(int size, int maxValue) {
    int* arr = new int[size+1];
    arr[0] = size;
    for (int i = 1; i < arr[0];i++) arr[i]=rand()% maxValue + 1;
    return arr;
}

void print(int* arr) {
    cout << arr[0] << ": ";
    for (int i = 1; i < arr[0];i++) cout << arr[i] << " ";
}

int main(int argc, char* argv[])
{
    int size = rand() % 11;
    //int size = rand()%10;
    int maxValue = 100;
    int* arr = genRandArray(size, maxValue);
    print(arr);
    delete[] arr;
}
