#include <iostream>
#include <ctime>
#include <exception>
using namespace std;


// В этом примере показаны три способа использования исключений
class exception_child: public exception
{
public:
  virtual const char* what() const throw()
  {
    return "Дочерний класс случайной величины";
  }
} myex;

class MyException
{
public:
	MyException(char* message,int error_code)
	{
		_message = message;
		_code = error_code;
	};
	char* Message()
	{
		return _message;
	};
	int ErrorCode()
	{
		return _code;
	};
protected:
	char* _message;
	int _code;
} SomeException("Нестандартный объект для обработки исключений",1);

void DoSomething()
{
	int rnd = rand()%3;
	switch (rnd)
	{
	case 0:
		throw new exception("Указатель на случайную величину");
	case 1:
		throw SomeException;
	case 2:
		throw myex;
	}

}
int main()
{
	srand(time(0));
	try
	{
		
		DoSomething();
	}
	catch(MyException& e)
	{
		cout << "Сообщение об ошибке: " << e.Message() << ", код ошибки: " << e.ErrorCode();
	}
	catch(exception_child& e)
	{
		cout << "Сообщение об ошибке: " << e.what();
	}
	catch(exception* e)
	{
		cout << "Сообщение об ошибке: " << e->what();
		delete e; //обязательно!
	}
	catch(...)
	{
		return 1; // Произошло неизвестное исключение, программа выходит с ошибкой
	}
	cin.get();
	return 0;
}