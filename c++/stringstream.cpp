
#include <iostream>
#include <sstream>

using namespace std;

int main()
{
    string s;
    string key, val;
    stringstream ss;
    while (1) {
        getline(cin, s);
        if (s[0] == '#') continue;
        size_t idx = s.find('=');
        if (idx == string::npos) continue;
        s[idx] = ' ';
        ss.clear();
        ss<<s;
        ss>>key;
        if (!ss.eof()) {
            ss>>val;
        }
        cout<<"key: "<<key<<", val: "<<val<<endl;
    }

    return 0;
}
