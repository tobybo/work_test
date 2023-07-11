
#include <iostream>
#include <string>
#include <climits>
#include <bitset>

using namespace std;

int main()
{
    unsigned int src = UINT_MAX;
    unsigned int total = 1;
    for (int i = 1; i < 32; ++i) {
        src -= total;
        total <<= 1;
        //cout<< bitset<sizeof(src) * 8>(src)<<endl;
        //cout<< hex << src <<endl;
    }
    total = 1;
    for (int i = 0; i < 31; ++i) {
        cout<<"0x"<< hex << total<<","<<endl;
        total <<= 1;
    }
    return 0;
}
