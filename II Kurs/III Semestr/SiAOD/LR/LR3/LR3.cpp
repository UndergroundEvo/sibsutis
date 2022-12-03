/********************************************************
 * Encoding:  Cyrillic (Windows 1251)                         *
 * Name:      "Удаление Случайного Дерева Поиска (СДП)" *
 * Authors:   ИП-111 Корнилов Андрей,                   *
 *            ИП-111 Попов Мирон.                       *
 ********************************************************/

#include <iostream>
#include <iomanip>
#include <math.h>

using namespace std;

const int N = 10;

struct Vertex
{
    int Data;
    Vertex *Left;
    Vertex *Right;
};

Vertex *rootSDP;

Vertex *buildSDP(int D, Vertex *Root);
Vertex *deleteSDP(int D, Vertex *Root);

void bypassLeftRight(Vertex *p);

int main()
{
    setlocale(LC_ALL, "Russian");

    int Arr[N];

    for (int i = 1; i <= N; i++)
    {
        cout << "\nВведите " << i << " число:\t";
        cin >> Arr[i];
    }

    rootSDP = (struct Vertex *)malloc(sizeof(struct Vertex));

    for (int j = 1; j <= N; j++)
        buildSDP(Arr[j], rootSDP);

    cout << "\n\nСДП (ДВОЙНАЯ КОСВЕННОСТЬ):\n"
         << endl;
    bypassLeftRight(rootSDP);

    for (int l = 1; l <= N; l++)
    {
        cout << "\n\nУДАЛЕНИЕ " << l << " ВЕРШИНЫ"
             << endl;

        deleteSDP(Arr[l], rootSDP);

        cout << "\n\tПОСЛЕ УДАЛЕНИЯ:\n\t";
        bypassLeftRight(rootSDP);
    }

    system("pause");
    return 0;
}

/************* ПОСТРОЕНИЕ СДП (ДВОЙНАЯ КОСВЕННОСТЬ) *************/
Vertex *buildSDP(int D, Vertex *Root)
{
    Vertex **p;

    p = &Root;
    while (*p != NULL)
    {
        if (D < (*p)->Data)
            p = &((*p)->Left);
        else if (D >= (*p)->Data)
            p = &((*p)->Right);
        else
        {
            cout << "Данные с ключом уже есть в дереве!" << endl;
            break;
        }
    }
    if (*p == NULL)
    {
        *p = (struct Vertex *)malloc(sizeof(struct Vertex));
        (*p)->Data = D;
        (*p)->Left = NULL;
        (*p)->Right = NULL;
    }
    return Root;
}
/****************************************************************/

/************************ УДАЛЕНИЕ ИЗ СДП ************************/
Vertex *deleteSDP(int D, Vertex *Root)
{
    Vertex **p;
    Vertex *q, *s, *r;

    p = &Root;

    while (*p != NULL)
    {
        if ((*p)->Data < D)
            p = &((*p)->Right);
        else if ((*p)->Data > D)
            p = &((*p)->Left);
        else
            cout << "Данные с ключом уже есть в дереве!" << endl;
        break;
    }

    if (*p != NULL)
    {
        q = *p;

        if (q->Left == NULL)
            *p = q->Right;
        else if (q->Right == NULL)
            *p = q->Left;
        else
        {
            r = q->Left;
            s = q;

            if (r->Right == NULL)
            {
                r->Right = q->Right;
                *p = r;
            }
            else
            {
                while (r->Right != NULL)
                {
                    s = r;
                    r = r->Right;
                }
                s->Right = r->Left;
                r->Left = q->Left;
                r->Right = q->Right;
                *p = r;
            }
        }
        free(q);
    }
    return Root;
}
/*****************************************************************/

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