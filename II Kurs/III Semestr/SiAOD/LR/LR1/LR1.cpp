/***************************************************************
 * Encoding:  Cyrillic (CP 866)                                *
 * Name:      "Идеально Сбалансированное Дерево Поиска (ИСДП)" *
 * Authors:   ИП-111 Корнилов Андрей,                          *
 *            ИП-111 Попов Мирон.                              *
 ***************************************************************/

#include <iostream>
#include <iomanip>
#include <math.h>
#include <time.h>

using namespace std;

const int N = 100;

struct Vertex
{
  int Data;
  Vertex *Left;
  Vertex *Right;
};

Vertex *rootISDP;

Vertex *buildISDP(int L, int R, int *Arr);
void insertSort(int A[], int n);

void bypassLeftRight(Vertex *p);

int Size(Vertex *p);
int checkSum(Vertex *p);
int Height(Vertex *p);
int avgHeight(int H, Vertex *p);

int main()
{
  srand(time(NULL));

  int Arr[N];
  int Temp, Flag;

  for (int i = 1; i <= N;)
  {
    Flag = 0;
    Temp = 1 + rand() % 100;

    if (i == 1)
    {
      Arr[i] = Temp;
      i++;
    }

    else
    {
      for (int j = 1; j < i; j++)
      {
        if (Temp != Arr[j])
          Flag = 0;
        else if (Temp == Arr[j])
        {
          Flag = 1;
          break;
        }
      }

      if (Flag == 1)
        continue;
      else if (Flag == 0)
      {
        Arr[i] = Temp;
        i++;
      }
    }
  }

  insertSort(Arr, N);

  int L = Arr[1];
  int R = Arr[N];

  rootISDP = (struct Vertex *)malloc(sizeof(struct Vertex));
  rootISDP = buildISDP(L, R, Arr);

  cout << "ИСДП:\n"
       << endl;
  bypassLeftRight(rootISDP);

  int size = Size(rootISDP);
  cout << "\n\nРазмер = " << size << endl;
  int sum = checkSum(rootISDP);
  cout << "Сумма = " << sum << endl;
  int h = Height(rootISDP);
  cout << "Высота = " << h << endl;
  float avg = avgHeight(1, rootISDP);
  cout << "Средняя высота = " << avg / float(size) << endl;

  system("pause");
  return 0;
}

/******************* ПОСТРОЕНИЕ ИСДП *******************/
Vertex *buildISDP(int L, int R, int *Arr)
{
  int m;
  Vertex *p;
  if (L > R)
    return NULL;
  else
  {
    m = ceil((L + R) / (float)2);
    p = (struct Vertex *)malloc(sizeof(struct Vertex));
    p->Data = Arr[m];
    p->Left = buildISDP(L, m - 1, Arr);
    p->Right = buildISDP(m + 1, R, Arr);
    return p;
  }
}
/*******************************************************/

/******** СОРТИРОВКА ВЕРШИН ********/
void insertSort(int A[], int n)
{
  int i, Temp, j;

  for (i = 2; i <= n; i++)
  {
    Temp = A[i];
    j = i - 1;
    while ((j > 0) && (Temp < A[j]))
    {
      A[j + 1] = A[j];
      j = j - 1;
    }
    A[j + 1] = Temp;
  }
}
/***********************************/

/**************** ОБХОД ДЕРЕВА СЛЕВА НАПРАВО ****************/
void bypassLeftRight(Vertex *p)
{
  if (p != NULL)
  {
    bypassLeftRight(p->Left);
    cout << setw(3) << p->Data << "   ";
    bypassLeftRight(p->Right);
  }
}
/************************************************************/

/*********** ВЫЧИСЛЕНИЕ РАЗМЕРА ДЕРЕВА ***********/
int Size(Vertex *p)
{
  int size;
  if (p == NULL)
    size = 0;
  else
    size = 1 + Size(p->Left) + Size(p->Right);
  return size;
}
/*************************************************/

/******************* ВЫЧИСЛЕНИЕ СУММЫ ДЕРЕВА *******************/
int checkSum(Vertex *p)
{
  int Sum = 0;
  if (p == NULL)
    Sum = 0;
  else
    Sum = p->Data + checkSum(p->Left) + checkSum(p->Right);
  return Sum;
}
/***************************************************************/

/*************** ВЫЧИСЛЕНИЕ ВЫСОТЫ ДЕРЕВА ***************/
int Height(Vertex *p)
{
  int H = 0;
  if (p == NULL)
    H = 0;
  else
    H = 1 + max(Height(p->Left), Height(p->Right));
  return H;
}
/********************************************************/

/******************** ВЫЧИСЛЕНИЕ СРЕДНЕЙ ВЫСОТЫ ДЕРЕВА ********************/
int avgHeight(int H, Vertex *p)
{
  int avgH;
  if (p == NULL)
    avgH = 0;
  else
    avgH = H + avgHeight(H + 1, p->Left) + avgHeight(H + 1, p->Right);
  return avgH;
}
/**************************************************************************/