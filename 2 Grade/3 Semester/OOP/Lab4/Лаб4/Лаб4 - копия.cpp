#include <iostream>
#include "TXLib.h"
using namespace std;
const int size_array = 100;
int screen_sizeX = 640, screen_sizeY = 480;
COLORREF color = 0;
class base {
private:
	int dotX, dotY, direction, side = 0;
public:
    void Dot(int dotX,int dotY, COLORREF color) {
        txSetColor(color, 10);
        txCircle(dotX, dotY, 5);
    }
    void Create_RenderWindow() {
        txCreateWindow(screen_sizeX, screen_sizeY, true);
    }
    void Type1() {
        switch (direction) {
        case 1:
            if (dotX < screen_sizeX) dotX += 5;
            else direction = 4;
            break;
        case 2:
            if (dotY < screen_sizeY) dotY += 5;
            else direction = 3;
            break;
        case 3:
            if (dotY > 7) dotY -= 5;
            else direction = 2;
            break;
        case 4:
            if (dotX > 5) dotX -= 5;
            else direction = 1;
            break;
        }
    }
};
class normal:private base {
private:
    int dotX1, dotY1, rad;
public:
    void Line(int dotX, int dotY, int dotX1, int dotY1, COLORREF color) {
        txSetColor(color, 10);
        txLine(dotX, dotY, dotX1, dotY1);
    }
    void Circle(int dotX, int dotY,int rad, COLORREF color) {
        txSetColor(color, 10);
        txCircle(dotX, dotY, rad);
    }
};
class cringe:private normal {
private:
    int dotX2, dotY2;
public:
    void Rectangle(int dotX, int dotY, int dotX1, int dotY1, COLORREF color) {
        txSetColor(color, 10);
        txRectangle(dotX, dotY, dotX1, dotY1);
    }
    void Triangle(int dotX, int dotY, int dotX1, int dotY1,int dotX2, int dotY2, COLORREF color) {
        txSetColor(color, 10);
        txTriangle(dotX, dotY, dotX1, dotY1, dotX2, dotY2);
    }
    void Ellipse(int dotX, int dotY, int dotX1, int dotY1, COLORREF color) {
        txSetColor(color, 10);
        txEllipse(dotX, dotY, dotX1, dotY1);
    }
};
int main()
{
    setlocale(LC_ALL, "ru");
    srand(time(0));
    int type;
    base arr[size_array], open;
    open.Create_RenderWindow();
    txTextOut(5, 0, "Метод движения фигур?");
    txTextOut(5, 20, "1) прямолинейное движение с отражением от стенок экрана");
    txTextOut(5, 40, "2) вращение вокруг центра фигуры");
    cin >> type;
    for (int i = 0,j=rand()%7+1; i < size_array; i++)
         
        switch (j) {
        case 1: arr[i].Dot(dotX,dotY);
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        }
    if (type == 1) {
        while (true) {
            txSetColor(RGB(0, 0, 0), 10);
            for (int i = 0; i < size_array; i++) {
                arr[i].Delete_Dot();
                arr[i].Type1();
                arr[i].Draw_Dot();

            }
            txSleep(1);
        }
    }
}
