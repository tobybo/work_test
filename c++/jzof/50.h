// 在字符串 s 中找出第一个只出现一次的字符。如果没有，返回一个单空格。 s 只包含小写字母。
//
// 示例 1
//
// 输入：s = "abaccdeff"
// 输出：'b'
// 示例 2:
//
// 输入：s = ""
// 输出：' '
//
// 限制：
// 0 <= s 的长度 <= 50000

class Solution {
public:
    char firstUniqChar(string s) {
        int count[26] = {0};
        int addr[26] = {0};
        for (int i = 0; i < s.size(); ++i) {
            int val = s[i] - 'a';
            if (!count[val]++) {
                addr[val] = i;
            }
        }
        int min_idx = s.size();
        for (int i = 0; i < 26; ++i) {
            if (count[i] == 1) {
                min_idx = min(min_idx, addr[i]);
            }
        }
        if (min_idx >= 0 && min_idx < s.size()) {
            return s[min_idx];
        }
        return ' ';
    }
};
