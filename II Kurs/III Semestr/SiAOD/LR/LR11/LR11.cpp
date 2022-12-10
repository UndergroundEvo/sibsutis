/***************************************************
 * Encoding:  Cyrillic (CP 866)                    *
 * Name:      "Построение кодов Шеннона, Хаффмена, *
 *             Фано, Гилберта-Мура"                *
 * Authors:   ИП-111 Корнилов Андрей,              *
 *            ИП-111 Попов Мирон.                  *
 ***************************************************/

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

const int sizeChar = 20;

struct Code
{
    char key;
    float P;
    float Q;
    int L = 0;
    char *C;
};

bool Sorting(const pair<int, int> &A, const pair<int, int> &B)
{
    return (A.second > B.second);
}

/********** КОД ШЕННОНА **********/
void Shannon(int size, Code *Arr);
/*********************************/

/*************** КОД ХАФФМАНА ***************/
int Up(int n, float q, Code *Arr);
void Down(int size, int n, int j, Code *Arr);
void Huffman(int size, int n, Code *Arr);
/********************************************/

/**************** КОД ФАНО ****************/
int Med(int L, int R, Code *Arr);
void Fano(int L, int R, int k, Code *Arr);
/******************************************/

/********* КОД ГИЛБЕРТА-МУРА *********/
void GilbertMur(int size, Code *Arr);
/*************************************/

void printCode(int n, int count, Code *Arr, string Name);

int main()
{
    string fileName = "text.txt";

    vector<pair<char, int>> probability;
    vector<char> sourceFile;

    ifstream file(fileName, ios::binary);

    if (file.is_open())
    {
        while (!file.eof())
        {
            char ch;
            file.read((char *)&ch, sizeof(char));
            sourceFile.push_back(ch);
        }
    }

    for (int i = 0; i < sourceFile.size(); i++)
    {
        bool f = false;

        for (int j = 0; j < probability.size(); j++)
        {
            if (sourceFile[i] == probability[j].first)
            {
                f = true;
                probability[j].second++;
            }
        }
        if (!f)
        {
            probability.push_back(make_pair(sourceFile[i], 1));
        }
    }

    sort(probability.begin(), probability.end(), Sorting);

    const int n = (int)probability.size();
    int k = -1;

    Code *shannon = new Code[n];
    Code *huffman = new Code[n];
    Code *fano = new Code[n];
    Code *gilbertMur = new Code[n];

    for (int i = 0; i < probability.size(); i++)
    {
        shannon[i].key = probability[i].first;
        shannon[i].P = (double)probability[i].second / (double)sourceFile.size();
        shannon[i].C = new char[sizeChar];

        huffman[i].key = probability[i].first;
        huffman[i].P = (double)probability[i].second / (double)sourceFile.size();
        huffman[i].Q = (double)probability[i].second / (double)sourceFile.size();
        huffman[i].C = new char[sizeChar];

        fano[i].key = probability[i].first;
        fano[i].P = probability[i].second;
        fano[i].C = new char[sizeChar];

        gilbertMur[i].key = probability[i].first;
        gilbertMur[i].P = (double)probability[i].second / (double)sourceFile.size();
        gilbertMur[i].C = new char[sizeChar];
    }

    Shannon(n, shannon);
    cout << "\nКОД ШЕННОНА:" << endl;
    printCode(probability.size(), sourceFile.size(), shannon, "Shannon");

    Huffman(n, n - 1, huffman);
    cout << "\nКОД ХАФФМАНА:" << endl;
    printCode(probability.size(), sourceFile.size(), huffman, "Huffman");

    Fano(0, probability.size() - 1, k, fano);
    cout << "\nКОД ФАНО:" << endl;
    printCode(probability.size(), sourceFile.size(), fano, "Fano");

    GilbertMur(n, gilbertMur);
    cout << "\nКОД ГИЛБЕРТА-МУРА:" << endl;
    printCode(probability.size(), sourceFile.size(), gilbertMur, "GilbertMur");

    cout << "\n"
         << endl;

    double Entropy = 0;
    double avgLenght_Fano = 0;
    double avgLenght_Huffman = 0;
    double avgLenght_Shannon = 0;
    double avgLenght_GilbertMur = 0;

    for (int i = 0; i < probability.size(); i++)
    {
        Entropy -= (fano[i].P / sourceFile.size()) * log2((fano[i].P / sourceFile.size()));
        avgLenght_Shannon += shannon[i].L * shannon[i].P;
        avgLenght_Huffman += huffman[i].L * (huffman[i].Q);
        avgLenght_Fano += fano[i].L * (fano[i].P / sourceFile.size());
        avgLenght_GilbertMur += gilbertMur[i].L * gilbertMur[i].P;
    }
    cout << setw(15) << "Энтропия" << setw(49) << "Средняя длина кодового слова" << endl;
    cout << setw(19) << "исходного текста"
         << setw(14) << "Код Шеннона"
         << setw(15) << "Код Хаффмена"
         << setw(11) << "Код Фано"
         << setw(20) << "Код Гилберта-Мура"
         << endl;

    cout << setw(13) << round(Entropy * 1000) / 1000
         << setw(17) << round(avgLenght_Shannon * 1000) / 1000
         << setw(15) << round(avgLenght_Huffman * 1000) / 1000
         << setw(13) << round(avgLenght_Fano * 1000) / 1000
         << setw(15) << round(avgLenght_GilbertMur * 1000) / 1000
         << endl;

    system("pause");
    return 0;
}

