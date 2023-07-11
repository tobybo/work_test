// 面试题 08.05. 递归乘法
//
// 递归乘法。 写一个递归函数，不使用 * 运算符， 实现两个正整数的相乘。可以使用加号、减号、位移，但要吝啬一些。
//
// 示例1:
//
//  输入：A = 1, B = 10
//  输出：10
// 示例2:
//
//  输入：A = 3, B = 4
//  输出：12
// 提示:
//
// 保证乘法范围不会溢出

#include <iostream>

using namespace std;

int multiplication(int A, int B) {
    int ans = 0;
    while (B) {
        if (B & 1) ans += A;
        B >>= 1;
        A <<= 1;
    }
    return ans;
}

int main(void)
{
    int A, B;
    cin>>A>>B;

    int ans = multiplication(A, B);
    cout<<ans<<endl;

    return 0;
}
