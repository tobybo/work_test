// 结论是:
// 自身：组合对象构造先于自身构造;
// 继承：基类对象构造先于自身
// 注意：初始化列表的初始化对象只能是自身成员，但是初始化列表中已经可见组合或基类成员数据

#include <iostream>

using namespace std;

class B {
    public:
    B() {
        cout<<"B"<<endl;
    }
};

class Base {
    public:
    B b;
    int x = 0;
    Base() {
        cout<<"base"<<endl;
    }
};

class A : public Base {
    public:
    int y;
    A() : y(x) {
        cout<<"A "<<this<<" "<<&x<<endl;
    }
    int init() {
        cout<<"init x: "<<x<<endl;
        return 2;
    }
};

int main(void) {
    A a;
    return 0;
}
