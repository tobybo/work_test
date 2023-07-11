// 面试题 17.06. 2出现的次数
//
// 编写一个方法，计算从 0 到 n (含 n) 中数字 2 出现的次数。
//
// 示例:
//
// 输入: 25
// 输出: 9
// 解释: (2, 12, 20, 21, 22, 23, 24, 25)(注意 22 应该算作两次)
// 提示：
//
// n <= 10^9

#include <iostream>
#include <algorithm>

using namespace std;

inline int getNine(int n) {
    int ans = 0;
    int x = 9;
    while (n--) {
        ans += x;
        x *= 10;
    }
    return ans;
}

int main() {
    int n;
    cin>>n;
    int base = 2;
    string s = to_string(n);
    int len = s.size();
    int ans = 0;
    int left_num = 0;
    int right_num = 0;
    int cur = 0;
    int left_ratio, right_ratio, left_val, right_val;
    if (len == 1) {
        ans = n >= base? 1:0;
    } else {
        // 0: 1; 1: 198; 2: 180; 3: 200
        for (int i = 0; i < len; ++i) {
            left_num = i;
            right_num = len - i - 1;
            left_val = left_num? stoi(s.substr(0, left_num)) + 1: 0;
            right_val = right_num? stoi(s.substr(i + 1, right_num)) + 1: 0;
            cur = stoi(s.substr(i, 1));
            if (cur > base) {
                left_ratio = left_num ? left_val : 1;
                right_ratio = right_num ? getNine(right_num) + 1 : 1;
            } else {
                left_ratio = left_num ? left_val - 1: 0;
                right_ratio = right_num ? getNine(right_num) + 1 : 1;
            }
            ans += left_ratio * right_ratio;
            if (cur == base) {
                left_ratio = 1;
                right_ratio = right_num ? right_val : 1;
                ans += left_ratio * right_ratio;
            }
            printf("i,%d, cur,%d, left_num,%d, left_val,%d, right_num,%d, right_val,%d, ans,%d\n", i, cur, left_num, left_val, right_num, right_val, ans);
        }
    }
    cout<<ans<<endl;
    return 0;
}
