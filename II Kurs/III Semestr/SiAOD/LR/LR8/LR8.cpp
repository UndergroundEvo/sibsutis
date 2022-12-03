/***************************************************************
 * Encoding:  Cyrillic (CP 866)                                *
 * Name:      "Построение Дерева Оптимального Поиска (ДОП)     *
 *             Точным и Приближенными (A1 и A2) алгоритмами"   *
 * Authors:   ИП-111 Корнилов Андрей,                          *
 *            ИП-111 Попов Мирон.                              *
 ***************************************************************/

#include <iostream>
#include <iomanip>
#include <math.h>
#include <time.h>

using namespace std;

const int N = 100;

int AW[N + 1][N + 1] = {0};
int AP[N + 1][N + 1] = {0};
int AR[N + 1][N + 1] = {0};

struct Vertex
{
    int Data;
    int Weight;
    Vertex *Left;
    Vertex *Right;
};

Vertex *rootDOP;
Vertex *rootDOP_A1;
Vertex *rootDOP_A2;

struct V
{
    bool use;
    int data;
    int weight;
};

void buildSDP_Recursion(int D, int W, Vertex *&p);

void buildDOP(int L, int R, V *Arr, Vertex *&Root);

void A1(V *Arr, Vertex *&Root);
void A2(int L, int R, V *Arr, Vertex *&Root);

void calculateAW(V *Arr)
{
    for (int i = 0; i <= N; i++)
    {
        for (int j = i + 1; j <= N; j++)
        {
            AW[i][j] = AW[i][j - 1] + Arr[j].weight;
        }
    }
}
void calculateAP_and_AR()
{
    int i, j, m, min, k, h;
    for (i = 0; i <= N - 1; i++)
    {
        int j = i + 1;
        AP[i][j] = AW[i][j];
        AR[i][j] = j;
    }

    for (h = 2; h <= N; h++)
    {
        for (i = 0; i <= N - h; i++)
        {
            j = i + h;
            m = AR[i][j - 1];
            min = AP[i][m - 1] + AP[m][j];
            for (k = m + 1; k <= AR[i + 1][j]; k++)
            {
                int x = AP[i][k - 1] + AP[k][j];
                if (x < min)
                {
                    m = k;
                    min = x;
                }
            }
            AP[i][j] = min + AW[i][j];
            AR[i][j] = m;
        }
    }
}

float DOP_sumWeight(Vertex *Root);
float DOP_sumLenght(int L, Vertex *Root);
float DOP_avgHeight(Vertex *Root);

void bypassLeftRight(Vertex *p);

int Size(Vertex *p);
int checkSum(Vertex *p);
// int Height(Vertex *p);
// int avgHeight(Vertex *p, int H);

int main()
{
    srand(time(NULL));

    V Arr[N + 1];

    Arr[0].data = 0;
    Arr[0].weight = 0;

    for (int i = 1; i <= N; i++)
    {
        Arr[i].data = i;
        Arr[i].weight = rand() % 100 + 1;
    }

    calculateAW(Arr);
    calculateAP_and_AR();
    
    // cout << "\n\nВЫВОД AR 10x10: "
    //      << endl;
    // for (int i = 0; i <= 10; i++)
    // {
    //     cout << endl;
    //     for (int j = 0; j <= 10; j++)
    //         cout << setw(2) << AR[i][j] << "\t";
    // }

    cout << "\n\nПОСТРОЕНИЕ ДОП (ТОЧНЫЙ АЛГОРИТМ): \n"
         << endl;
    buildDOP(0, N, Arr, rootDOP);
    bypassLeftRight(rootDOP);

    cout << "\n\nПОСТРОЕНИЕ ДОП (ПРИБЛИЖЕННЫЙ АЛГОРИТМ A1): \n"
         << endl;
    A1(Arr, rootDOP_A1);
    bypassLeftRight(rootDOP_A1);

    cout << "\n\nПОСТРОЕНИЕ ДОП (ПРИБЛИЖЕННЫЙ АЛГОРИТМ A2): \n"
         << endl;
    A2(1, N, Arr, rootDOP_A2);
    bypassLeftRight(rootDOP_A2);

    cout << "\n\n"
         << "\t+---------------+--------+--------------+------------------+\n"
         << "\t|     n=100     | Размер | Контр. сумма | Средневзвешенная |\n"
         << "\t|               |        |              |      высота      |\n"
         << "\t+---------------+--------+--------------+------------------+\n"
         << "\t|  ДОП (Точный) |  " << setw(4) << Size(rootDOP) << "  |  " << setw(10) << checkSum(rootDOP) << "  |  " << setw(14) << DOP_avgHeight(rootDOP) << "  |\n"
         << "\t+---------------+--------+--------------+------------------+\n"
         << "\t|  ДОП (A1)     |  " << setw(4) << Size(rootDOP_A1) << "  |  " << setw(10) << checkSum(rootDOP_A1) << "  |  " << setw(14) << DOP_avgHeight(rootDOP_A1) << "  |\n"
         << "\t+---------------+--------+--------------+------------------+\n"
         << "\t|  ДОП (A2)     |  " << setw(4) << Size(rootDOP_A2) << "  |  " << setw(10) << checkSum(rootDOP_A2) << "  |  " << setw(14) << DOP_avgHeight(rootDOP_A2) << "  |\n"
         << "\t+---------------+--------+--------------+------------------+\n"
         << endl;

    system("pause");
    return 0;
}

