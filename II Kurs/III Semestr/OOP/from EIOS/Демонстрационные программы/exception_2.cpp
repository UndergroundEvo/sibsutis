#include <iostream>
#include <ctime>
#include <exception>
using namespace std;


// � ���� ������� �������� ��� ������� ������������� ����������
class exception_child: public exception
{
public:
  virtual const char* what() const throw()
  {
    return "�������� ����� ��������� ��������";
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
} SomeException("������������� ������ ��� ��������� ����������",1);

void DoSomething()
{
	int rnd = rand()%3;
	switch (rnd)
	{
	case 0:
		throw new exception("��������� �� ��������� ��������");
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
		cout << "��������� �� ������: " << e.Message() << ", ��� ������: " << e.ErrorCode();
	}
	catch(exception_child& e)
	{
		cout << "��������� �� ������: " << e.what();
	}
	catch(exception* e)
	{
		cout << "��������� �� ������: " << e->what();
		delete e; //�����������!
	}
	catch(...)
	{
		return 1; // ��������� ����������� ����������, ��������� ������� � �������
	}
	cin.get();
	return 0;
}