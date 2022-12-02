#include <iostream>
#include <conio.h>
#include <stdlib.h>

using namespace std;



class X
{    protected: 
        int x;
   public:
        X(){x=0; cout<<"default construktor"<<" x="<<x<<endl;}
        X(int i){x=i; cout<<"initial construktor"<<" x="<<x<<endl;}                  
};
int main()
{ // X obj_x;
  X obj_x();
//X obj_x(5);  
}	
