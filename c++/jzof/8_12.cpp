// 设计一种算法，打印 N 皇后在 N × N 棋盘上的各种摆法，其中每个皇后都不同行、不同列，也不在对角线上。这里的“对角线”指的是所有的对角线，不只是平分整个棋盘的那两条对角线。
//
// 注意：本题相对原题做了扩展
// 示例:
//
//  输入：4
//  输出：[[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]
//  解释: 4 皇后问题存在如下两个不同的解法。
// [
//  [".Q..",  // 解法 1
//   "...Q",
//   "Q...",
//   "..Q."],
//
//  ["..Q.",  // 解法 2
//   "Q...",
//   "...Q",
//   ".Q.."]
// ]

#include <iostream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

void buildMap(vector<vector<string>> &ans, vector<vector<char>> &s, bool *horirontal, bool *vertical, bool *forward_slash, bool *backslash, int n, int i, int j) {
    if (horirontal[i]) return;
    if (vertical[j]) return;
    // check slash
    int fslash_idx = n - i - 1 + j;
    if (forward_slash[fslash_idx]) return;
    int bslash_idx = i + j;
    if (backslash[bslash_idx]) return;

    s[i][j] = 'Q';
    horirontal[i] = true;
    vertical[j] = true;
    forward_slash[fslash_idx] = true;
    backslash[bslash_idx] = true;
    if (i == n - 1) {
        // succ
        vector<string> temp;
        for (int i = 0; i < n; ++i) {
            temp.emplace_back(s[i].begin(), s[i].end());
        }
        ans.push_back(temp);
    } else {
        for (int k = 0; k < n; ++k) {
            buildMap(ans, s, horirontal, vertical, forward_slash, backslash, n, i + 1, k);
        }
    }
    s[i][j] = '.';
    horirontal[i] = false;
    vertical[j] = false;
    forward_slash[fslash_idx] = false;
    backslash[bslash_idx] = false;
}

int main() {
    int n;
    cin>>n;
    bool horirontal[n];
    memset(horirontal, 0, sizeof(horirontal));
    bool vertical[n];
    memset(vertical, 0, sizeof(vertical));
    bool forward_slash[2 * n];
    memset(forward_slash, 0, sizeof(forward_slash));
    bool backslash[2 * n];
    memset(backslash, 0, sizeof(backslash));
    vector<vector<string>> ans;
    vector<vector<char>> s(n, vector<char>(n, '.'));
    for (int i = 0; i < n; ++i) {
        buildMap(ans, s, horirontal, vertical, forward_slash, backslash, n, 0, i);
    }
    for (int i = 0; i < ans.size(); ++i) {
        cout<<"第 "<<i+1<<" 种:"<<endl;
        for (int j = 0; j < ans[0].size(); ++j) {
            cout<<ans[i][j]<<endl;
        }
        cout<<endl;
    }
    return 0;
}

