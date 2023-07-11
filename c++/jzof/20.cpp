// 剑指 Offer 20. 表示数值的字符串
//
// 请实现一个函数用来判断字符串是否表示数值（包括整数和小数）。
//
// 数值（按顺序）可以分成以下几个部分：
//
// 若干空格
//
// 一个 小数 或者 整数
// （可选）一个 'e' 或 'E' ，后面跟着一个 整数
//
// 若干空格
//
// 小数（按顺序）可以分成以下几个部分：
// （可选）一个符号字符（'+' 或 '-'）
// 下述格式之一：
// 至少一位数字，后面跟着一个点 '.'
// 至少一位数字，后面跟着一个点 '.' ，后面再跟着至少一位数字
// 一个点 '.' ，后面跟着至少一位数字
//
// 整数（按顺序）可以分成以下几个部分：
// （可选）一个符号字符（'+' 或 '-'）
// 至少一位数字
// 部分数值列举如下：
//
// ["+100", "5e2", "-123", "3.1416", "-1E-16", "0123"]
// 部分非数值列举如下：
//
// ["12e", "1a3.14", "1.2.3", "+-5", "12e+5.4"]
//
//
// 示例 1：
//
// 输入：s = "0"
// 输出：true
// 示例 2：
//
// 输入：s = "e"
// 输出：false
// 示例 3：
//
// 输入：s = "."
// 输出：false
// 示例 4：
//
// 输入：s = "    .1  "
// 输出：true
//
//
// 提示：
//
// 1 <= s.length <= 20
// s 仅含英文字母（大写和小写），数字（0-9），加号 '+' ，减号 '-' ，空格 ' ' 或者点 '.' 。

#include <iostream>
#include <string>
using namespace std;

class CSolution {
    public:
        enum STATE {
            PRE_SPACE = 1,
            DECIMAL = 2,
            INTEGER = 3,
            NUMBER = 4, // decimal or integer
            TIMES_TEN = 5, // about e or E
            AFTER_SPACE = 6,
        };

        bool isValidNumber(char c) {
            return c >= '0' && c <= '9';
        }

        bool isValid(char c) {
            if (isValidNumber(c)) return true;
            return isSign(c) || c == '.' || isEqualE(c) || c == ' ';
        }

        bool isEqualE(char c) {
            return c == 'e' || c == 'E';
        }

        bool isSign(char c) {
            return c == '+' || c == '-';
        }

        bool isNumber(string s) {
            char cur_state = PRE_SPACE;
            int n = s.size();
            for (int i = 0; i < n; ++i) {
                if (!isValid(s[i])) return false;
                switch (cur_state) {
                    case PRE_SPACE:
                        if (s[i] != ' ') {
                            i--;
                            cur_state = NUMBER;
                        }
                        break;
                    case NUMBER:
                        if (i - 1 < 0 || s[i - 1] == ' ') {
                            // the first char
                            if (isEqualE(s[i])) {
                                return false;
                            }
                            if (isSign(s[i])) {
                                break;
                            }
                        }
                        if (i - 1 < 0 || s[i - 1] == ' ' || isSign(s[i - 1])) {
                            // the first char without sign
                            bool point_start = false;
                            switch (s[i]) {
                                case '.' :
                                    i++;
                                    if (i >= n) return false;
                                    point_start = true;
                                    // fall through
                                default:
                                    if (isValidNumber(s[i])) {
                                        while (i < n && isValidNumber(s[i])) {
                                            i++;
                                        }
                                    } else {
                                        return false;
                                    }
                                    if (i == n) return true;
                                    if (!isValid(s[i])) return false;
                                    switch (s[i]) {
                                        case '.':
                                            if (point_start) return false;
                                            i++;
                                            if (i >= n) return false;
                                            // fall through
                                        case 'S': // S is special just for follow '.'
                                            if (isValidNumber(s[i])) {
                                                while (i < n && isValidNumber(s[i])) {i++;}
                                            } else {
                                                return false;
                                            }
                                            if (i == n) return true;
                                            // the end of one decimal;
                                            // next one maby e or E
                                            cur_state = TIMES_TEN;
                                            i--;
                                            break;
                                        case ' ':
                                            cur_state = AFTER_SPACE;
                                            break;
                                        default:
                                            cur_state = TIMES_TEN;
                                            i--;
                                            break;
                                    }
                                    break;
                            }
                        }
                        break;
                    case TIMES_TEN:
                        if (isEqualE(s[i])) {
                            cur_state = INTEGER;
                            if (i + 1 == n) return false;
                        } else {
                            cur_state = AFTER_SPACE;
                            i--;
                        }
                        break;
                    case INTEGER:
                        if (isSign(s[i])) {
                            i++;
                            if (i == n) return false;
                        }
                        if (isValidNumber(s[i])) {
                            while (i < n && isValidNumber(s[i])) {i++;}
                        } else {
                            return false;
                        }
                        if (i == n) return true;
                        cur_state = AFTER_SPACE;
                        i--;
                        break;
                    case AFTER_SPACE:
                        if (s[i] != ' ') {
                            return false;
                        }
                        break;
                    default:
                        break;
                }
            }
            return cur_state == AFTER_SPACE;
        }
};

int main() {
    string s;
    getline(cin, s);
    CSolution sol;
    cout<<(sol.isNumber(s)?"true":"false")<<endl;
    return 0;
}

