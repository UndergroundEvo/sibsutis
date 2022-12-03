/**************************************
 * Encoding:  Cyrillic (CP 866)       *
 * Name:      "Построени ДБ-дерева"   *
 * Authors:   ИП-111 Корнилов Андрей, *
 *            ИП-111 Попов Мирон.     *
 **************************************/

#include <iostream>
#include <iomanip>
#include <math.h>
#include <time.h>

using namespace std;

const int sizeArr = 100;

struct Vertex
{
    int Data;
    int Balance;
    Vertex *Left;
    Vertex *Right;
};

Vertex *rootDBD, *rootAVL;

bool Growth, VR = false, HR = false;

Vertex *buildDBD(int D, Vertex *&p);

void LLrotate(Vertex *&p);
void LRrotate(Vertex *&p);
void RRrotate(Vertex *&p);
void RLrotate(Vertex *&p);

Vertex *buildAVL(int D, Vertex *&p);

void bypassLeftRight(Vertex *p);

int Size(Vertex *p);
int checkSum(Vertex *p);
int Height(Vertex *p);
int avgHeight(int H, Vertex *p);

int main()
{
    srand(time(NULL));

    int Arr[sizeArr];
    int Flag = 0, Temp;

    int sizeDBD, sumDBD, heightDBD;
    int sizeAVL, sumAVL, heightAVL;

    float avgHeightDBD, avgHeightAVL;

    for (int i = 0; i <= sizeArr;)
    {
        Flag = 0;
        Temp = 1 + rand() % 200;
        if (i == 1)
        {
            Arr[i] = Temp;
            i++;
        }
        else
        {
            for (int j = 0; j < i; j++)
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

    rootDBD = (struct Vertex *)malloc(sizeof(struct Vertex));
    rootDBD = NULL;
    rootAVL = (struct Vertex *)malloc(sizeof(struct Vertex));
    rootAVL = NULL;

    for (int j = 0; j < sizeArr; j++)
        buildDBD(Arr[j], rootDBD);

    for (int j = 0; j < sizeArr; j++)
        buildAVL(Arr[j], rootAVL);

    cout << "ДБД:\n"
         << endl;
    bypassLeftRight(rootAVL);

    sizeDBD = Size(rootDBD);
    sumDBD = checkSum(rootDBD);
    heightDBD = Height(rootDBD);
    avgHeightDBD = avgHeight(1, rootDBD) / float(sizeDBD);

    sizeAVL = Size(rootAVL);
    sumAVL = checkSum(rootAVL);
    heightAVL = Height(rootAVL);
    avgHeightAVL = avgHeight(1, rootAVL) / float(sizeAVL);

    cout << "\n\n"
         << "\t+-------+--------+--------------+--------+--------------+\n"
         << "\t| n=100 | Размер | Контр. сумма | Высота | Средн.высота |\n"
         << "\t+-------+--------+--------------+--------+--------------+\n"
         << "\t|  ДБД  |  " << setw(4) << sizeDBD << "  |  " << setw(10) << sumDBD << "  |  " << setw(4) << heightDBD << "  |  " << setw(10) << avgHeightDBD << "  |\n"
         << "\t+-------+--------+--------------+--------+--------------+\n"
         << "\t|  АВЛ  |  " << setw(4) << sizeAVL << "  |  " << setw(10) << sumAVL << "  |  " << setw(4) << heightAVL << "  |  " << setw(10) << avgHeightAVL << "  |\n"
         << "\t+-------+--------+--------------+--------+--------------+\n"
         << endl;

    system("pause");
    return 0;
}

/********** ДОБАВЛЕНИЕ В ДЕРЕВО ДБ **********/
Vertex *buildDBD(int D, Vertex *&p)
{
    Vertex *q;

    if (p == NULL)
    {
        p = new Vertex;
        p->Data = D;
        p->Left = p->Right = NULL;
        p->Balance = 0;
        VR = true;
    }
    else if (p->Data > D)
    {
        buildDBD(D, p->Left);
        if (VR == true)
        {
            if (p->Balance == 0)
            {
                q = p->Left;
                p->Left = q->Right;
                q->Right = p;
                p = q;
                q->Balance = 1;
                VR = false;
                HR = true;
            }
            else
            {
                p->Balance = 0;
                VR = true;
                HR = false;
            }
        }
        else
        {
            HR = false;
        }
    }
    else if (p->Data < D)
    {
        buildDBD(D, p->Right);
        if (VR == true)
        {
            p->Balance = 1;
            HR = true;
            VR = false;
        }
        else if (HR == true)
        {
            if (p->Balance == 1)
            {
                q = p->Right;
                p->Balance = q->Balance = 0;
                p->Right = q->Left;
                q->Left = p;
                p = q;
                VR = true;
                HR = false;
            }
            else
            {
                HR = false;
            }
        }
    }
    return p;
}
/********************************************/

/******** LL - ПОВОРОТ ********/
void LLrotate(Vertex *&p)
{
    Vertex *q;

    q = p->Left;
    q->Balance = p->Balance = 0;
    p->Left = q->Right;
    q->Right = p;
    p = q;
}
/******************************/

/******** LR - ПОВОРОТ ********/
void LRrotate(Vertex *&p)
{
    Vertex *q, *r;

    q = p->Left;
    r = q->Right;
    if (r->Balance < 0)
    {
        p->Balance = 1;
    }
    else
    {
        p->Balance = 0;
    }
    if (r->Balance > 0)
    {
        q->Balance = -1;
    }
    else
    {
        q->Balance = 0;
    }
    r->Balance = 0;
    q->Right = r->Left;
    p->Left = r->Right;
    r->Left = q;
    r->Right = p;
    p = r;
}
/******************************/

/******** RR - ПОВОРОТ ********/
void RRrotate(Vertex *&p)
{
    Vertex *q;

    q = p->Right;
    q->Balance = p->Balance = 0;
    p->Right = q->Left;
    q->Left = p;
    p = q;
}
/******************************/

/******** RL - ПОВОРОТ ********/
void RLrotate(Vertex *&p)
{
    Vertex *q, *r;

    q = p->Right;
    r = q->Left;
    if (r->Balance > 0)
    {
        p->Balance = -1;
    }
    else
    {
        p->Balance = 0;
    }
    if (r->Balance < 0)
    {
        q->Balance = 1;
    }
    else
    {
        q->Balance = 0;
    }
    r->Balance = 0;
    q->Left = r->Right;
    p->Right = r->Left;
    r->Left = p;
    r->Right = q;
    p = r;
}
/******************************/

/*************** ДОБАВЛЕНИЕ В ДЕРЕВО АВЛ ***************/
Vertex *buildAVL(int D, Vertex *&p)
{
    if (p == NULL)
    {
        p = new Vertex;
        p->Data = D;
        p->Left = p->Right = NULL;
        p->Balance = 0;
        Growth = true;
    }
    else if (p->Data > D)
    {
        buildAVL(D, p->Left);
        if (Growth == true)
        {
            if (p->Balance > 0)
            {
                p->Balance = 0;
                Growth = false;
            }
            else if (p->Balance == 0)
            {
                p->Balance = -1;
                Growth = true;
            }
            else
            {
                if (p->Left->Balance < 0)
                {
                    LLrotate(p);
                    Growth = false;
                }
                else
                {
                    LRrotate(p);
                    Growth = false;
                }
            }
        }
    }
    else if (p->Data < D)
    {
        buildAVL(D, p->Right);
        if (Growth == true)
        {
            if (p->Balance < 0)
            {
                p->Balance = 0;
                Growth = false;
            }
            else if (p->Balance == 0)
            {
                p->Balance = 1;
                Growth = true;
            }
            else
            {
                if (p->Right->Balance > 0)
                {
                    RRrotate(p);
                    Growth = false;
                }
                else
                {
                    RLrotate(p);
                    Growth = false;
                }
            }
        }
    }
    else
    {
        cout << "Вершина существует в дереве!" << endl;
    }
    return p;
}
/*******************************************************/

/******** ОБХОД ДЕРЕВА СЛЕВА НАПРАВО ********/
void bypassLeftRight(Vertex *p)
{
    if (p != NULL)
    {
        bypassLeftRight(p->Left);
        cout << setw(3) << p->Data << "   ";
        bypassLeftRight(p->Right);
    }
}
/********************************************/

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