// 面试题 16.08. 整数的英语表示
//
// 给定一个整数，打印该整数的英文描述。
//
// 示例 1:
//
// 输入: 123
// 输出: "One Hundred Twenty Three"
// 示例 2:
//
// 输入: 12345
// 输出: "Twelve Thousand Three Hundred Forty Five"
// 示例 3:
//
// 输入: 1234567
// 输出: "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven"
// 示例 4:
//
// 输入: 1234567891
// 输出: "One Billion Two Hundred Thirty Four Million Five Hundred Sixty Seven Thousand Eight Hundred Ninety One"

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <numeric>

using namespace std;

vector<int> LEVEL {
    1000000000,
    1000000,
    1000,
};
unordered_map<int, string> LEVEL_NAME {
    {1000, "Thousand"},
    {1000000, "Million"},
    {1000000000, "Billion"},
};
int SMALL_MAX = 19;
int MIDDLE_MAX = 99;
int HIGH_MAX = 999;
vector<string> SMALL {"One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
vector<string> MIDDLE {"Twenty", "Thirty", "Fourty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};

void translate(int k, vector<string> &ans) {
    if (k == 0) return;
    if (k <= HIGH_MAX) {
        if (k <= SMALL_MAX) {
            ans.push_back(SMALL[k-1]);
        } else if (k <= MIDDLE_MAX) {
            ans.push_back(MIDDLE[k / 10 - 2]);
            translate(k % 10, ans);
        } else {
            ans.push_back(SMALL[k / 100 - 1]);
            ans.push_back("Hundred");
            translate(k % 100, ans);
        }
    } else {
        for (int lv_num: LEVEL) {
            if (k >= lv_num) {
                translate(k / lv_num, ans);
                ans.push_back(LEVEL_NAME[lv_num]);
                translate(k % lv_num, ans);
                break;
            }
        }
    }
}

int main() {
    int k;
    cin>>k;
    vector<string> ans;
    translate(k, ans);
    string s;
    int n = ans.size();
    for (int i = 0; i < n; ++i) {
        s += ans[i];
        if (i != n - 1) {
            s += " ";
        }
    }
    cout<<s<<endl;
    return 0;
}
