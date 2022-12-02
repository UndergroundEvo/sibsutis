#include <iostream>
#include <windows.h>
#include <ctime>
#include <cstdlib>

enum Color {
		Black     = 0,
		Grey      = FOREGROUND_INTENSITY,
		LightGrey = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
		White     = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
		Red       = FOREGROUND_RED,
		Green     = FOREGROUND_GREEN,
		Blue      = FOREGROUND_BLUE,
		Yellow    = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
		Default   = LightGrey
};

class Point {
		int x;
		int y;
		Color color;
	public:
		Point(int set_x=0, int set_y=0, Color set_color=Default) : x(set_x), y(set_y), color(set_color)
		{}
		void setCoordinates(int, int);
		void setColor(int);
		void draw() const;
};

void Point::setCoordinates(int set_x, int set_y)
{
	x = set_x;
	y = set_y;
}

void Point::setColor(int set_color)
{
	switch(set_color) {
		case 1:
			color = Black;
			break;
		case 2:
			color = Grey;
			break;
		case 3:
			color = LightGrey;
			break;
		case 4:
			color = White;
			break;
		case 5:
			color = Red;
			break;
		case 6:
			color = Green;
			break;
		case 7:
			color = Blue;
			break;
		case 8:
			color = Yellow;
			break;
	}
}

void Point::draw() const
{
	COORD pointCoord;
	pointCoord.X = x;
	pointCoord.Y = y;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pointCoord);
	std::cout << '.';
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Default);
}

int main()
{
	std::srand(std::time(NULL));
	Point point[100];
	system("cls");
	for(int i=0; i<100; ++i) {
		point[i].setCoordinates(std::rand()%80, std::rand()%25);
		point[i].setColor(std::rand()%8+1);
		point[i].draw();
	}

	return 0;
}
