#include <iostream>
#include "TXLib.h"
using namespace std;
const int size_array = 100;
class tPoint {
private:
	int screen_sizeX = 640, screen_sizeY = 480;
	int dotX, dotY, direction, side=0;
	COLORREF color;
public:
	void Create_RenderWindow() {
		txCreateWindow(screen_sizeX, screen_sizeY, true);
	}
	tPoint() {
		dotX = rand() % 640 + 1;
		dotY = rand() % 480 + 1;
		direction = rand() % 4 + 1;
		color = RGB(rand() % 255, rand() % 255, rand() % 255);
	}
	void Draw_Dot() {
		txSetColor(color, 10);
		txCircle(dotX,dotY,5);
	}
	void Delete_Dot() {
		txSetColor(0,10);
		txCircle(dotX, dotY, 5);
	}
	void Type1(){
		switch (direction){
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
	void Type2(){
		switch (direction){
		case 1:
		if (dotX < screen_sizeX){
			dotX += 10;
			dotY += side;
		}
		else{
			side = rand() % 20 - 10;
			direction = 1 + rand() % 4;
			if (dotX >= screen_sizeX) direction = 4;
		}
		break;
		case 2:
			if (dotY < screen_sizeY){
				dotY += 10;
				dotX += side;
			}
			else{
				side = rand() % 20 - 10;
				direction = 1 + rand() % 4;
				if (dotY >= screen_sizeY) direction = 3;
				}
			break;
		case 3:
			if (dotY > 7){
				dotY -= 10;
				dotX -= side;
			}
			else{
				side = rand() % 20 - 10;
				direction = 1 + rand() % 4;
				if (dotY <= 7) direction = 2;
				}
		break;
		case 4:
			if (dotX > 5){
				dotX -= 10;
				dotY -= side;
			}
			else{
				side = rand() % 20 - 10;
				direction = 1 + rand() % 4;
				if (dotX <= 7) direction = 1;
				}
		break;
		}
	}
};
int main(){
	setlocale(LC_ALL, "ru");
	srand(time(0));
	int type;
	tPoint arr[size_array], open;
	open.Create_RenderWindow();
	txTextOut(5, 0, "Метод движения точек?");
	txTextOut(5, 20, "1) прямолинейное движение с отражением от стенок экрана");
	txTextOut(5, 40, "2) случайное движение с отражением.");
	cin >> type;
	/*for (int i = 0; i < size_array; i++) 
		arr[i].tPoint;*/
	if (type == 1) {
		while (true){
			txSetColor(RGB(0,0,0),10);
			for (int i = 0; i < size_array; i++){
				arr[i].Delete_Dot();
				arr[i].Type1();
				arr[i].Draw_Dot();
			}
			txSleep(1);
		}
	}
	else {
		while (true){
			txSetColor(RGB(0, 0, 0), 10);
			for (int i = 0; i < size_array; i++){
				arr[i].Delete_Dot();
				arr[i].Type2();
				arr[i].Draw_Dot();
			}
			txSleep(1);
		}
	}
}