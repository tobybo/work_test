// 面试题 17.09. 第 k 个数
//
// 有些数的素因子只有 3，5，7，请设计一个算法找出第 k 个数。
// 注意，不是必须有这些素因子，而是必须不包含其他的素因子。
// 例如，前几个数按顺序应该是 1，3，5，7，9，15，21。
//
// 示例 1:
//
// 输入: k = 5
//
// 输出: 9

#include <iostream>
#include <climits>

using namespace std;

class Solution {
    private:
        int pre[5] = {-1, 1, 3, 5, 7};
    public:
        int getKthMagicNumber(int k) {
            if (k <= 4) return pre[k];
            int arr[k+1];
            arr[1] = 1;
            arr[2] = 3;
            arr[3] = 5;
            arr[4] = 7;
            int cur = INT_MAX;
            int p3 = 2;
            int p5 = 2;
            int p7 = 2;
            int cur3, cur5, cur7;
            for (int i = 5, j = 1; i <= k; ++i, ++j) {
                cur3 = 3 * arr[p3];
                cur5 = 5 * arr[p5];
                cur7 = 7 * arr[p7];
                cur = min(cur3, min(cur5, cur7));
                arr[i] = cur;
                if (cur == cur3) p3++;
                else if (cur == cur5) p5++;
                else p7++;
            }
            return cur;
        }
};

int main(void)
{
    int k;
    cin>>k;
    Solution sol;
    cout<<sol.getKthMagicNumber(k)<<endl;
    return 0;
}
