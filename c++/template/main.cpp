
#include <iostream>

#include "multiargs.h"

using namespace std;

int main() {
    int a = 5;
    int b = multiargs::lexical_cast<int>(a);
    cout<<b<<endl;
    multiargs::CTest<int, float> test_obj;
    return 0;
}
