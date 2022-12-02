#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>

using namespace std;
using namespace sf;
const int N = 100;
const int resX = 640;
const int resY = 480;
RenderWindow window(VideoMode(resX, resY), "Лаба_4+(5)");//иницализация окна

class base {
protected:
    int dotX,dotY,direction,size,side,R,G,B;
    Color color;
public:
    base() {//конструктор основного класса
        dotX = rand() % 640 + 1;
        dotY = rand() % 480 + 1;
        direction = rand() % 4 + 1;
        size = rand() % 100 + 1;
        R = rand() % 255 + 1;
        G = rand() % 255 + 1;
        B = rand() % 255 + 1;
    }
    void Type1() {//тип движений с отражением от стенок экрана 
        switch (direction) {
        case 1:
            if (dotX < resX) dotX += 20;
            else direction = 4;
            break;
        case 2:
            if (dotY < resY) dotY += 20;
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
};
class Line : public base {
protected:
    int lenght;
    RectangleShape line;
public:
    Line() {
        lenght = rand() % 10 + 1;
    }
    void Draw_Line(int mode, int angle) {
        Color color(R, G, B, 255);//назначение цвета
        line.setFillColor(color);//выбор цвета заливки
        line.setSize(Vector2f(lenght, size));//размер через конструктор Vector2f (перебирает наши параметры длинна и размер непосредственно в координаты) ну это теория;)
        line.setOrigin(lenght / 2, size / 2);//задаем центр обьекта
        line.setPosition(Vector2f(dotX + lenght, dotY));//положение на экране
        window.draw(line);
        if (mode == 1) Type1(); else RotationLine(angle);//выбор метода движений
    }
    virtual void RotationLine(int angle){//виртуальный метод, на сколько я понял то это метод будет унаследован и в последствии будут перезаписаться 
        line.setRotation(angle);         //сам метод про вращение фигур
    }
};
class Circle : public Line {//класс круг наследует параметры из public и protected класса Line
protected:
    int rad;
    CircleShape circle;
public:
    Circle() {
        rad = rand() % 25 + 1;
    }
    void Draw_Circle(int mode) {
        Color color(R, G, B, 255);
        circle.setFillColor(color);
        circle.setRadius(rad);
        circle.setPosition(Vector2f(dotX, dotY));
        window.draw(circle);
        if (mode == 1) Type1();//круг как не крути круг :D
    }
};
class Triangle : public Circle {
protected:
    CircleShape triangle;
public:
    ~Triangle() {}//деструктор
    void Draw_Triangle(int mode, int angle) {
        Color color(R, G, B, 255);
        triangle.setFillColor(color);
        triangle.setPointCount(3);
        triangle.setRadius(rad);
        triangle.setOrigin(rad,rad);
        triangle.setPosition(Vector2f(dotX + lenght, dotY));
        window.draw(triangle);
        if (mode == 1) Type1(); else RotationLine(angle);
    }
    void RotationLine(int angle) override{//унаследованый виртуальный метод перезаписан
        triangle.setRotation(angle);
    }
};
class Rectangle : public Circle {
protected:
    CircleShape rectangle;
public:
    ~Rectangle() {}
    void Draw_Rectangle(int mode, int angle) {
        Color color(R, G, B, 255);
        rectangle.setFillColor(color);
        rectangle.setPointCount(4);
        rectangle.setRadius(rad);
        rectangle.setOrigin(rad, rad);
        rectangle.setPosition(Vector2f(dotX + lenght, dotY));
        if (mode == 1) Type1(); else RotationLine(angle);
        window.draw(rectangle);
    }
    void RotationLine(int angle) override {
        rectangle.setRotation(angle);
    }
};
class Ellipse : public Circle {
protected:
    int H_Lenght ,V_Lenght;
    CircleShape ellipse;
public:
    Ellipse() {
        V_Lenght = rand() % 5 + 1;
        H_Lenght = 0;
    }
    void Draw_Ellipse(int mode, int angle) {
        Color color(R, G, B, 255);
        ellipse.setFillColor(color);
        ellipse.setRadius(rad);
        ellipse.setOrigin(rad, rad);
        ellipse.setPosition(Vector2f(dotX, dotY));
        ellipse.setScale(H_Lenght,V_Lenght);
        if (V_Lenght == 1) H_Lenght = 2; else H_Lenght = 1;//Грубо говоря растягивает нашу фигуру
        if (mode == 1) Type1(); else RotationLine(angle);
        window.draw(ellipse);
    }
    void RotationLine(int angle) override {
        ellipse.setRotation(angle);
    }
};
class Rhombus : public Ellipse {
protected:
    CircleShape rhombus;
public:
    ~Rhombus() {}
    void Draw_Rhombus(int mode, int angle) {
        Color color(R, G, B, 255);
        rhombus.setFillColor(color);
        rhombus.setPointCount(4);
        rhombus.setRadius(rad);
        rhombus.setOrigin(rad, rad);
        rhombus.setPosition(Vector2f(dotX, dotY));
        rhombus.setScale(H_Lenght, V_Lenght);
        if (V_Lenght == 1) H_Lenght = 2; else H_Lenght = 1;
        if (mode == 1) Type1(); else RotationLine(angle);
        window.draw(rhombus);
    }
    void RotationLine(int angle) override {
        rhombus.setRotation(angle);
    }
};
int main(){
    window.setVerticalSyncEnabled(true);//без этого будет ЖЕСТЬ
    window.setFramerateLimit(60);
    setlocale(LC_ALL, "ru");
    srand(time(0));

    Line shapeLine[N];//создаем массив типо класса
    Circle shapeCircle[N];
    Triangle shapeTriangle[N];
    Rectangle shapeRectangle[N];
    Ellipse shapeEllipse[N];
    Rhombus shapeRhombus[N];
    int mode, angle=0;

    cout << "Задайте тип движения:" << endl
         << "1)Прямолинейное движение с отражением от стенок экрана" << endl
         << "2)Вращение вокруг центра фигуры" << endl;
    cin >> mode;

    while (window.isOpen()) {//пока окно открыто рисуются фигуры
        for (int i = 0;i < N;i++) {
            shapeLine[i].Draw_Line(mode,angle);
            shapeCircle[i].Draw_Circle(mode);
            shapeTriangle[i].Draw_Triangle(mode,angle);
            shapeRectangle[i].Draw_Rectangle(mode, angle);
            shapeEllipse[i].Draw_Ellipse(mode, angle);
            shapeRhombus[i].Draw_Rhombus(mode, angle);
        }
        window.display();//отображаем на дисплее
        window.clear(Color::Black);//стираем и рисуем заново
        if (angle > 359) angle = 0; else angle++;//вращение фигур, может работать и бех этого но для предотвращения переполнения перменной лишнем не будет
    }
}