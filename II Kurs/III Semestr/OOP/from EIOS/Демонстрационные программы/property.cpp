// test2.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
#include <stdlib.h> // для system("pause");

using namespace std; //для использования cout

class TMult
{ private:
int fval1;
int fval2;
int FRes;
void DoMult();
void SetVal1(int v);
void SetVal2(int v);
public:
TMult();
__property int Res={read=FRes, write=FRes};
__published:
__property int val1={read=fval1, write=Setval1 default 1};
__property int val2={read=fval2, write=Setval2 default 2};
 };



int main()
{
	int i=10;
	double d=1.1;
	long l=2345;

	
	cout<< "max is  "<<d<<"  i  "<<i<<" = "<<maximum(d,i)<<"\n";
	cout<< "max is  "<<i<<"  i  "<<d<<" = "<<maximum(i,d)<<"\n";
	cout<< "max is  "<<2<<"  i  "<<5.5<<" = "<<maximum(2,5.5)<<"\n";
	cout<< "max is  "<<i<<"  i  "<<5.5<<" = "<<maximum(i,5.5)<<"\n";
	cout<< "max is  "<<5.5<<"  i  "<<2<<" = "<<maximum(5.5,2)<<"\n";
	cout<< "max is  "<<i<<"  i  "<<l<<" = "<<maximum(i,l)<<"\n";
    cout<< "max is  "<<d<<"  i  "<<l<<" = "<<maximum(d,l)<<"\n";
   

	system("pause");
	return 0;
}

