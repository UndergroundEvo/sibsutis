/**************************************
 * Encoding:  Cyrillic (CP 866)       *
 * Name:      "Построение АВЛ-дерева" *
 * Authors:   ИП-111 Корнилов Андрей, *
 *            ИП-111 Попов Мирон.     *
 **************************************/

#include <iostream>
#include <iomanip>
#include <math.h>
#include <time.h>

using namespace std;

const int N = 100;

struct Vertex
{
    int Data;
    int Balance;
    Vertex *Left;
    Vertex *Right;
};

Vertex *rootAVL, *rootSDP;

bool Growth;

void LLrotate(Vertex *&p);
void LRrotate(Vertex *&p);
void RRrotate(Vertex *&p);
void RLrotate(Vertex *&p);

Vertex *buildAVL(int D, Vertex *&p);
Vertex *buildSDP(int D, Vertex *&p);

void bypassLeftRight(Vertex *p);

int Size(Vertex *p);
int checkSum(Vertex *p);
int Height(Vertex *p);
int avgHeight(int H, Vertex *p);

int main()
{
    srand(time(NULL));

    int Arr[N];
    int Flag = 0, Temp;

    int sizeAVL, sumAVL, heightAVL;
    int sizeSDP, sumSDP, heightSDP;

    float avgheightAVL, avgheightSDP;

    for (int i = 0; i <= N;)
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

    rootAVL = (struct Vertex *)malloc(sizeof(struct Vertex));
    rootAVL = NULL;
    rootSDP = (struct Vertex *)malloc(sizeof(struct Vertex));
    rootSDP = NULL;

    for (int j = 0; j < N; j++)
    {
        buildSDP(Arr[j], rootSDP);
    }

    for (int j = 0; j < N; j++)
    {
        buildAVL(Arr[j], rootAVL);
    }

    cout << "\n\nАВЛ:\n"
         << endl;
    bypassLeftRight(rootAVL);

    sizeAVL = Size(rootAVL);
    sumAVL = checkSum(rootAVL);
    heightAVL = Height(rootAVL);
    avgheightAVL = avgHeight(1, rootAVL) / float(sizeAVL);

    sizeSDP = Size(rootSDP);
    sumSDP = checkSum(rootSDP);
    heightSDP = Height(rootSDP);
    avgheightSDP = avgHeight(1, rootSDP) / float(sizeSDP);

  cout << "\n\n"
       << "\t+-------+--------+--------------+--------+--------------+\n"
       << "\t| n=100 | Размер | Контр. сумма | Высота | Средн.высота |\n"
       << "\t+-------+--------+--------------+--------+--------------+\n"
       << "\t|  АВЛ  |  " << setw(4) << sizeAVL << "  |  " << setw(10) << sumAVL << "  |  " << setw(4) << heightAVL << "  |  " << setw(10) << avgheightAVL << "  |\n"
       << "\t+-------+--------+--------------+--------+--------------+\n"
       << "\t|  СДП  |  " << setw(4) << sizeSDP << "  |  " << setw(10) << sumSDP << "  |  " << setw(4) << heightSDP << "  |  " << setw(10) << avgheightSDP << "  |\n"
       << "\t+-------+--------+--------------+--------+--------------+\n"
       << endl;

    system("pause");
    return 0;
}

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

/**************** ПОСТРОЕНИЕ СДП (РЕКУРСИЯ) ****************/
Vertex *buildSDP(int D, Vertex *&p)
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
        buildSDP(D, p->Left);
    }
    else if (D >= p->Data)
    {
        buildSDP(D, p->Right);
    }
    else
    {
        cout << "Вершина существует в дереве!" << endl;
    }
}
/***********************************************************/

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