 /*************************************************************************
 > File Name: test.cpp
 > Author: Ys
 > Created Time: 2019年03月21日 星期四 10时22分31秒
 ************************************************************************/

#include<iostream>
using namespace std;

struct A{
	A(){
		cout << "A()" << endl;
	}

	~A(){
		cout << "~A()" << endl;
	}
};

struct B{
	B(){
		cout << "B()" << endl;
	}

	~B(){
		cout << "~B()" << endl;
	}
};

static A a;
B b;

int main(void)
{
    return 0;
}