void Shannon(int size, Code *Arr)
{
    Arr[0].Q = 0;
    Arr[0].L = -log2(Arr[0].P) + 1;

    for (int i = 1; i < size; i++)
    {
        Arr[i].Q = Arr[i - 1].Q + Arr[i - 1].P;
        Arr[i].L = -log2(Arr[i].P) + 1;
    }

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < Arr[i].L; j++)
        {
            Arr[i].Q = Arr[i].Q * 2;
            if (Arr[i].Q >= 1)
            {
                Arr[i].C[j] = '1';
                Arr[i].Q -= 1;
            }
            else
                Arr[i].C[j] = '0';
        }
    }
}

int Up(int n, float q, Code *Arr)
{
    int j = 0;

    for (int i = n - 1; i > 0; i--)
    {
        if (Arr[i - 1].P <= q)
            Arr[i].P = Arr[i - 1].P;
        else
        {
            j = i;
            break;
        }
    }

    Arr[j].P = q;
    return j;
}
void Down(int size, int n, int j, Code *Arr)
{
    char *S = new char[size];

    for (int i = 0; i < size; i++)
        S[i] = Arr[j].C[i];

    int L = Arr[j].L;

    for (int i = j; i <= n - 2; i++)
    {
        for (int k = 0; k < size; k++)
            Arr[i].C[k] = Arr[i + 1].C[k];

        Arr[i].L = Arr[i + 1].L;
    }

    for (int i = 0; i < size; i++)
    {
        Arr[n - 1].C[i] = S[i];
        Arr[n].C[i] = S[i];
    }

    Arr[n - 1].C[L] = '0';
    Arr[n].C[L] = '1';
    Arr[n - 1].L = L + 1;
    Arr[n].L = L + 1;
}
void Huffman(int size, int n, Code *Arr)
{
    float q;
    int j;
    if (n == 1)
    {
        Arr[0].C[0] = '0';
        Arr[0].L = 1;
        Arr[1].C[0] = '1';
        Arr[1].L = 1;
    }
    else
    {
        q = Arr[n - 1].P + Arr[n].P;
        j = Up(n, q, Arr);
        Huffman(size, n - 1, Arr);
        Down(size, n, j, Arr);
    }
}

int Med(int L, int R, Code *Arr)
{
    int SL = 0;

    for (int i = L; i <= R; i++)
        SL += Arr[i].P;

    int SR = Arr[R].P;
    int m = R;

    while (SL >= SR)
    {
        m--;
        SL -= Arr[m].P;
        SR += Arr[m].P;
    }

    return m;
}
void Fano(int L, int R, int k, Code *Arr)
{
    int m;

    if (L < R)
    {
        k++;
        m = Med(L, R, Arr);

        for (int i = L; i <= R; i++)
        {
            if (i <= m)
            {
                Arr[i].C[k] = '0';
                Arr[i].L++;
            }
            else
            {
                Arr[i].C[k] = '1';
                Arr[i].L++;
            }
        }

        Fano(L, m, k, Arr);
        Fano(m + 1, R, k, Arr);
    }
}

void GilbertMur(int size, Code *Arr)
{
    Arr[0].Q = 0;
    Arr[0].L = -log2(Arr[0].P) + 2;

    for (int i = 1; i < size; i++)
    {
        Arr[i].Q = Arr[i - 1].Q + (Arr[i - 1].P) / 2;
        Arr[i].L = -log2(Arr[i].P) + 2;
    }

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < Arr[i].L; j++)
        {
            Arr[i].Q = Arr[i].Q * 2;

            if (Arr[i].Q >= 1)
            {
                Arr[i].C[j] = '1';
                Arr[i].Q -= 1;
            }
            else
                Arr[i].C[j] = '0';
        }
    }
}

void printCode(int n, int count, Code *Arr, string Name)
{
    cout << "\n"
         << setw(9) << "Символ"
         << setw(21) << "Верояность символа"
         << setw(16) << "Кодовое слово"
         << setw(23) << "Длина кодового слова"
         << endl;

    for (int i = 0; i < n; i++)
    {
        cout << setw(7) << Arr[i].key;
        cout << setw(11) << " ";

        if (Name == "Fano")
            cout << round(Arr[i].P / count * 10000) / 10000;
        else if (Name == "Shannon" || Name == "GilbertMur")
            cout << round(Arr[i].P * 10000) / 10000;
        else if (Name == "Huffman")
            cout << round(Arr[i].Q * 10000) / 10000;

        cout << setw(14) << " ";

        for (int j = 0; j < Arr[i].L; j++)
        {
            cout << Arr[i].C[j];
        }

        cout << setw(17) << "  " << Arr[i].L << endl;
    }
}
