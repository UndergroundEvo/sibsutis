#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>


using namespace std;
using namespace sf;

const int N = 25;
const int resX = 1024;
const int resY = 768;
Text text;
RenderWindow window(VideoMode(resX, resY), "LR6+");

class base
{
protected:
	int direction, size, side, R, G, B, T;
	float dotX, dotY;
	Color color;

public:
	base() {
		dotX = rand() % 1024 + 1;
		dotY = rand() % 768 + 1;
		direction = rand() % 4 + 1;
		size = rand() % 100 + 1;

		/*R = rand() % 255 + 1;
		G = rand() % 255 + 1;
		B = rand() % 255 + 1;*/
	};
	virtual ~base() {}
	virtual void Draw(int mode, float angle)=0;
	virtual void Move(){
		switch (direction)
		{
		case 1:
			if (dotX < resX)
				dotX += 1;
			else
				direction = 4;
			break;
		case 2:
			if (dotY < resY)
				dotY += 1;
			else
				direction = 3;
			break;
		case 3:
			if (dotY > 7)
				dotY -= 1;
			else
				direction = 2;
			break;
		case 4:
			if (dotX > 5)
				dotX -= 1;
			else
				direction = 1;
			break;
		}
	}
	virtual void Move(float angle)=0;
};
class Line : public base{
protected:
	float lenght;
	RectangleShape line;

public:
	Line(){
		lenght = rand() % 10 + 1;
		R = rand() % 255 + 1;
		G = rand() % 255 + 1;
		B = rand() % 255 + 1;
		T = rand() % 255 + 1;
	}
	Line(int multiplier,int R,int G,int B){
		lenght = (rand() % 10 + 1)* multiplier;
		Line::R = R;
		Line::G = G;
		Line::B = B;
	}
	~Line(){}
	void Draw (int mode, float angle){
		Color color(R, G, B, T);
		line.setFillColor(color);
		line.setSize(Vector2f(lenght, size));
		line.setOrigin(lenght / 2, size / 2);
		line.setPosition(Vector2f(dotX + lenght, dotY));
		window.draw(line);
		if (mode == 1)
			base::Move();
		else
			Move(angle);
	}
	/*void Draw_Line(int mode, float angle)
	{
		Color color(R, G, B, 255);
		line.setFillColor(color);
		line.setSize(Vector2f(lenght, size));
		line.setOrigin(lenght / 2, size / 2);
		line.setPosition(Vector2f(dotX + lenght, dotY));
		window.draw(line);
		if (mode == 1)
			Type1();
		else
			RotationLine(angle);
	}*/

	void Move(float angle){
		line.setRotation(angle);
	}
};
class Circle : public Line
{
protected:
	float rad;
	CircleShape circle;

public:
	Circle()
	{
		rad = rand() % 25 + 1;
	}
	Circle(int multiplier, int R, int G, int B)
	{
		rad = (rand() % 25 + 1)* multiplier;
		Circle::R = R;
		Circle::G = G;
		Circle::B = B;
	}

	void Draw(int mode, float angle){
		Color color(R, G, B, T);
		circle.setFillColor(color);
		circle.setRadius(rad);
		circle.setPosition(Vector2f(dotX, dotY));
		window.draw(circle);
		if (mode == 1) base::Move();
	}
};
class Triangle : public Circle
{
protected:
	CircleShape triangle;
public:
	Triangle() {
		lenght = rand() % 10 + 1;
		rad = rand() % 30 + 1;
		R = rand() % 255 + 1;
		G = rand() % 255 + 1;
		B = rand() % 255 + 1;
	}
	Triangle(int multiplier, int R, int G, int B) {
		lenght = (rand() % 10 + 1) * multiplier;
		rad = (rand() % 30 + 1) * multiplier;
		Triangle::R = R;
		Triangle::G = G;
		Triangle::B = B;
	}
	~Triangle() {}
	void Draw(int mode, float angle)
	{
		Color color(R, G, B, T);
		triangle.setFillColor(color);
		triangle.setPointCount(3);
		triangle.setRadius(rad);
		triangle.setOrigin(rad, rad);
		triangle.setPosition(Vector2f(dotX + lenght, dotY));
		window.draw(triangle);
		if (mode == 1)
			base::Move();
		else
			Move(angle);
	}

