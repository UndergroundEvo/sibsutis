#include <iostream>
#include <stdlib.h>
#include "TXLib.h"
using namespace std;
const int size_array = 100;
int screen_sizeX = 640, screen_sizeY = 480;
class base {
public:
    int dotX=NULL, dotY = NULL, direction = NULL, side = 0;
    COLORREF color = 0;
    void Dot() {
        txSetColor(color, 10);
        txCircle(dotX, dotY, 5);
    }
    void Create_RenderWindow() {
        txCreateWindow(screen_sizeX, screen_sizeY, true);
    }
    void Type1() {
        switch (direction) {
        case 1:
            if (dotX < screen_sizeX) dotX += 20;
            else direction = 4;
            break;
        case 2:
            if (dotY < screen_sizeY) dotY += 20;
            else direction = 3;
            break;
        case 3:
            if (dotY > 7) dotY -= 20;
            else direction = 2;
            break;
        case 4:
            if (dotX > 5) dotX -= 20;
            else direction = 1;
            break;
        }
    }
    void Type2() {
        switch (direction) {
        case 1:
            if (dotX < screen_sizeX) {
                dotX += 10;
                dotY += side;
            }
            else {
                side = rand() % 20 - 10;
                direction = 1 + rand() % 4;
                if (dotX >= screen_sizeX) direction = 4;
            }
            break;
        case 2:
            if (dotY < screen_sizeY) {
                dotY += 10;
                dotX += side;
            }
            else {
                side = rand() % 20 - 10;
                direction = 1 + rand() % 4;
                if (dotY >= screen_sizeY) direction = 3;
            }
            break;
        case 3:
            if (dotY > 7) {
                dotY -= 10;
                dotX -= side;
            }
            else {
                side = rand() % 20 - 10;
                direction = 1 + rand() % 4;
                if (dotY <= 7) direction = 2;
            }
            break;
        case 4:
            if (dotX > 5) {
                dotX -= 10;
                dotY -= side;
            }
            else {
                side = rand() % 20 - 10;
                direction = 1 + rand() % 4;
                if (dotX <= 7) direction = 1;
            }
            break;
        }
    }
};
class normal: public base { 
public:
    int dotX1 = NULL, dotY1 = NULL, rad = 10;
    void Line() {
        txSetColor(color, 10);
        txLine(dotX, dotY, dotX1, dotY1);
    }
    void Circle() {
        txSetColor(color, 10);
        txCircle(dotX, dotY, rad);
    }
};
class cringe:public normal {
public:
    int dotX2 = NULL, dotY2 = NULL;
    void Rectangle() {
        txSetColor(color, 10);
        txSetFillColor(color);
        txRectangle(dotX, dotY, dotX1, dotY1);
    }
    void Triangle() {
        txSetColor(color, 1);
        txSetFillColor(color);
        //txTriangle(dotX, dotY, dotX1, dotY1, dotX2, dotY2);
        POINT A[3] = { { dotX, dotY }, { dotX1, dotY1 }, { dotX2, dotY2 } };
        txPolygon(A,3);
    }
    void Ellipse() {
        txSetColor(color, 10);
        txSetFillColor(color);
        txEllipse(dotX, dotY, dotX1, dotY1);
    }
    cringe() {
        dotX = rand() % screen_sizeX;
        dotY = rand() % screen_sizeY;
        dotX1 = dotX + rand() % 60 - 30;
        dotY1 = dotY + rand() % 60 - 30;
        dotX2 = dotX + rand() % 60 - 30;
        dotY2 = dotY + rand() % 60 - 30;
        direction = rand() % 4 + 1;
        color = RGB(rand() % 255, rand() % 255, rand() % 255);
    }
};
int main()
{
    setlocale(LC_ALL, "ru");
    srand(time(0));
    int type,figure[size_array];
    cringe open,arr[size_array];
    for (int i = 0; i < size_array; i++) {
        //arr[i].Generate();
        figure[i] = rand() % 5 + 1;
    }
    open.Create_RenderWindow();
    txTextOut(5, 0, "Метод движения фигур?");
    txTextOut(5, 20, "1) Прямолинейное движение с отражением от стенок экрана");
    txTextOut(5, 40, "2) Вращение вокруг центра фигуры");
    cin >> type;
    if (type == 1) {
        while (true) {
            txSetColor(RGB(0, 0, 0), 10);
            for (int i = 0; i < size_array; i++) {
                //txBegin();
                //txSetFillColor(0);
                //txClear();
                arr[i].Type1();
                switch (figure[i]) {
                default:
                    arr[i].Dot(); break;
                case 1:
                    arr[i].Line(); break;
                case 2:
                    arr[i].Circle(); break;
                case 3:
                    arr[i].Rectangle(); break;
                case 4:
                    arr[i].Triangle(); break;
                case 5:
                    arr[i].Ellipse(); break;
                }
                txSleep(1);
                //txEnd();
            }
        }//Замена метода постраения фигур, на незвасимый от других точек
        //И необходимо что-то сдлеать с обновление экрана((( Слишком медленно
    }
}
