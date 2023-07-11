
#include <iostream>

using namespace std;

int main(void)
{
#ifdef __x86_64__
    cout<<"is x86_64"<<endl;
#else
    cout<<"is not x86_64"<<endl;
#endif
    return 0;
}