/*********** ПОСТРОЕНИЕ СДП РЕКУРСИВНО ***********/
void buildSDP_Recursion(int D, int W, Vertex *&p)
{
    if (p == NULL)
    {
        p = new Vertex;
        p->Data = D;
        p->Weight = W;
        p->Left = NULL;
        p->Right = NULL;
    }
    else if (D < p->Data)
    {
        buildSDP_Recursion(D, W, p->Left);
    }
    else if (D >= p->Data)
    {
        buildSDP_Recursion(D, W, p->Right);
    }
}
/*************************************************/

/************* ПОСТРОЕНИЕ ДОП (ТОЧНЫЙ АЛГОРИТМ) *************/
void buildDOP(int L, int R, V *Arr, Vertex *&Root)
{
    int k = 0;
    if (L < R)
    {
        k = AR[L][R];
        buildSDP_Recursion(Arr[k].data, Arr[k].weight, Root);
        buildDOP(L, k - 1, Arr, Root);
        buildDOP(k, R, Arr, Root);
    }
}
/************************************************************/

/******************* ПОСТРОЕНИЕ ДОП АЛГОРИТМОМ A1 *******************/
void A1(V *Arr, Vertex *&Root)
{
    Root = NULL;
    for (int i = 1; i <= N; i++)
        Arr[i].use = false;
    for (int i = 1; i <= N; i++)
    {
        int max = 0;
        int index = 0;
        for (int j = 1; j <= N; j++)
        {
            if (Arr[j].weight >= max && Arr[j].use == false)
            {
                max = Arr[j].weight;
                index = j;
            }
        }
        Arr[index].use = true;
        buildSDP_Recursion(Arr[index].data, Arr[index].weight, Root);
    }
}
/********************************************************************/

/******************* ПОСТРОЕНИЕ ДОП АЛГОРИТМОМ A2 *******************/
void A2(int L, int R, V *Arr, Vertex *&Root)
{
    int Wes = 0, Sum = 0;
    int i;
    if (L <= R)
    {
        for (i = L; i <= R; i++)
            Wes += Arr[i].weight;
        for (i = L; i <= R - 1; i++)
        {
            if (Sum < (Wes / 2) && (Sum + Arr[i].weight) > (Wes / 2))
                break;
            Sum += Arr[i].weight;
        }
        buildSDP_Recursion(Arr[i].data, Arr[i].weight, Root);
        A2(L, i - 1, Arr, Root);
        A2(i + 1, R, Arr, Root);
    }
}
/********************************************************************/

/************************ ВЫЧИСЛЕНИЕ СУММЫ ВЕСОВ ВЕРШИН ДОП************************/
float DOP_sumWeight(Vertex *Root)
{
    int Sum;
    if (Root == NULL)
        Sum = 0;
    else
        Sum = Root->Weight + DOP_sumWeight(Root->Left) + DOP_sumWeight(Root->Right);
    return Sum;
}
/***********************************************************************************/

/******************************* ВЫЧИСЛЕНИЕ СУММЫ ДЛИН ВЕСОВ ВЕРШИН ДОП *******************************/
float DOP_sumLenght(int L, Vertex *Root)
{
    int Sum;
    if (Root == NULL)
        Sum = 0;
    else
        Sum = Root->Weight * L + DOP_sumLenght(L + 1, Root->Left) + DOP_sumLenght(L + 1, Root->Right);
    return Sum;
}
/******************************************************************************************************/

/********** ВЫЧИСЛЕНИЕ СРЕДНЕВЗВЕШЕННОЙ ВЫСОТЫ **********/
float DOP_avgHeight(Vertex *Root)
{
    float avgH;
    avgH = DOP_sumLenght(1, Root) / DOP_sumWeight(Root);
    return avgH;
}
/********************************************************/

/******* ОБХОД ДЕРЕВА СЛЕВА НАПРАВО *******/
void bypassLeftRight(Vertex *p)
{
    if (p != NULL)
    {
        bypassLeftRight(p->Left);
        cout << setw(3) << p->Data << " (" 
             << setw(3) << p->Weight << ")"
             << "   ";
        bypassLeftRight(p->Right);
    }
}
/******************************************/

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