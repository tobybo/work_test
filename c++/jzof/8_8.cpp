// 面试题 08.08. 有重复字符串的排列组合
//
// 有重复字符串的排列组合。编写一种方法，计算某字符串的所有排列组合。
//
// 示例1:
//
//  输入：S = "qqe"
//  输出：["eqq","qeq","qqe"]
// 示例2:
//
//  输入：S = "ab"
//  输出：["ab", "ba"]
// 提示:
//
// 字符都是英文字母。
// 字符串长度在[1, 9]之间。

// 方法一：动态规划

#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

vector<string> ans;

void fillStr(string &input, string &temp, int pos, bool *vis) {
    int n = input.size();
    if (pos == n) {
        ans.push_back(temp);
        return;
    }
    for (int i = 0; i < n; ++i) {
        if (vis[i] || (i - 1 >= 0 && input[i - 1] == input[i] && !vis[i - 1])) {
            continue;
        }
        temp.push_back(input[i]);
        vis[i] = true;
        fillStr(input, temp, pos+1, vis);
        vis[i] = false;
        temp.pop_back();
    }
}

int main(void)
{
    string input;
    cin>>input;

    sort(input.begin(), input.end());
    string temp;

    int n = input.size();
    bool vis[n];
    memset(vis, 0, sizeof vis);

    fillStr(input, temp, 0, vis);

    for (auto &s: ans) {
        static string sep = "";
        cout<<sep<<s;
        sep = "\n\r";
    }
    cout<<endl;

    return 0;
}
