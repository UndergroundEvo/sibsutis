#include <iostream>
#include <conio.h>
#include <stdlib.h>

using namespace std;
  
   class vector  {
      int x,y,z;
      public:
             vector operator+(vector t);
             vector operator=(vector t);
             vector operator++();
             vector operator++(int);
             void show(){cout<<"x = "<<x<<" | y= "<<y<<"| z = "<<z<<"\n"; };
             void assign (int mx, int my, int mz )
               {  x=mx; 
                   y=my;
                   z=mz;     }
              };
vector vector::operator+(vector t)
{
  vector temp;
  temp.x = x+t.x;
  temp.y = y+t.y;
  temp.z = z+t.z;
  return temp;   };
vector  vector::operator=(vector t)
{
 x=t.x;
 y=t.y;
 z=t.z;
 return *this;        
};
vector  vector::operator++()
{
 x++;
 y++;
 z++;
 return *this;        
};
vector  vector::operator++(int)
{
++x;
 ++y;
++z;
 return *this;        
};

int main()
{
vector a,b,c;
 a.assign(1,2,3);
 b.assign(10,10,10); 
 a.show();
 b.show();
 c=a+b;
 c.show();
 c=a+b+c;
 c.show();
 c=b=a;
 c.show();
 b.show();
 //c++;
 c.show();
 


 getch(); 
 return 0;  
}
