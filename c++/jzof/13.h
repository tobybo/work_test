// 地上有一个m行n列的方格，从坐标 [0,0] 到坐标 [m-1,n-1] 。一个机器人从坐标 [0, 0] 的格子开始移动，它每次可以向左、右、上、下移动一格（不能移动到方格外），也不能进入行坐标和列坐标的数位之和大于k的格子。例如，当k为18时，机器人能够进入方格 [35, 37] ，因为3+5+3+7=18。但它不能进入方格 [35, 38]，因为3+5+3+8=19。请问该机器人能够到达多少个格子？
//
//
//
// 示例 1：
//
// 输入：m = 2, n = 3, k = 1
// 输出：3
// 示例 2：
//
// 输入：m = 3, n = 1, k = 0
// 输出：1
// 提示：
//
// 1 <= n,m <= 100
// 0 <= k <= 20

#ifndef _13_h_
#define _13_h_

#include <iostream>
#include <cmath>

int arr[6][12] {
    {0,1,2,3,4,5,6,7,8,9,1,2},
    {1,2,3,4,5,6,7,8,9,10,2,3},
    {2,3,4,5,6,7,8,9,10,11,3,4},
    {3,4,5,6,7,8,9,10,11,12,4,5},
    {4,5,6,7,8,9,10,11,12,13,5,6},
    {5,6,7,8,9,10,11,12,13,14,6,7},
};

class Solution {
public:
    int getIncSum(int min, int max) {
        int sum = 0;
        int pre_back_sum = min + max;
        int all_num = max - min + 1;
        int pre_back_num = (max - min + 1 + 1) / 2;
        int diff_sum = 0;
        if (all_num % 2 == 1) {
            diff_sum = pre_back_sum / 2;
        }
        sum = pre_back_sum * pre_back_num - diff_sum;
        printf("getIncSum, min,%d, max,%d, sum,%d\n", min, max, sum);
        return sum;
    }

    int blockCount(int m, int n, int k, int diff) {
        int sum = 0;
        if (m == 10 && n == 10) {
            int right_max_val = n - 1 + diff;
            if (k <= right_max_val) {
                int max_line_num = 10 - (right_max_val - k);
                int min_line_num = 1;
                sum += getIncSum(min_line_num, max_line_num);
            } else {
                int x = k - right_max_val;
                x = x > 10? 10:x;
                sum += x * 10;
                int rest_line_num = 10 - x;
                if (rest_line_num > 0) {
                    sum += getIncSum(10 - rest_line_num + 1, 10);
                }
            }
            return sum;
        }
        int last_line_num = 0;
        if (n - 1 + diff <= k) {
            last_line_num = n;
        } else {
            last_line_num = k + 1 - diff;
        }
        sum += last_line_num;
        for (int line = 1; line < m; ++line) {
            if (line + n - 1 + diff > k) {
                last_line_num--;
            }
            if (last_line_num > 0) {
                sum += last_line_num;
                //printf("line,%d, num,%d, sum,%d\n", line, last_line_num, sum);
            } else {
                break;
            }
        }
        return sum;
    }

    int getVal(int x, int y) {
        int ret = 0;
        ret += x / 10;
        ret += x % 10;
        ret += y / 10;
        ret += y % 10;
        return ret;
    }

    int movingCount(int m, int n, int k) {
        // k >= (n - 1 + diff)
        // diff++

        int sum = 0;
        int diff = 0;
        float f_m = m;
        float f_n = n;
        // 纵向的九宫格数量
        int line_block_num = ceil(f_m / 10);
        // 横向的九宫格数量
        int column_block_num = ceil(f_n / 10);
        int limit_column_block_num = column_block_num;
        for (int line_block_idx = 0; line_block_idx < line_block_num; ++line_block_idx) {
            for (int column_block_idx = 0; column_block_idx < limit_column_block_num; ++column_block_idx) {
                int _m, _n;
                _m = (line_block_idx + 1) * 10;
                if (_m > m) {
                    _m = m  % 10;
                } else {
                    _m = 10;
                }
                _n = (column_block_idx + 1) * 10;
                if (_n > n) {
                    _n = n  % 10;
                } else {
                    _n = 10;
                }
                diff = column_block_idx + line_block_idx;
                int left_x, left_y, up_x, up_y; // 新格子左边和上边的坐标
                int src_x, src_y; // 新格子起点
                src_x = line_block_idx * 10;
                src_y = column_block_idx * 10;
                left_x = src_x - 1;
                left_y = src_y;
                up_x = src_x;
                up_y = src_y - 1;
                if((line_block_idx == 0 && column_block_idx == 0) || (left_x >= 0 && left_y >= 0 && getVal(left_x, left_y) <= k) || (up_x >= 0 && up_y >= 0 && getVal(up_x, up_y) <= k)) {
                    sum += blockCount(_m, _n, k, diff);
                } else {
                    limit_column_block_num = column_block_idx;
                    break;
                }
            }
        }
        return sum;
    }
};

#endif
