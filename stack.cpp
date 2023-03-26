#include <iostream>
#include <string>
using namespace std;

class stack
{
protected:
	static const int MAX_SIZE = 100;		// push 최대 횟수 100번
	int point;
	string data[MAX_SIZE];
public:
	stack()
	{
		point = -1;
	}
	bool empty()
	{
		if (point == -1)
			return true;
		else
			return false;
	}
	bool full()
	{
		if (point == MAX_SIZE - 1)
			return true;
		else
			return false;
	}
	void push(string val)
	{
		if (full())
			throw("full");
		else
			data[++point] = val;
	}
	string pop()
	{
		if (empty())
			return "empty";
		else
			return data[point--];
	}
	string peek()
	{
		if (empty())
			return "empty";
		else
			return data[point];
	}
	int size()
	{
		return point + 1;
	}
	string top()
	{
		if (empty())
			return "empty";
		else
			return data[point];
	}
};

int main(void)
{
	stack s;
	int n;
	cin >> n;		// 반복 횟수
	string str;		// 명령어 판별(push, top ..etc)

	while (n--)
	{
		cin >> str;
		if (str == "push")
		{
			string input;		// 저장할 문자열
			cin >> input;
			s.push(input);
		}
		else if (str == "pop")
		{
			cout << s.pop() << endl;
		}
		else if (str == "size")
		{
			cout << s.size() << endl;
		}
		else if (str == "empty")
		{
			if (s.empty())
				cout << "empty" << endl;
			else
				cout << "not empty" << endl;
		}
		else if (str == "top")
		{
			cout << s.top() << endl;
		}
	}
	return 0;
}
