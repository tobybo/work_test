// 面试题 16.21. 交换和
// 提示
// 中等
// 47
// 相关企业
// 给定两个整数数组，请交换一对数值（每个数组中取一个数值），使得两个数组所有元素的和相等。
//
// 返回一个数组，第一个元素是第一个数组中要交换的元素，第二个元素是第二个数组中要交换的元素。若有多个答案，返回任意一个均可。若无满足条件的数值，返回空数组。
//
// 示例:
//
// 输入: array1 = [4, 1, 2, 1, 1, 2], array2 = [3, 6, 3, 3]
// 输出: [1, 3]
// 示例:
//
// 输入: array1 = [1, 2, 3], array2 = [4, 5, 6]
// 输出: []
// 提示：
//
// 1 <= array1.length, array2.length <= 100000

#ifndef _16_21_H_
#define _16_21_H_

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

class CSolution {
    public:
        int entrance() {
            string s1, s2;
            getline(cin, s1);
            getline(cin, s2);
            auto string_to_arr = [](string s)->vector<int> {
                vector<int> ret;
                string temp = "";
                for (auto c: s) {
                    if (c == ',' && temp != "") {
                        ret.push_back(stoi(temp));
                        temp = "";
                    } else if ( c != ',' && c != ' ') {
                        temp.push_back(c);
                    }
                }
                if (temp != "") {
                    ret.push_back(stoi(temp));
                }
                return ret;
            };
            vector<int> arr1 = string_to_arr(s1);
            vector<int> arr2 = string_to_arr(s2);
            vector<int> ret = findPairNum(arr1, arr2);
            if (!ret.size()) {
                cout<<"can not find"<<endl;
            } else {
                cout<<"ret: "<<ret[0]<<", "<<ret[1]<<endl;
            }
            return 0;
        }

	public:
        /* 找出两个数组中各一个数，交换之后两个数组之和相等。
         * 1. 计算两个数组各自的和，获取差值 diff，两个交换的数的差值为 expectation = diff/2。
         * 2. 对两个数组进行排序（递增）。
         * 3. 通过双指针，查询符合差值为 expectation 的两个数。
         * */
        vector<int> findPairNum(vector<int>& arr1, vector<int>& arr2) {
            auto cal_sum = [](vector<int>& arr)->int{
                int sum = 0;
                for (auto num : arr) {
                    sum += num;
                }
                return sum;
            };
            int expectation = cal_sum(arr1) - cal_sum(arr2);
            int min_flag = 0; // 0 数组1的和较大 1 数组2的和较大
            if (expectation < 0) {
                expectation = -expectation;
                min_flag = 1;
            }
            if (expectation & 1) {
                /* toby@2023-08-13): 奇数差值无法通过交换两个整数实现题目要求 */
                return {};
            }
            expectation >>= 1;
            sort(arr1.begin(), arr1.end());
            sort(arr2.begin(), arr2.end());

            auto double_pointer = [min_flag, expectation](vector<int>& arr1, vector<int>& arr2)->vector<int>{
                int nonius_1 = 0;
                int nonius_2 = 0;
                int len_1 = arr1.size();
                int len_2 = arr2.size();
                while (nonius_1 < len_1 && nonius_2 < len_2) {
                    while (arr1[nonius_1] + expectation == arr2[nonius_2]) {
                        if (min_flag) {
                            return {arr1[nonius_1], arr2[nonius_2]};
                        }
                        else {
                            return {arr2[nonius_2], arr1[nonius_1]};
                        }
                    }
                    while (nonius_2 < len_2 && arr1[nonius_1] + expectation > arr2[nonius_2]) {
                        nonius_2++;
                    }
                    while (nonius_1 < len_1 && arr1[nonius_1] + expectation < arr2[nonius_2]) {
                        nonius_1++;
                    }
                }
                return {};
            };

            vector<int> ret(2);
            if (min_flag) {
                ret = double_pointer(arr1, arr2);
            } else {
                ret = double_pointer(arr2, arr1);
            }
            return ret;
        }
};


#endif
