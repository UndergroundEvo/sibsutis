/***************************************************************
 * Encoding:  Cyrillic (CP 866)                                *
 * Name:      "Построение таблиц кодовых слов классами         *
 *             Fixed + Variable, гамма-код и омега-код Элиаса" *
 * Authors:   ИП-111 Корнилов Андрей,                          *
 *            ИП-111 Попов Мирон.                              *
 ***************************************************************/

#include <iostream>
#include <iomanip>

using namespace std;

string Int_to_String(int i);

void Binary(int x, int n, char *str);

void Fixed_Variable();
void gammaElias(int n);
void omegaElias(int n);

int main()
{
    cout << "Fixed + Variable Code: \n\n";
    Fixed_Variable();

    cout << "Elias\' Gamma Code: \n\n";
    gammaElias(64);

    cout << endl
         << "Elias\' Omega Code: \n\n";
    omegaElias(64);

    system("pause");
    return 0;
}

void Binary(int x, int n, char *str)
{
    int temp;

    for (int i = n - 2; i >= 0; i--)
    {
        temp = (x % 2) + '0';
        str[i] = (char)temp;
        x = x / 2;

        if (x <= 0)
        {
            for (int j = i - 1; j >= 0; j--)
                str[j] = '0';
            break;
        }
    }
}

void Fixed_Variable()
{
    int n = 16, i, l;
    int index;

    char c[n], e[5], man[n - 1];

    for (int x = 0; x < 64; x++)
    {
        Binary(x, n, c);

        for (i = 0; i < n - 1; i++)
        {
            if (c[i] == '1')
                break;
        }

        index = n - i - 1;
        Binary(index, 5, e);

        cout << setw(5) << x << " | ";
        cout << setw(4) << e;

        if (x >= 2)
        {
            l = 0;

            for (int j = i + 1; j < n; j++)
            {
                man[l] = c[j];
                l++;
            }

            cout << " " << man;
        }

        cout << "\n";
    }
    cout << "\n\n\n";
}

void gammaElias(int n)
{
    for (int i = 1; i < n; i++)
    {
        string mant;

        for (int j = i; j >= 1; j /= 2)
            mant.insert(0, 1, (char)(j % 2 + '0'));

        string exp;

        if (mant.length() >= 1)
            exp.insert(0, mant.length() - 1, '0');

        cout << setw(5) << i << " | " << setw(5) << exp << " " << mant << '\n';
    }
    cout << "\n\n";
}

string Int_to_String(int i)
{
    string str;

    for (int j = i; j >= 1; j /= 2)
        str.insert(0, 1, (char)(j % 2 + '0'));

    return str;
}

void omegaElias(int n)
{
    cout << setw(5) << "1" <<  " | " << " 0 \n";

    for (int i = 2; i < n; ++i)
    {
        string str = "0";
        str.insert(0, 1, ' ');
        str.insert(0, Int_to_String(i));

        string str1 = Int_to_String(i);
        str.insert(0, 1, ' ');

        int len = (int)str1.length() - 1;

        string tmp = Int_to_String(len);

        while (len > 1)
        {
            str.insert(0, tmp);
            str.insert(0, 1, ' ');
            len = (int)tmp.length() - 1;
            tmp = Int_to_String(len);
        }

        cout << setw(5) << i << " | " << str << '\n';
    }
    cout << "\n\n\n";
}