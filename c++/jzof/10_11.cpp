// 面试题 10.11. 峰与谷
//
// 在一个整数数组中，“峰”是大于或等于相邻整数的元素，相应地，“谷”是小于或等于相邻整数的元素。例如，在数组{5, 8, 4, 2, 3, 4, 6}中，{8, 6}是峰， {5, 2}是谷。现在给定一个整数数组，将该数组按峰与谷的交替顺序排序。
//
// 示例:
//
// 输入: [5, 3, 1, 2, 3]
// 输出: [5, 1, 3, 2, 3]
// 提示：
//
// nums.length <= 10000

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const vector<int> explode(const string& s, const char& c)
{
    string buff{""};
    vector<int> v;

    for(auto n:s)
    {
        if(n != c && n != ' ') buff+=n; else
            if(n == c && buff != "") { v.push_back(stoi(buff)); buff = ""; }
    }
    if(buff != "") v.push_back(stoi(buff));

    return v;
}

int main(void)
{
    string s;
    getline(cin, s);
    vector<int> input{explode(s, ',')};

    sort(input.begin(), input.end(), greater<int>());
    for (size_t i = 1; i < input.size() - 1; i += 2) {
        swap(input[i], input[i + 1]);
    }

    for (auto &v: input) {
        cout<<v<<" ";
    }
    cout<<endl;

    return 0;
}
