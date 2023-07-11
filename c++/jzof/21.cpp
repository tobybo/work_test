// 输入一个整数数组，实现一个函数来调整该数组中数字的顺序，使得所有奇数在数组的前半部分，所有偶数在数组的后半部分。
//
// 示例：
//
// 输入：nums = [1,2,3,4]
// 输出：[1,3,2,4]
// 注：[3,1,2,4] 也是正确的答案之一。
//
// 提示：
//
// 0 <= nums.length <= 50000
// 0 <= nums[i] <= 10000

#include <iostream>
#include <string>
using namespace std;

int main(int argc, char **argv) {
    int n = argc - 1;
    int input[n];
    for (int i = 0; i < n; ++i) {
        input[i] = stoi(string(argv[i + 1]));
    }
    int i = 0, j = n - 1;
    int temp;
    while (i < j) {
        while (i <= j && input[i] & 1) {
            // 奇数，位置不变
            i++;
        }
        while (j >= i && !(input[j] & 1)) {
            // 偶数，位置不变
            j--;
        }
        if (i < j) {
            temp = input[i];
            input[i] = input[j];
            input[j] = temp;
        }
    }
    for (int i = 0; i < n; ++i) {
        cout<<input[i]<<" ";
    }
    cout<<endl;
    return 0;
}
