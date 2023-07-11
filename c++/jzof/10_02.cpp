// 面试题 10.02. 变位词组
//
// 编写一种方法，对字符串数组进行排序，将所有变位词组合在一起。变位词是指字母相同，但排列不同的字符串。
//
// 注意：本题相对原题稍作修改
//
// 示例:
//
// 输入: ["eat", "tea", "tan", "ate", "nat", "bat"],
// 输出:
// [
//   ["ate","eat","tea"],
//   ["nat","tan"],
//   ["bat"]
// ]
// 说明：
//
// 所有输入均为小写字母。
// 不考虑答案输出的顺序。

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

const vector<string> explode(const string& s, const char& c)
{
    string buff{""};
    vector<string> v;

    for(auto n:s)
    {
        if(n != c && n != '"' && n != ' ') buff+=n; else
            if(n == c && buff != "") { v.push_back(buff); buff = ""; }
    }
    if(buff != "") v.push_back(buff);

    return v;
}

int main() {
    string s;
    getline(cin, s);
    cout<<"s: "<<s<<endl;
    vector<string> input{explode(s, ',')};
    unordered_map<uint64_t, unordered_map<uint64_t, int>> map;
    uint64_t key = 0;
    uint64_t value = 0;
    uint64_t cur = 0;
    int idx = 0;
    vector<vector<string>> ans;
    for (auto &s : input) {
        cout<<"input str: "<<s<<endl;
        key = 0;
        value = 0;
        for (char c: s) {
            cur = 1 << (c - 'a');
            key |= cur;
            value += cur;
        }
        auto itor = map.find(key);
        if (itor == map.end()) {
            map[key][value] = ans.size();
            ans.push_back({s});
        } else {
            auto inner_itor = itor->second.find(value);
            if (inner_itor != itor->second.end()) {
                idx = inner_itor->second;
                ans[idx].push_back(s);
                sort(s.begin(), s.end());
                sort(ans[idx][0].begin(), ans[idx][0].end());
                if (s != ans[idx][0]) {
                    cout<<"unmatch: "<<s<<" and "<<ans[idx][0]<<endl;
                }
            } else {
                itor->second[value] = ans.size();
                ans.push_back({s});
            }
        }
    }
    for (auto &v: ans) {
        for (auto &s: v) {
            cout<<s<<" ";
        }
        cout<<endl;
    }
    return 0;
}



