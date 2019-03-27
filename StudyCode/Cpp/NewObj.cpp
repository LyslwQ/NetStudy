#include <iostream>

using namespace std;

class A{
public:
    A(){cout << "A()" << endl;};
    A(int i){ cout << "A(i)" << endl;};
};

int main()
{
    A a();
    return 0;
}
