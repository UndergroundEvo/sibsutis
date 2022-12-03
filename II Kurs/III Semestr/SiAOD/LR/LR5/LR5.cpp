/**************************************
 * Encoding:  Cyrillic (Windows 1251) *
 * Name:      "Удаление АВЛ-дерева"   *
 * Authors:   ИП-111 Корнилов Андрей, *
 *            ИП-111 Попов Мирон.     *
 **************************************/

#include <iostream>
#include <iomanip>
#include <math.h>

using namespace std;

const int N = 10;

struct Vertex
{
    int Data;
    int Balance;
    Vertex *Left;
    Vertex *Right;
};

Vertex *rootAVL;

bool Growth, Decrease = false;

void LL1rotate(Vertex *&p);
void LRrotate(Vertex *&p);
void RR1rotate(Vertex *&p);
void RLrotate(Vertex *&p);

Vertex *buildAVL(int D, Vertex *&p);

void BL(Vertex *&p);
void BR(Vertex *&p);
void del(Vertex *&q, Vertex *&r);

Vertex *deleteAVL(int X, Vertex *&p);

void bypassLeftRight(Vertex *p);

int main()
{
    setlocale(LC_ALL, "Russian");

    int Arr[N];

    for (int i = 0; i < N; i++)
    {
        cout << "\nВведите " << i + 1 << " число:\t";
        cin >> Arr[i];
    }

    rootAVL = (struct Vertex *)malloc(sizeof(struct Vertex));
    rootAVL = NULL;

    for (int j = 0; j < N; j++)
        buildAVL(Arr[j], rootAVL);

    cout << "\n\nАВЛ:\n"
         << endl;
    bypassLeftRight(rootAVL);

    for (int l = 0; l < N; l++)
    {
        cout << "\n\nУДАЛЕНИЕ " << l + 1 << " ВЕРШИНЫ"
             << endl;

        deleteAVL(Arr[l], rootAVL);

        cout << "\n\tПОСЛЕ УДАЛЕНИЯ:\n\t";
        bypassLeftRight(rootAVL);
    }

    system("pause");
    return 0;
}

/********** LL1 - ПОВОРОТ **********/
void LL1rotate(Vertex *&p)
{
    Vertex *q;

    q = p->Left;

    if (q->Balance == 0)
    {
        p->Balance = -1;
        q->Balance = 1;
        Decrease = false;
    }
    else
    {
        p->Balance = q->Balance = 0;
    }

    p->Left = q->Right;
    q->Right = p;
    p = q;
}
/***********************************/

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

/********** RR1 - ПОВОРОТ **********/
void RR1rotate(Vertex *&p)
{
    Vertex *q;

    q = p->Right;

    if (q->Balance == 0)
    {
        p->Balance = 1;
        q->Balance = -1;
        Decrease = false;
    }
    else
    {
        p->Balance = q->Balance = 0;
    }

    p->Right = q->Left;
    q->Left = p;
    p = q;
}
/***********************************/

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
                    LL1rotate(p);
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
                    RR1rotate(p);
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

/** БАЛАНСИРОВКА ЛЕВОГО ПОДДЕРЕВА **/
void BL(Vertex *&p)
{
    if (p->Balance == -1)
    {
        p->Balance = 0;
    }
    else if (p->Balance == 0)
    {
        p->Balance = 1;
        Decrease = false;
    }
    else if (p->Balance == 1)
    {
        if (p->Right->Balance >= 0)
        {
            RR1rotate(p);
        }
        else
        {
            RLrotate(p);
        }
    }
}
/***********************************/

/** БАЛАНСИРОВКА ПРАВОГО ПОДДЕРЕВА **/
void BR(Vertex *&p)
{
    if (p->Balance == 1)
    {
        p->Balance = 0;
    }
    else if (p->Balance == 0)
    {
        p->Balance = -1;
        Decrease = false;
    }
    else if (p->Balance == -1)
    {
        if (p->Left->Balance <= 0)
        {
            LL1rotate(p);
        }
        else
        {
            LRrotate(p);
        }
    }
}
/************************************/

/** УДАЛЕНИЕ ВЕРШИНЫ, ИМЕЮЩУЮ ДВА ПОДДЕРЕВА **/
void del(Vertex *&q, Vertex *&r)
{
    if (r->Right != NULL)
    {
        del(q, r->Right);
        if (Decrease == true)
        {
            BR(r);
        }
    }
    else
    {
        q->Data = r->Data;
        q = r;
        r = r->Left;
        Decrease = true;
    }
}
/*********************************************/

/************* УДАЛЕНИЕ ДЕРЕВА АВЛ ************/
Vertex *deleteAVL(int X, Vertex *&p)
{
    Vertex *q, *r;

    if (p == NULL)
    {
        cout << "Ключа в дерееве нет!" << endl;
    }
    else if (p->Data > X)
    {
        deleteAVL(X, p->Left);
        if (Decrease == true)
        {
            BL(p);
        }
    }
    else if (p->Data < X)
    {
        deleteAVL(X, p->Right);
        if (Decrease == true)
        {
            BR(p);
        }
    }
    else
    {
        q = p;
        if (q->Right == NULL)
        {
            p = q->Left;
            Decrease = true;
        }
        else if (q->Left == NULL)
        {
            p = q->Right;
            Decrease = true;
        }
        else
        {
            r = q;
            del(q, r->Left);
            if (Decrease == true)
            {
                BL(p);
            }
        }
        free(q);
    }
    return p;
}
/**********************************************/

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