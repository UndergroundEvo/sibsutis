#include <iostream>
#include <exception>
using namespace std;


// Основы

int main () {
  try
  {
	  throw 20;
  }
  catch (int e)
  {
	  cout << "Произошла ошибка " << e << endl;
  }
  cin.get();
  return 0;
}