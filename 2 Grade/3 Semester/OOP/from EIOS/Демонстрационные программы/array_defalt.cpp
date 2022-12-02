#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <time.h>

using namespace std;


class Point {
		int x;
		int y;
		int color;
	public:
           Point (int set_x=rand() % 640, int set_y=rand() % 360,
        int set_color=rand() % 14) : x(set_x), y(set_y), color(set_color)
		       { 
                                             cout<<"constructor   Point\n";
                                           }
		
           void ff () {cout<<" color="<<color<<endl;};
};
int main()
{

srand(time(0));

Point *p = new Point[3];
    p[0].ff();
    p[1].ff();
    p[2].ff();
    p->ff();  

 return 0;
}

