#include <bits/stdc++.h>
using namespace std;

struct Data
{
	int a, b;
	// default + parametrized constructor
	Data(int a = 2, int b = 8) : a(a), b(b) {} 
	// Using const here because it doesn't modify the member obj
	Data operator+(const Data& d) const
	{
		return Data(d.a + a);
	}
	// '=' operator modifies the current obj hence, no 'const'
	Data& operator=(const Data& d)
	{
		cout<<"'=' was called obj.a = "<<a<<endl;
		a = d.a;
		return *this; // Returns same obj by reference for ex: a = (b = c)
	}
	bool operator==(const Data& d) const
	{
		return (d.a == a && d.b == b);
	}
};

// Classes work similar to structs
class Data2
{
	int a, b;
public:
	Data2(int a = 2, int b = 8) : a(a), b(b) {}
	Data2(const Data2 &d) // Important to put const here
	{
		cout << "Copy constructor called" << endl;
		a = d.a;
		b = d.b;
	}
	Data2 operator+(const Data2& d) const
	{
		return Data2(d.a + a);
	}
	bool operator==(const Data2& d) const
	{
		return (d.a == a && d.b == b);
	}
	int getA()
	{
		return a;
	}
};

int main() 
{
	int n = 10;
	Data b(3), c(4);
	Data& a = (b = c); // Here, first '=' doesn't invoke the operator= 
	Data& ad = a;
	// a now refers to b, ad also refers to b
	cout<<a.a<<endl;
	cout<<a.b<<endl;
	c.a = 2;
	cout<<(a == b)<<endl;
	Data *p = new Data(5, 6);
	cout<<p->a<<endl;
	Data2 d2(8, 7), d3(9, 10);
	cout <<  d2.getA() << endl;
	d2 = d3; // Default copy constructor not called
	Data2 d4 = d2; // Default copy constructor called
	cout << d4.getA() << endl;
	return 0;
}