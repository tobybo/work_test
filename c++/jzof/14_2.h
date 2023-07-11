// 给你一根长度为 n 的绳子，请把绳子剪成整数长度的 m 段（m、n都是整数，n>1并且m>1），每段绳子的长度记为 k[0],k[1]...k[m - 1] 。请问 k[0]*k[1]*...*k[m - 1] 可能的最大乘积是多少？例如，当绳子的长度是8时，我们把它剪成长度分别为2、3、3的三段，此时得到的最大乘积是18。
//
// 答案需要取模 1e9+7（1000000007），如计算初始结果为：1000000008，请返回 1。
//
// 示例 1：
//
// 输入: 2
// 输出: 1
// 解释: 2 = 1 + 1, 1 × 1 = 1
// 示例 2:
//
// 输入: 10
// 输出: 36
// 解释: 10 = 3 + 3 + 4, 3 × 3 × 4 = 36
//
//
// 提示：
//
// 2 <= n <= 1000

#ifndef _14_2_h_
#define _14_2_h_

#include <iostream>
#include <cmath>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    class bigNumber {
    public:
        // BASE * limit + BASE < 2e9: BASE <= 2e9/(limit + 1) 不会越界
        // BASE <= pow(2e9, 0.5)
        const int BASE = pow(2e9, 0.25);
        vector<int> carry_bit;
        bigNumber(int val){
            while (val > 0) {
                carry_bit.push_back(val % BASE);
                val = val / BASE;
            }
        }
        bigNumber(int val, int idx){
            for (int i = 0; i < idx; ++i) {
                carry_bit.push_back(0);
            }
            while (val > 0) {
                carry_bit.push_back(val % BASE);
                val = val / BASE;
            }
        }
        bigNumber(const bigNumber& second) {
            this->carry_bit = second.carry_bit;
        }

        void reset(int val) {
            carry_bit.resize(0);
            while (val > 0) {
                carry_bit.push_back(val % BASE);
                val = val / BASE;
            }
        }
        bigNumber& operator=(const bigNumber& second) {
            this->carry_bit = second.carry_bit;
            return *this;
        }
        bool operator <(const bigNumber &second) {
            int n = this->carry_bit.size();
            int m = second.carry_bit.size();
            if (n < m) {
                return true;
            } else if (n > m) {
                return false;
            }
            for (int i = n - 1; i >= 0; --i) {
                if (this->carry_bit[i] < second.carry_bit[i]) {
                    return true;
                } else if (this->carry_bit[i] > second.carry_bit[i]) {
                    return false;
                }
            }
            return false;
        }

        bigNumber& operator+(const bigNumber& second) {
            if (this->carry_bit.size() == 0) {
                this->carry_bit = second.carry_bit;
            } else {
                int m = second.carry_bit.size();
                if (m == 0) return *this;
                int add_val = 0;
                for (int i = 0; i < m; ++i) {
                    add_val += second.carry_bit[i];
                    if (this->carry_bit.size() <= i) {
                        while (add_val > 0) {
                            this->carry_bit.push_back(add_val % BASE);
                            add_val = add_val / BASE;
                        }
                    } else {
                        add_val += this->carry_bit[i];
                        this->carry_bit[i] = add_val % BASE;
                        add_val /= BASE;
                    }
                }
                if (add_val > 0) {
                    for (int i = m; i < this->carry_bit.size(); ++i) {
                        add_val += this->carry_bit[i];
                        this->carry_bit[i] = add_val % BASE;
                        add_val /= BASE;
                    }
                    while (add_val > 0) {
                        this->carry_bit.push_back(add_val % BASE);
                        add_val = add_val / BASE;
                    }
                }
            }
            return *this;
        }

        //(x*base + y) * (z*base + u) = xz * base * base + y * u + (yz + ux) * base
        bigNumber operator *(bigNumber second) {
            int n = this->carry_bit.size();
            int m = second.carry_bit.size();
            if (n == 0) return *this;
            if (m == 0) return second;
            bigNumber ret(0);
            for (int i = 0; i < m; ++i) {
                for (int j = 0; j < n; ++j) {
                    int val = this->carry_bit[j] * second.carry_bit[i];
                    ret = ret + bigNumber(val, i + j);
                }
            }
            return ret;
        }

        int fetch(int limit) {
            long long ans = 0;
            for (int i = this->carry_bit.size() - 1; i >= 0; --i) {
                ans = ans * BASE + this->carry_bit[i];
                ans = ans % limit;
                printf("i,%d, ans,%lld\n", i, ans);
            }
            return ans;
        }
    };

    void getAns(int n, vector<bigNumber> &f) {
        //if (f[n].carry_bit.size()) return f[n];
        bigNumber ans(0);
        int N = n;
        bigNumber second(0);
        for (int n = 2; n <= N; ++n) {
            for (int x = 1; x <= n - 1; ++x) {
                second.reset(x * (n - x));
                if (ans < second) {
                    ans = second;
                }
                if ((n - x) >= 2) {
                    second = bigNumber(x) * f[n - x];
                    //printf("getans, N,%d, n,%d, val,%d, x,%d, second,%d\n", N, n, f[n-x].fetch(1000000007), x, second.fetch(1000000007));
                    if (ans < second) {
                        ans = second;
                    }
                }
            }
            f[n] = ans;
            ans.reset(0);
        }
        //return ans;
    }

    // unsigned long long getAns(int n, unsigned long long*f) {
    //     if (f[n]) return f[n];
    //     unsigned long long ans = 0;
    //     int N = n;
    //     for (int n = 2; n <= N; ++n) {
    //         for (int x = 1; x <= n - 1; ++x) {
    //             ans = max(ans, (unsigned long long)x * (n - x));
    //             if ((n - x) >= 2) {
    //                 ans = max(ans, x * getAns(n - x, f));
    //             }
    //         }
    //     }
    //     f[n] = ans;
    //     return ans;
    // }

    int cuttingRope(int n) {
        // f(m, x, n) 表示将 n 分为 m 段, 第一段为 x 时的最大值, m = [2, n], x = [1, n - (m - 1)] (n - x 剩下的要足够分 m - 1 段, n - x >= m - 1)
        // ans = max(f(m, x, n))
        //
        // f(m, 1, n) = 1 * f(n - 1, m - 1)
        // f(m, 2, n) = 2 * f(n - 2, m - 1)
        // f(m, 3, n) = 3 * f(n - 3, m - 1)
        // f(m, x, n) = x * f(n - x, m - 1)
        //
        // f(n, x) 表示将 n 分成两段以上时, 第一段为 x 时的最大值; x = [1, n - 1] 因为至少分为两段
        // f(n, x) = max(x * f(n - x), x * (n - x))
        vector<bigNumber> f(n + 1, bigNumber(0));
        getAns(n, f);
        //while (res > 1000000007) res -= 1000000007;
        return f[n].fetch(1000000007);
    }
};

#endif
