#include <iostream>
#include <conio.h>
#include <stdlib.h>

using namespace std;

class X
{ 
   protected: 
        int x;
   public:
        X(){x=0; cout<<"default construktor"<<" x="<<x<<endl;}
       // X(int i){x=i; cout<<"initial construktor"<<" x="<<x<<endl;}                  
};
/*class Y: public X
{ 
   protected: 
        int y;
   public:
       // Y():y(0){cout<<"default construktor"<<" y="<<y<<endl;}
    //   Y(){ y=0;cout<<"default construktor"<<" y="<<y<<endl;}
      //  Y(int i, int j=22):X(i)
      //  {y=j; cout<<"initial construktor"<<" y="<<y<<endl;}                  
};
*/
int main()
{
  X obj_x;
//X obj_x();
//X obj_x(5);
//Y obj_y(7);
//Y obj_y(6,10);  
    
 getch(); 
 return 0;  
}
