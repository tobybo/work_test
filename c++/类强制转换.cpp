#include <iostream>

using namespace std;

class A {
    public:
        int _val;
        explicit A(int val) : _val(val) {}
};

int main()
{
    A a = 5 + 5;
    cout<<a._val<<endl;
    return 0;
}
