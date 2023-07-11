
#include <iostream>
#include <string>

using namespace std;

int main()
{
    string a = "111";
    //string a = "0x7f";
    //string a = "7";
    cout<<stoi(a, nullptr, 2)<<endl;
    return 0;
}
