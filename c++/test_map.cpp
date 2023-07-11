#include <map>
#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

class CTest {
    public:
        const int size = 90;
        vector<unordered_map<char, bool>> map = vector<unordered_map<char, bool>>(90, unordered_map<char, bool>());

};

int main() {
    std::map<int, int> map;
    auto val = map[1];
    std::cout<<val<<std::endl;
    map[1] = 10;
    std::map<int, int>::iterator itor = map.find(1);
    std::cout<<(*itor).second<<std::endl;

    vector<unordered_map<char, bool>> v(90, unordered_map<char, bool>());
    return 0;
}
