// 面试题 01.08. 零矩阵
//
// 编写一种算法，若M × N矩阵中某个元素为0，则将其所在的行与列清零。
//
// 示例 1：
//
// 输入：
// [
//   [1,1,1],
//   [1,0,1],
//   [1,1,1]
// ]
// 输出：
// [
//   [1,0,1],
//   [0,0,0],
//   [1,0,1]
// ]
// 示例 2：
//
// 输入：
// [
//   [0,1,2,0],
//   [3,4,5,2],
//   [1,3,1,5]
// ]
// 输出：
// [
//   [0,0,0,0],
//   [0,4,5,0],
//   [0,3,1,0]
// ]

#include <iostream>
#include <string>
#include <cstring>
#include <vector>

using namespace std;

const vector<int> explode(const string& s, const char& c)
{
    string buff{""};
    vector<int> v;

    for(auto n:s)
    {
        if(n != c) buff+=n; else
            if(n == c && buff != "") { v.push_back(stoi(buff)); buff = ""; }
    }
    if(buff != "") v.push_back(stoi(buff));

    return v;
}

int main(void)
{
    int m,n;
    cin>>m;
    cin.ignore();

    vector<vector<int>> nums;
    for (int i = 0; i < m; ++i) {
        string s;
        getline(cin, s);
        vector<int> temp{explode(s, ',')};
        nums.push_back(temp);
        n = temp.size();
    }

    if (!m || !n) return 0;
    bool Y[m], X[n];
    for (int y = 0; y < m; ++y) {
        Y[y] = 1;
        for (int x = 0; x < n; ++x) {
            if (!nums[y][x]) {
                Y[y] = 0;
                break;
            }
        }
    }
    for (int x = 0; x < n; ++x) {
        X[x] = 1;
        for (int y = 0; y < m; ++y) {
            if (!nums[y][x]) {
                X[x] = 0;
                break;
            }
        }
    }
    for (int y = 0; y < m; ++y) {
        if (!Y[y]) {
            memset(&nums[y][0], 0, sizeof(int) * n);
            continue;
        }
        for (int x = 0; x < n; ++x) {
            nums[y][x] = X[x]? nums[y][x]: 0;
        }
    }
    for (auto &v: nums) {
        for (auto val: v) {
            cout<<val<<" ";
        }
        cout<<endl;
    }
    return 0;
}

