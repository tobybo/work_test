// 面试题 05.02. 二进制数转字符串
//
// 二进制数转字符串。给定一个介于0和1之间的实数（如0.72），类型为double，打印它的二进制表达式。如果该数字无法精确地用32位以内的二进制表示，则打印“ERROR”。
//
// 示例1:
//
//  输入：0.625
//  输出："0.101"
// 示例2:
//
//  输入：0.1
//  输出："ERROR"
//  提示：0.1无法被二进制准确表示
//
//
// 提示：
//
// 32位包括输出中的 "0." 这两位。
// 题目保证输入用例的小数位数最多只有 6 位

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int main() {
    double num;
    cin>>num;
    string num_s = to_string(num).substr(2);
    while (num_s[num_s.size() - 1] == '0') {
        num_s.pop_back();
    }
    size_t max_len = 32;
    string s = "0.";
    double rest_val = 0;
    double cur_div = 1;
    int n = num_s.size();
    for (int j = 0; j < n; ++j) {
        if (s.size() >= max_len) {
            s = "ERROR";
            break;
        }
        // 0.625 -> 6; 62; 625;
        rest_val = rest_val * 10 + (num_s[j] - '0');
        cur_div = cur_div / 2 * 10;
        // printf("j: %d, c: %d, rest: %f, cur: %f", j, num_s[j], rest_val, cur_div);
        // cout<<", s: "<<s<<endl;
        if (rest_val >= cur_div) {
            rest_val -= cur_div;
            s.push_back('1');
        } else {
            s.push_back('0');
        }
        if (rest_val && j == n - 1) {
            n++;
            num_s.push_back('0');
        }
    }
    cout<<s<<endl;

    return 0;
}
