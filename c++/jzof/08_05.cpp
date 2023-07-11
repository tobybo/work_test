// 面试题 05.08. 绘制直线
//
// 已知一个由像素点组成的单色屏幕，每行均有 w 个像素点，所有像素点初始为 0，左上角位置为 (0,0)。
//
// 现将每行的像素点按照「每 32 个像素点」为一组存放在一个 int 中，再依次存入长度为 length 的一维数组中。
//
// 我们将在屏幕上绘制一条从点 (x1,y) 到点 (x2,y) 的直线（即像素点修改为 1），请返回绘制过后的数组。
//
//
//
// 注意：
//
// 用例保证屏幕宽度 w 可被 32 整除（即一个 int 不会分布在两行上）
//
//
// 示例1:
//
//  输入：length = 1, w = 32, x1 = 30, x2 = 31, y = 0
//  输出：[3]
//  解释：在第 0 行的第 30 位到第 31 位画一条直线，屏幕二进制形式表示为 [00000000000000000000000000000011]，因此返回 [3]
// 示例2:
//
//  输入：length = 3, w = 96, x1 = 0, x2 = 95, y = 0
//  输出：[-1, -1, -1]
//  解释：由于二进制 11111111111111111111111111111111 的 int 类型代表 -1，因此返回 [-1,-1,-1]
//
//
// 提示：
//
// 1 <= length <= 10^5
// 1 <= w <= 3 * 10^5
// 0 <= x1 <= x2 < w
// 0 <= y <= 10

#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

class Solution {
public:
    /*
     * 1. 创建长度为 length 的 int 数组 ans[]
     * 2. 设直线的起点为 A(x1, y)，终点为 B(x2, y)
     * 3. 计算 A 在数组中的索引 idxA = y * (w/32) + x1/32
     *    计算 B 在数组中的索引 idxB = y * (w/32) + x2/32
     * 4. 计算 A 在指定整数中的位数 bitA = 32 - (x1 % 32) [1,32位] 因为示例给出的顺序是从左往右对应高位到低位
     *    计算 B 在指定整数中的位数 bitB = 32 - (x2 % 32)
     * 5. 修改数组
     *      循环(idx = [idxA,idxB]):
     *          先将所有位设置为1
     *              ans[idx] = -1
     *      将 arr[idxA] 更高位置为0
     *          ans[idxA] >>= 32 - bitA
     *      将 arr[idxB] 更低位置为0
     *          ans[idxB] ^= (1 << bitB) - 1
     *      注意: 猜测 leet 的狗屎编译环境可能会报整数越界的错，可能需要先转成 unsigned int 再进行移位
     *
     * */
    vector<int> drawLine(int length, int w, int x1, int x2, int y) {
        vector<int> ans(length, 0);
        int idxA = y * (w/32) + x1/32;
        int idxB = y * (w/32) + x2/32;
        int bitA = 32 - (x1 % 32);
        int bitB = 32 - (x2 % 32);
        for (int idx = idxA; idx <= idxB; ++idx) {
            ans[idx] = -1;
        }
        //cout<<"bitA: "<<bitA<<", bitB: "<<bitB<<endl;
        ans[idxA] = (unsigned int)-1 >> (32 - bitA);
        //cout<<bitset<32>(ans[idxA])<<endl;
        ans[idxB] ^= (1 << (bitB - 1)) - 1;
        //cout<<bitset<32>(ans[idxA])<<endl;
        return ans;
    }
};

int main()
{
    int length, w, x1, x2, y;
    cin>>length>>w>>x1>>x2>>y;
    Solution sol;
    vector<int> ans = sol.drawLine(length, w, x1, x2, y);
    cout<<"[";
    for (auto v: ans) {
        cout<<v<<",";
    }
    cout<<"]"<<endl;
    return 0;
}
