// 面试题 16.09. 运算
//
// 请实现整数数字的乘法、减法和除法运算，运算结果均为整数数字
// 程序中只允许使用加法运算符和逻辑运算符，允许程序中出现正负常数，
// 不允许使用位运算。
//
// 你的实现应该支持如下操作：
//
// Operations() 构造函数
// minus(a, b) 减法，返回a - b
// multiply(a, b) 乘法，返回a * b
// divide(a, b) 除法，返回a / b
// 示例：
//
// Operations operations = new Operations();
// operations.minus(1, 2); //返回-1
// operations.multiply(3, 4); //返回12
// operations.divide(5, -2); //返回-2
// 提示：
//
// 你可以假设函数输入一定是有效的，例如不会出现除法分母为0的情况
// 单个用例的函数调用次数不会超过1000次

#include <iostream>
#include <string>
#include <algorithm>
#include <bitset>
#include <climits>

using namespace std;

class Operations {
    public:
        Operations() {
        }

        unsigned int high_part[31] = {
            0xfffffffe,
            0xfffffffc,
            0xfffffff8,
            0xfffffff0,
            0xffffffe0,
            0xffffffc0,
            0xffffff80,
            0xffffff00,
            0xfffffe00,
            0xfffffc00,
            0xfffff800,
            0xfffff000,
            0xffffe000,
            0xffffc000,
            0xffff8000,
            0xffff0000,
            0xfffe0000,
            0xfffc0000,
            0xfff80000,
            0xfff00000,
            0xffe00000,
            0xffc00000,
            0xff800000,
            0xff000000,
            0xfe000000,
            0xfc000000,
            0xf8000000,
            0xf0000000,
            0xe0000000,
            0xc0000000,
            0x80000000,
        };

        unsigned int low_part[32] = {
            0x1,
            0x2,
            0x4,
            0x8,
            0x10,
            0x20,
            0x40,
            0x80,
            0x100,
            0x200,
            0x400,
            0x800,
            0x1000,
            0x2000,
            0x4000,
            0x8000,
            0x10000,
            0x20000,
            0x40000,
            0x80000,
            0x100000,
            0x200000,
            0x400000,
            0x800000,
            0x1000000,
            0x2000000,
            0x4000000,
            0x8000000,
            0x10000000,
            0x20000000,
            0x40000000,
            0x80000000,
        };

        unsigned int getCompletement(unsigned int val) {
            if (val == 0) return UINT_MAX;
            unsigned int high;
            int high_idx;
            for (int i = 0; i < 31; ++i) {
                if (val < low_part[i+1]) {
                    high_idx = i;
                    high = high_part[i];
                    break;
                }
            }
            /*
             * 1. 计算出每一个1所在的位数，记录进标记数组
             * 2. 遍历 0 到 high_idx, 将 未被标记的 low_part 累加上去
             * 3. 最后将得到的反码 + 1
             * */
            unsigned int vis[32] = {0};
            unsigned int ans = 0;
            vis[0] = val % 2;
            val = val - vis[0];
            while (ans < val) {
                unsigned long bit_val = 2;
                int count = 1;
                while (bit_val + bit_val + ans <= val) {
                    bit_val += bit_val;
                    count++;
                }
                vis[count] = 1;
                ans += bit_val;
            }

            for (int i = 0; i < high_idx; ++i) {
                if (!vis[i]) {
                    high += low_part[i];
                }
            }
            return high;
        }

        int getOppositeNumber(int val) {
            unsigned int temp = val;
            if (val > 0) {
                return getCompletement(temp) + 1;
            } else {
                /*
                 * 1. 将反码 - 1
                 * 2. 减去符号位
                 * 3. 复用正数求反码
                 * 4. 减去符号位
                 * */
                temp--;
                temp -= high_part[30];
                return getCompletement(temp) - high_part[30];
            }
        }

        int minus(int a, int b) {
            if (b == 0) return a;
            return a + getOppositeNumber(b);
        }

        int multiply(int a, int b) {
            if (a == 0 || b == 0) return 0;
            unsigned int tempa = a;
            int ans = 0;
            unsigned int last_div = -1;
            unsigned int div = 2;
            int flag = 0;
            if (b < 0) {
                b = getOppositeNumber(b);
                flag = 1;
            }
            while (b) {
                if (b % (int)div){
                    ans += (int)tempa;
                    b += last_div;
                }
                tempa += tempa;
                last_div += last_div;
                div += div;
            }
            if (flag) {
                ans = getOppositeNumber(ans);
            }
            return ans;
        }

        int divide(int a, int b) {
            if (b == 1) return a;
            if (b == -1) return getOppositeNumber(a);
            int ans = 0;
            int total = 0;
            int flag = 0;
            if (a < 0) {
                a = getOppositeNumber(a);
                flag = 1;
            }
            if (b < 0) {
                b = getOppositeNumber(b);
                flag = flag? 0:1;
            }
            if (a < b) return 0;
            while (ans < a) {
                unsigned int bit_val = b;
                unsigned int count = 1;
                while (bit_val + bit_val + ans <= (unsigned int)a) {
                    if ((int)bit_val > INT_MAX - (int)bit_val - ans) {
                        break;
                    }
                    bit_val += bit_val;
                    count += count;
                }
                if (ans + bit_val > (unsigned int)a) {
                    // 向下取整
                    break;
                }
                ans += bit_val;
                total += count;
            }
            if (flag) {
                total = getOppositeNumber(total);
            }
            return total;
        }
};

int main(void)
{
    Operations operations;
    //cout<<"expect fffffffe "<< hex <<operations.getCompletement(1)<<endl;
    // cout<<"expect 0 "<<(operations.getCompletement(9) & 9)<<endl;
    // cout<<"expect 0 "<<(operations.getCompletement(99) & 99)<<endl;
    // cout<<"expect 0 "<<(operations.getCompletement(999) & 999)<<endl;

    // int val = -2147483647;
    // int opt = operations.getOppositeNumber(val);
    // cout<<"expect "<<dec<<-val<<" "<<hex<<-val<<", "<<dec<<opt<<" "<<hex<<opt;
    // cout<<val<<" 正码: "<<bitset<sizeof(val)*8>(val)<<endl;

    cout<<"expect -1, "<<operations.minus(1, 2)<<endl; //返回-1
    cout<<"expect 0, "<<operations.minus(1, 1)<<endl; //返回-1
    cout<<"expect 2, "<<operations.minus(1, -1)<<endl; //返回-1
    cout<<"expect -2147483648, "<<operations.minus(-1, 2147483647)<<endl; //返回-1
    cout<<"expect 12, "<<operations.multiply(3, 4)<<endl; //返回12
    cout<<"expect -2147483600, "<<operations.multiply(-100, 21474836)<<endl; //返回12
    cout<<"expect -2, "<<operations.divide(5, -2)<<endl; //返回-2
    cout<<"expect 2, "<<operations.divide(5, 2)<<endl; //返回-2
    cout<<"expect 2, "<<operations.divide(-5, -2)<<endl; //返回-2

    cout<<"expect 109, "<<operations.minus(19, -90)<<endl; //返回-1
    cout<<"expect 2147483647, "<<operations.minus(0, -2147483647)<<endl; //返回-1
    cout<<"expect 2147483647, "<<operations.multiply(-1, -2147483647)<<endl; //返回12
    cout<<"expect -2147483648, "<<operations.divide(-2147483648, 1)<<endl; //返回-2

    cout<<"expect 1, "<<operations.divide(1834157185,1594413306)<<endl;
    return 0;
}
