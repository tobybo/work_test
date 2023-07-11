// 输入一个非负整数数组，把数组里所有数字拼接起来排成一个数，打印能拼接出的所有数字中最小的一个。
//
// 示例 1:
//
// 输入: [10,2]
// 输出: "102"
// 示例 2:
//
// 输入: [3,30,34,5,9]
// 输出: "3033459"
//
// 35
// 354
//
// 提示:
//
// 0 < nums.length <= 100
// 说明:
//
// 输出结果可能非常大，所以你需要返回一个字符串而不是整数
// 拼接起来的数字可能会有前导 0，最后结果不需要去掉前导 0

#ifndef _45_h_
#define _45_h_

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <numeric>
using namespace std;

class Solution {
public:
    string minNumber(vector<int>& nums) {
        vector<string> vec_s;
        for (int num: nums) {
            vec_s.push_back(to_string(num));
            //printf("num,%d\n", num);
            //ans += to_string(num);
        }
        auto func = [](const string &a, const string &b){ return a + b < b + a; };
        sort(vec_s.begin(), vec_s.end(), func);
        string ans;
        return accumulate(vec_s.begin(), vec_s.end(), ans);
    }
};

#endif