	void Move(float angle){
		triangle.setRotation(angle);
	}
};
class Rectangle : public Circle
{
protected:
	CircleShape rectangle;

public:
	Rectangle() {
		lenght = rand() % 10 + 1;
		rad = rand() % 30 + 1;
		R = rand() % 255 + 1;
		G = rand() % 255 + 1;
		B = rand() % 255 + 1;

	}
	Rectangle(int multiplier, int R, int G, int B) {
		lenght = (rand() % 10 + 1) * multiplier;
		rad = (rand() % 30 + 1) * multiplier;
		Rectangle::R = R;
		Rectangle::G = G;
		Rectangle::B = B;
	}
	~Rectangle() {}
	void Draw(int mode, float angle)
	{
		Color color(R, G, B, T);
		rectangle.setFillColor(color);
		rectangle.setPointCount(4);
		rectangle.setRadius(rad);
		rectangle.setOrigin(rad, rad);
		rectangle.setPosition(Vector2f(dotX + lenght, dotY));
		window.draw(rectangle);
		if (mode == 1)
			base::Move();
		else
			Move(angle);
	}
	void Move(float angle)
	{
		rectangle.setRotation(angle);
	}
};
class Ellipse : public Circle
{
protected:
	float H_Lenght, V_Lenght;
	CircleShape ellipse;

public:
	Ellipse()
	{
		V_Lenght = rand() % 5 + 1;
		H_Lenght = 0;
		lenght = rand() % 10 + 1;
		rad = rand() % 30 + 1;
		R = rand() % 255 + 1;
		G = rand() % 255 + 1;
		B = rand() % 255 + 1;
	}
	Ellipse(int multiplier, int R, int G, int B) {
		V_Lenght = rand() % 5 + 1;
		H_Lenght = 0;
		lenght = (rand() % 10 + 1) * (multiplier / 2);
		rad = (rand() % 30 + 1) * (multiplier / 2);
		Ellipse::R = R;
		Ellipse::G = G;
		Ellipse::B = B;
	}
	~Ellipse() {}
	void Draw(int mode, float angle)
	{
		Color color(R, G, B, 255);
		ellipse.setFillColor(color);
		ellipse.setRadius(rad);
		ellipse.setOrigin(rad, rad);
		ellipse.setPosition(Vector2f(dotX, dotY));
		ellipse.setScale(H_Lenght, V_Lenght);
		if (V_Lenght == 1)
			H_Lenght = 2;
		else
			H_Lenght = 1;
		if (mode == 1)
			base::Move();
		else
			Move(angle);
		window.draw(ellipse);
	}

	void Move(float angle)
	{
		ellipse.setRotation(angle);
	}
};
class Rhombus : public Ellipse
{
protected:
	CircleShape rhombus;

public:
	Rhombus() {
		V_Lenght = rand() % 5 + 1;
		H_Lenght = 0;
		lenght = rand() % 10 + 1;
		rad = rand() % 30 + 1;
		R = rand() % 255 + 1;
		G = rand() % 255 + 1;
		B = rand() % 255 + 1;

	}
	Rhombus(int multiplier, int R, int G, int B) {
		V_Lenght = rand() % 5 + 1;
		H_Lenght = 0;
		lenght = (rand() % 10 + 1) * (multiplier/10);
		rad = (rand() % 30 + 1) * (multiplier / 10);
		Rhombus::R = R;
		Rhombus::G = G;
		Rhombus::B = B;
	}
	~Rhombus() {}
	void Draw(int mode, float angle)
	{
		Color color(R, G, B, 255);
		rhombus.setFillColor(color);
		rhombus.setPointCount(4);
		rhombus.setRadius(rad);
		rhombus.setOrigin(rad, rad);
		rhombus.setPosition(Vector2f(dotX, dotY));
		rhombus.setScale(H_Lenght, V_Lenght);
		if (V_Lenght == 1)
			H_Lenght = 2;
		else
			H_Lenght = 1;
		if (mode == 1)
			base::Move();
		else
			Move(angle);
		window.draw(rhombus);
	}

	void Move(float angle)
	{
		rhombus.setRotation(angle);
	}
};
int main(){
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);
	setlocale(LC_ALL, "ru");
	srand(time(NULL));
	
	int mode, multiplier,R=125,G = 125,B = 125;
	sf::Event event;
	
	cout << "Задайте тип движения:\n"
		<< "1) Прямолинейное движение с отражением от стенок экрана !!!указание параметров!!!\n"
		<< "2) Вращение вокруг центра фигуры\n"
		<< endl;
	cin >> mode;

	base* Shapes[10][N];
	if (mode == 1) {
		cout << "Введите множитель (от 1 до 10) и цвета RGB (от 0 до 255)\n" << endl;
		cin >> multiplier;
		cin >> R;
		cin >> G;
		cin >> B;
		for (int j = 0;j < N;j++) {
			Shapes[0][j] = new Line(multiplier,R,G,B);
			Shapes[1][j] = new Circle(multiplier, R, G, B);
			Shapes[2][j] = new Triangle(multiplier, R, G, B);
			Shapes[3][j] = new Rectangle(multiplier, R, G, B);
			Shapes[4][j] = new Ellipse(multiplier, R, G, B);
			Shapes[5][j] = new Rhombus(multiplier, R, G, B);
		}
	}
	else {
		for (int j = 0;j < N;j++) {
			Shapes[0][j] = new Line();
			Shapes[1][j] = new Circle();
			Shapes[2][j] = new Triangle();
			Shapes[3][j] = new Rectangle();
			Shapes[4][j] = new Ellipse();
			Shapes[5][j] = new Rhombus();
		}
	}

	float angle = 0;

	while (window.isOpen())
	{

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		for (int i = 0; i < N; i++)
		{
			Shapes[0][i]->Draw(mode, angle); //Line
			Shapes[1][i]->Draw(mode, angle); //Circle
			Shapes[2][i]->Draw(mode, angle); //Triangle
			Shapes[3][i]->Draw(mode, angle); //Rectangle
			Shapes[4][i]->Draw(mode, angle); //Ellipse
			Shapes[5][i]->Draw(mode, angle); //Rhombus
		}
		window.display();
		window.clear(Color::Black);
		angle = angle > 359 ? 0 : angle + 1;
	}
}