/**********************************************
 * Encoding:  Cyrillic (CP 866)               *
 * Name:      "Случайное Дерево Поиска (СДП)" *
 * Authors:   ИП-111 Корнилов Андрей,         *
 *            ИП-111 Попов Мирон.             *
 **********************************************/

#include <iostream>
#include <iomanip>
#include <math.h>
#include <time.h>

using namespace std;

using namespace std;

const int N = 100;

struct Vertex
{
  int Data;
  Vertex *Left;
  Vertex *Right;
};

Vertex *rootISDP, *rootSDP_R, *rootSDP_DI;

Vertex *buildISDP(int L, int R, int *Arr);
Vertex *buildSDP_Recursion(int D, Vertex *&p);
Vertex *buildSDP_dobleIdirection(int *B, Vertex *Root);

void bypassLeftRight(Vertex *p);

int Size(Vertex *p);
int checkSum(Vertex *p);
int Height(Vertex *p);
int avgHeight(int H, Vertex *p);

int main()
{
  srand(time(NULL));

  int Arr_A[N], Arr_B[N];
  int Count = 0, Flag = 0, Temp;

  for (int i = 1; i <= N; i++)
    Arr_A[i] = i;

  for (int j = 1; j <= N; j++)
    Arr_B[j] = 1 + rand() % 200;

  int L = Arr_A[1];
  int R = Arr_A[N];

  rootISDP = (struct Vertex *)malloc(sizeof(struct Vertex));
  rootSDP_R = (struct Vertex *)malloc(sizeof(struct Vertex));
  rootSDP_R = NULL;
  rootSDP_DI = (struct Vertex *)malloc(sizeof(struct Vertex));
  rootSDP_DI = NULL;

  for (int i = 1; i <= N; i++)
    buildSDP_Recursion(Arr_B[i], rootSDP_R);

  rootSDP_DI = buildSDP_dobleIdirection(Arr_B, rootSDP_DI);

  rootISDP = buildISDP(L, R, Arr_A);

  int size_ISDP = Size(rootISDP);
  int sum_ISDP = checkSum(rootISDP);
  int height_ISDP = Height(rootISDP);
  int avgHight_ISDP = avgHeight(1, rootISDP) / float(size_ISDP);

  cout << "СДП (РЕКУРСИЯ):\n"
       << endl;
  bypassLeftRight(rootSDP_R);

  cout << "\n\nСДП (ДВОЙНАЯ КОСВЕННОСТЬ):\n"
       << endl;
  bypassLeftRight(rootSDP_DI);

  int size_SDP_R = Size(rootSDP_R);
  int sum_SDP_R = checkSum(rootSDP_R);
  int height_SDP_R = Height(rootSDP_R);
  float avgHight_SDP_R = avgHeight(1, rootSDP_R) / float(size_SDP_R);

  int size_SDP_DI = Size(rootSDP_DI);
  int sum_SDP_DI = checkSum(rootSDP_DI);
  int height_SDP_DI = Height(rootSDP_DI);
  float avgHight_SDP_DI = avgHeight(1, rootSDP_DI) / float(size_SDP_DI);

  cout << "\n\n"
       << "\t+-----------+--------+--------------+--------+--------------+\n"
       << "\t|   n=100   | Размер | Контр. сумма | Высота | Средн.высота |\n"
       << "\t+-----------+--------+--------------+--------+--------------+\n"
       << "\t| ИСДП      |  " << setw(4) << size_ISDP << "  |  " << setw(10) << sum_ISDP << "  |  " << setw(4) << height_ISDP << "  |  " << setw(10) << avgHight_ISDP << "  |\n"
       << "\t+-----------+--------+--------------+--------+--------------+\n"
       << "\t| СДП (Р)   |  " << setw(4) << size_SDP_R << "  |  " << setw(10) << sum_SDP_R << "  |  " << setw(4) << height_SDP_R << "  |  " << setw(10) << avgHight_SDP_R << "  |\n"
       << "\t+-----------+--------+--------------+--------+--------------+\n"
       << "\t| СДП (ДК)  |  " << setw(4) << size_SDP_DI << "  |  " << setw(10) << sum_SDP_DI << "  |  " << setw(4) << height_SDP_DI << "  |  " << setw(10) << avgHight_SDP_DI << "  |\n"
       << "\t+-----------+--------+--------------+--------+--------------+\n"
       << endl;

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

/************** ПОСТРОЕНИЕ СДП (РЕКУРСИЯ) **************/
Vertex *buildSDP_Recursion(int D, Vertex *&p)
{
  if (p == NULL)
  {
    p = (struct Vertex *)malloc(sizeof(struct Vertex));
    p->Data = D;
    p->Left = NULL;
    p->Right = NULL;
  }
  else if (D < p->Data)
  {
    buildSDP_Recursion(D, p->Left);
  }
  else if (D >= p->Data)
  {
    buildSDP_Recursion(D, p->Right);
  }
  else
  {
    cout << "Вершина существует в дереве!" << endl;
  }
}
/*******************************************************/

/********** ПОСТРОЕНИЕ СДП (ДВОЙНАЯ КОСВЕННОСТЬ) **********/
Vertex *buildSDP_dobleIdirection(int *B, Vertex *Root)
{
  int i;
  for (i = 1; i <= N; i++)
  {
    Vertex **p;
    p = &Root;
    while (*p != NULL)
    {
      if (B[i] < (*p)->Data)
        p = &((*p)->Left);
      else if (B[i] >= (*p)->Data)
        p = &((*p)->Right);
      else
      {
        cout << "Данные содержатся в дереве!" << endl;
        break;
      }
    }
    if (*p == NULL)
    {
      *p = (struct Vertex *)malloc(sizeof(struct Vertex));
      (*p)->Data = B[i];
      (*p)->Left = NULL;
      (*p)->Right = NULL;
    }
  }
  return Root;
}
/**********************************************************/

/****** ОБХОД ДЕРЕВА СЛЕВА НАПРАВО ******/
void bypassLeftRight(Vertex *p)
{
  if (p != NULL)
  {
    bypassLeftRight(p->Left);
    cout << setw(3) << p->Data << "   ";
    bypassLeftRight(p->Right);
  }
}
/****************************************/

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